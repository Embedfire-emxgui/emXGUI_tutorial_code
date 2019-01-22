/**
  *********************************************************************
  * @file    gui_lcd_port.c
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   液晶驱动接口
  *********************************************************************
  * @attention
  * 官网    :www.emXGUI.com
  *
  **********************************************************************
  */ 
  
#include "board.h"
#include "gui_drv.h"
#include "gui_drv_cfg.h"
#include "gui_lcd_port.h"
/*============================================================================*/




/**
  * @brief  液晶屏初始化接口
  * @param  fb_addr 要使用的显存地址
  */
void LCD_HardInit(u32 fb_addr)
{	
  /* 初始化液晶屏 */  
#if	(LCD_FORMAT == COLOR_FORMAT_RGB565)
  LCD_Init(fb_addr, 33, LTDC_Pixelformat_RGB565);
#endif
  
#if	(LCD_FORMAT == COLOR_FORMAT_XRGB8888)
  LCD_Init(fb_addr, 21, LTDC_Pixelformat_ARGB8888);
#endif

}

/**
  * @brief  液晶背光控制接口
  * @param  on 1为亮，其余值为灭
  */
void LCD_BkLight(int on)
{
  LCD_BackLed_Control(on);
}


/**
  * @brief  初始化显示设备接口，并创建SURFACE表面
  * @param  无
  * @retval 显示设备Surface对象指针，创建得到的绘图表面
  */
SURFACE* GUI_DisplayInit(void)
{
  /* 绘图表面 */
	SURFACE *pSurf;

#if	(LCD_FORMAT == COLOR_FORMAT_RGB565)

  //创建绘图表面
  /* 动态申请的方式  */
// pSurf = GUI_CreateSurface(SURF_RGB565, 
//                              LCD_XSIZE,LCD_YSIZE,
//                              LCD_XSIZE*2,
//                              NULL);  
                              
  /* 直接指定地址的方式， 显存地址，*/
 pSurf = GUI_CreateSurface(SURF_RGB565, 
                              LCD_XSIZE,LCD_YSIZE,
                              LCD_XSIZE*2,
                              (void*)LCD_FRAME_BUFFER);    

#endif

#if	(LCD_FORMAT == COLOR_FORMAT_XRGB8888)
	//动态申请的方式，初始化LCD Surface结构数据(XRGB8888格式)
	//lcd_buffer =(u8*)GUI_GRAM_Alloc(LCD_XSIZE,LCD_YSIZE*4);
  
  /* 直接指定地址的方式， 显存地址，*/
  /* 动态申请的方式  */
// pSurf = GUI_CreateSurface(SURF_XRGB8888, 
//                              LCD_XSIZE,LCD_YSIZE,
//                              LCD_XSIZE*4,
//                              NULL);  
                          
  pSurf = GUI_CreateSurface(SURF_XRGB8888, 
                              LCD_XSIZE,LCD_YSIZE,
                              LCD_XSIZE*4,
                              (void*)LCD_FRAME_BUFFER);                             

#endif
  
  if(pSurf == NULL)
  {
    GUI_Printf("#Error: GUI_CreateSurface Failed.\r\n");
  }

  //LCD硬件初始化
 	LCD_HardInit((u32)pSurf->Bits); 

  //清屏
	pSurf->GL->FillArea(pSurf,0,0,LCD_XSIZE,LCD_YSIZE,pSurf->CC->MapRGB(0,0,0)); 
	//打开背光
  LCD_BkLight(TRUE);

	while(0)
	{ //测试

		pSurf->GL->FillArea(pSurf,20,30,128,80,pSurf->CC->MapRGB(255,255,255));
		GUI_msleep(200);
		pSurf->GL->FillArea(pSurf,20,30,128,80,pSurf->CC->MapRGB(255,0,0));
		GUI_msleep(200);
		pSurf->GL->FillArea(pSurf,20,30,128,80,pSurf->CC->MapRGB(0,255,0));
		GUI_msleep(200);
		pSurf->GL->FillArea(pSurf,20,30,128,80,pSurf->CC->MapRGB(0,0,255));
		GUI_msleep(200);
		pSurf->GL->FillArea(pSurf,20,30,128,80,pSurf->CC->MapRGB(0,0,0));
		GUI_msleep(200);
		break;
	}

	return pSurf;
}


/**
  * @brief  创建SURFACE表面
  * @param  Format 绘图表面格式
  * @param  Width Height 绘图表面宽高
  * @param  LineBytes 绘图表面每行像素占多少字节
  * @param  bits 显存地址，若为NULL，则会使用GUI_GMEM_Alloc申请动态显存
  * @retval 显示设备Surface对象指针，创建得到的绘图表面
  */
SURFACE*	GUI_CreateSurface(SURF_FORMAT Format,int Width,int Height,int LineBytes,void *bits)
{

	SURFACE *pSurf;
   		
	switch(Format)
	{
		
		case	SURF_RGB332:
				pSurf = (SURFACE*)GUI_MEM_Alloc(sizeof(SURFACE));

				pSurf->Flags =0;

				if(LineBytes <= 0)
				{
					LineBytes = Width;
				}

				if(bits==NULL)
				{
					bits = (void*)GUI_GRAM_Alloc(Height*LineBytes);
					pSurf->Flags |= SURF_FLAG_GRAM;

				}
				SurfaceInit_RGB332(pSurf,&GL_MEM_8PP,Width,Height,LineBytes,bits);
				break;
					////
		
		case	SURF_RGB565:
				pSurf = (SURFACE*)GUI_MEM_Alloc(sizeof(SURFACE));
				pSurf->Flags =0;
				if(LineBytes <= 0)
				{
					LineBytes = Width*2;
				}
				if(bits==NULL)
				{
					bits = (void*)GUI_GRAM_Alloc(Height*LineBytes);
					pSurf->Flags |= SURF_FLAG_GRAM;

				}
				SurfaceInit_RGB565(pSurf,&GL_MEM_16PP,Width,Height,LineBytes,bits);
				break;
				////
		
		case	SURF_ARGB4444:
				pSurf = (SURFACE*)GUI_MEM_Alloc(sizeof(SURFACE));
				pSurf->Flags =0;
				if(LineBytes <= 0)
				{
					LineBytes = Width*2;
				}
				if(bits==NULL)
				{
					bits = (void*)GUI_GRAM_Alloc(Height*LineBytes);
					pSurf->Flags |= SURF_FLAG_GRAM;

				}
				SurfaceInit_ARGB4444(pSurf,&GL_MEM_16PP,Width,Height,LineBytes,bits);
				break;
				////
						
		case	SURF_XRGB8888:
				pSurf = (SURFACE*)GUI_MEM_Alloc(sizeof(SURFACE));
				pSurf->Flags =0;
				if(LineBytes <= 0)
				{
					LineBytes = Width*4;
				}
				if(bits==NULL)
				{
					bits = (void*)GUI_GRAM_Alloc(Height*LineBytes);
					pSurf->Flags |= SURF_FLAG_GRAM;

				}
				SurfaceInit_XRGB8888(pSurf,&GL_MEM_32PP,Width,Height,LineBytes,bits);
				break;
				////	
									
		case	SURF_ARGB8888:
				pSurf = (SURFACE*)GUI_MEM_Alloc(sizeof(SURFACE));
				pSurf->Flags =0;
				if(LineBytes <= 0)
				{
					LineBytes = Width*4;
				}
				if(bits==NULL)
				{
					bits = (void*)GUI_GRAM_Alloc(Height*LineBytes);
					pSurf->Flags |= SURF_FLAG_GRAM;

				}
				SurfaceInit_ARGB8888(pSurf,&GL_MEM_32PP,Width,Height,LineBytes,bits);
				break;
				////	
									
		default:
				pSurf = NULL;
				break;
				////
	
	}
		
	return	pSurf;
}


/**
  * @brief  释放绘图表面
  * @param  pSurf 要释放的绘图表面
  * @note  它会释放pSurf使用的内存，
  *         若该表面申请了动态内存作为显存空间，还会释放相应的显存空间 
  * @retval 无
  */
void	GUI_DeleteSurface(const SURFACE *pSurf)
{
	if(pSurf!=NULL)
	{
		if(pSurf->Flags&SURF_FLAG_GRAM)
		{
			GUI_GRAM_Free(pSurf->Bits);
		}
		GUI_MEM_Free((void*)pSurf);
	}
}

/********************************END OF FILE****************************/

