

#include	"fsl_pxp.h"

#include	"emxGUI.h"
#include	"emxGUI_Arch.h"

/*=========================================================================================*/
/*=========================================================================================*/

void MEM_Flush(u32 addr,u32 size)
{
//  SCB_CleanDCache_by_Addr((uint32_t*)addr,size);
}

/*=========================================================================================*/

static volatile int PXP_Rdy=FALSE;
static GUI_SEM *sem_pxp=NULL;
static int init=0;

void PXP_IRQHandler(void)
{
  uint32_t ulReturn;
  /* 进入临界段，临界段可以嵌套 */
  ulReturn = taskENTER_CRITICAL_FROM_ISR(); 

	PXP_ClearStatusFlags(PXP,kPXP_CompleteFlag);
	NVIC_ClearPendingIRQ(PXP_IRQn);

	//size =PXP->OUT_PITCH*(PXP->OUT_LRC&0xFFFF);
	//SCB_InvalidateDCache_by_Addr(PXP->OUT_BUF,size);

	PXP_Rdy=TRUE;
	GUI_SemPostISR(sem_pxp);

	taskEXIT_CRITICAL_FROM_ISR( ulReturn ); 
}

void PXP_WaitRdy(void)
{
	while(PXP_Rdy==FALSE)
	{
		GUI_SemWait(sem_pxp,200);
	}

}

void PXP_WaitDone(uint32_t *addr,u32 size)
{
	while(PXP_Rdy==FALSE)
	{
		GUI_SemWait(sem_pxp,200);
	}
	PXP->CTRL_CLR =PXP_CTRL_ENABLE_MASK;

	SCB_InvalidateDCache_by_Addr(addr,size);

}

void PXP_Execu(void)
{
	PXP_Rdy =FALSE;

	//PXP_Start(PXP);
	PXP->CTRL_SET =PXP_CTRL_ENABLE_MASK;
}

void PXP_DrvInit(void)
{
	if(init==0)
	{
		init=1;

		sem_pxp =GUI_SemCreate(0,1);
		PXP_Rdy =TRUE;

		PXP_Init(PXP);
		PXP_Reset(PXP);
		PXP_SetProcessBlockSize(PXP,kPXP_BlockSize16);
		PXP_EnableOverWrittenAlpha(PXP,FALSE);
		PXP_EnableAlphaSurfaceOverlayColorKey(PXP,FALSE);
		PXP_EnableLcdHandShake(PXP,false);
		PXP_EnableContinousRun(PXP,false);
     
		PXP_EnableInterrupts(PXP,kPXP_CompleteInterruptEnable);
		NVIC_EnableIRQ(PXP_IRQn);
		NVIC_ClearPendingIRQ(PXP_IRQn);
    NVIC_SetPriority(PXP_IRQn, 6U);
		/* Disable AS. */
		PXP_SetAlphaSurfacePosition(PXP, 0, 0, 0, 0);
		PXP_SetOverwrittenAlphaValue(PXP,255);
		PXP_EnableOverWrittenAlpha(PXP,false);

		/* Disable CSC1, it is enabled by default. */
		PXP_EnableCsc1(PXP, false);
	}

}

/*=========================================================================================*/

BOOL	PXP_fill_rect(const SURFACE *pSurf,int x,int y,int w,int h,u32 c)
{
	pxp_ps_pixel_format_t pixelFormat;
	u32 out_addr;

//	return FALSE;

	if( (w*h) < (128*128))
	{
		return FALSE;
	}

	switch(pSurf->Format)
	{

	case SURF_RGB565:
		pixelFormat =kPXP_OutputPixelFormatRGB565;
		out_addr =(uint32_t)pSurf->GL->SetPos(pSurf,x,y);
		break;

	case SURF_XRGB8888:
		pixelFormat =kPXP_OutputPixelFormatRGB888;
		out_addr =(uint32_t)pSurf->GL->SetPos(pSurf,x,y);
		break;
#if 0
	case SURF_ARGB4444:
		pixelFormat =kPXP_OutputPixelFormatRGB565;
		out_addr =(uint32_t)pSurf->GL->SetPos(pSurf,x,y);
		break;

	case SURF_ARGB8888:
		pixelFormat =kPXP_OutputPixelFormatRGB888;
		out_addr =(uint32_t)pSurf->GL->SetPos(pSurf,x,y);
		break;
#endif
	default:
		return FALSE;

	}


	c=pSurf->CC->ToARGB(c);

	PXP_WaitRdy();

	//PXP_SetProcessSurfaceBackGroundColor(PXP,c);
	PXP->PS_BACKGROUND =c;

	//PXP_SetProcessSurfacePosition(PXP,0,0,0,0);
	PXP->OUT_PS_ULC =((0xFFFF)<<16)|(0xFFFF);
	PXP->OUT_PS_LRC =((0xFFFF)<<16)|(0xFFFF);

	//PXP_SetProcessSurfaceScaler(PXP,0,0,0,0);
	PXP->PS_CTRL &= ~((0x3<<10)|(0x3<<8));
	PXP->PS_SCALE = 0x10001000;

	//PXP_SetAlphaSurfacePosition(PXP,0,0,0,0);
	PXP->OUT_AS_ULC =(0xFFFF<<16)|(0xFFFF);
	PXP->OUT_AS_LRC =(0xFFFF<<16)|(0xFFFF);


#if 0
	//out_cfg.pixelFormat =kPXP_OutputPixelFormatRGB565;
	out_cfg.width =w;
	out_cfg.height =h;
	out_cfg.pitchBytes =pSurf->WidthBytes;
	//out_cfg.buffer0Addr =(uint32_t)gdev_16bpp_set_addr(pSurf,x,y);
	out_cfg.buffer1Addr =(uint32_t)0;
	out_cfg.interlacedMode =kPXP_OutputProgressive;
	PXP_SetOutputBufferConfig(PXP,&out_cfg);
#endif

	PXP->OUT_CTRL = (kPXP_OutputProgressive<<8)|(pixelFormat);
	PXP->OUT_BUF  =(u32)out_addr;
//	PXP->OUT_BUF2 =0;

	PXP->OUT_PITCH =pSurf->WidthBytes;
	PXP->OUT_LRC   =((w-1)<<16)|(h-1);

	PXP_Execu();
	PXP_WaitDone((uint32_t*)out_addr,pSurf->WidthBytes*h);

	return TRUE;

}


BOOL	PXP_draw_bitmap_RGB(const SURFACE *pSurf,int x,int y,int w,int h,int width_bytes,const U8 *bits,pxp_ps_pixel_format_t pixelFormat)
{
	pxp_ps_buffer_config_t ps_cfg;
	pxp_output_buffer_config_t out_cfg;
	int dst_w,dst_h;
	int src_w,src_h;

//	if((u32)bits < SDRAM_BASE)
//	{
//		return FALSE;
//	}

	if( (w*h) < (32*16))
	{
		return FALSE;
	}
	switch(pSurf->Format)
	{

	case SURF_RGB565:
		out_cfg.pixelFormat =kPXP_OutputPixelFormatRGB565;
		out_cfg.buffer0Addr =(uint32_t)pSurf->GL->SetPos(pSurf,x,y);
		break;

	case SURF_XRGB8888:
		out_cfg.pixelFormat =kPXP_OutputPixelFormatRGB888;
		out_cfg.buffer0Addr =(uint32_t)pSurf->GL->SetPos(pSurf,x,y);
		break;

	case SURF_ARGB4444:
		out_cfg.pixelFormat =kPXP_OutputPixelFormatARGB4444;
		out_cfg.buffer0Addr =(uint32_t)pSurf->GL->SetPos(pSurf,x,y);
		break;

	case SURF_ARGB8888:
		out_cfg.pixelFormat =kPXP_OutputPixelFormatARGB8888;
		out_cfg.buffer0Addr =(uint32_t)pSurf->GL->SetPos(pSurf,x,y);
		break;

	default:
		return FALSE;

	}

	MEM_Flush((u32)bits,h*width_bytes);

	ps_cfg.pixelFormat =pixelFormat;
	ps_cfg.bufferAddr =(uint32_t)bits;

	dst_w =w;
	dst_h =h;
	src_w =w;
	src_h =h;
	PXP_WaitRdy();

 	//ps_cfg.pixelFormat =kPXP_PsPixelFormatRGB565;
	//ps_cfg.bufferAddr  =(uint32_t)bits;
	ps_cfg.pitchBytes  =width_bytes;
	ps_cfg.swapByte =FALSE;
	PXP_SetProcessSurfaceBufferConfig(PXP,&ps_cfg);

	//PXP_SetProcessSurfaceBackGroundColor(PXP,0x000000);
	//PXP_SetProcessSurfacePosition(PXP,0,0,dst_w-1,dst_h-1);
	PXP->OUT_PS_ULC =((0)<<16)|(0);
	PXP->OUT_PS_LRC =((dst_w-1)<<16)|(dst_h-1);

	//PXP_SetProcessSurfaceScaler(PXP,src_w,src_h,dst_w,dst_h);
	PXP->PS_CTRL &= ~((0x3<<10)|(0x2<<8)); //DECX & DECY
//	PXP->PS_CTRL |=  ((0x0<<10)|(0x0<<8));

	PXP->PS_SCALE = 0x10001000;

	//PXP_SetAlphaSurfacePosition(PXP, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF);
	PXP->OUT_AS_ULC =(0xFFFF<<16)|(0xFFFF);
	PXP->OUT_AS_LRC =(0xFFFF<<16)|(0xFFFF);

	//out_cfg.pixelFormat =kPXP_OutputPixelFormatRGB565;
	out_cfg.width =dst_w;
	out_cfg.height =dst_h;
	out_cfg.pitchBytes =pSurf->WidthBytes;
	//out_cfg.buffer0Addr =(uint32_t)gdev_16bpp_set_addr(pSurf,x,y);
	out_cfg.buffer1Addr =(uint32_t)0;
	out_cfg.interlacedMode =kPXP_OutputProgressive;
	PXP_SetOutputBufferConfig(PXP,&out_cfg);

	PXP_Execu();
	PXP_WaitDone((uint32_t*)out_cfg.buffer0Addr,out_cfg.pitchBytes*out_cfg.height);

	return TRUE;

}

BOOL 	PXP_draw_bitmap_ARGB(const SURFACE *pSurf,int x,int y,int w,int h,int width_bytes,const U8 *bits,pxp_as_pixel_format_t pixelFormat)
{
	pxp_ps_buffer_config_t ps_cfg;
	pxp_as_buffer_config_t as_cfg;
	pxp_output_buffer_config_t out_cfg;

	//return FALSE;

//	if((u32)bits < SDRAM_BASE)
//	{
//		return FALSE;
//	}

	if( (w*h) < (32*16))
	{
		return FALSE;
	}


	switch(pSurf->Format)
	{

	case SURF_RGB565:
		out_cfg.pixelFormat =kPXP_OutputPixelFormatRGB565;
		out_cfg.buffer0Addr =(uint32_t)pSurf->GL->SetPos(pSurf,x,y);
		ps_cfg.pixelFormat =kPXP_PsPixelFormatRGB565;

		break;

	case SURF_XRGB8888:
		out_cfg.pixelFormat =kPXP_OutputPixelFormatRGB888;
		out_cfg.buffer0Addr =(uint32_t)pSurf->GL->SetPos(pSurf,x,y);
		ps_cfg.pixelFormat =kPXP_PsPixelFormatRGB888;
		break;
#if 0
	case SURF_ARGB4444:
		out_cfg.pixelFormat =kPXP_OutputPixelFormatARGB4444;
		out_cfg.buffer0Addr =(uint32_t)pSurf->GL->SetPos(pSurf,x,y);
		ps_cfg.pixelFormat =kPXP_PsPixelFormatRGB444;
		break;
#endif

#if 0
	case SURF_ARGB8888:
		out_cfg.pixelFormat =kPXP_OutputPixelFormatARGB8888;
		out_cfg.buffer0Addr =(uint32_t)pSurf->GL->SetPos(pSurf,x,y);
		ps_cfg.pixelFormat =kPXP_PsPixelFormatRGB888;
		break;
#endif

	default:
		return FALSE;

	}


	MEM_Flush((u32)bits,h*width_bytes);

	PXP_WaitRdy();

	ps_cfg.bufferAddr  =out_cfg.buffer0Addr;
	ps_cfg.pitchBytes  =pSurf->WidthBytes;
	ps_cfg.swapByte =FALSE;
	PXP_SetProcessSurfaceBufferConfig(PXP,&ps_cfg);

	//PXP_SetProcessSurfaceBackGroundColor(PXP,0x000000);
	PXP->PS_BACKGROUND =0x000000;

	//PXP_SetProcessSurfacePosition(PXP,0,0,dst_w-1,dst_h-1);
	PXP->OUT_PS_ULC =((0)<<16)|(0);
	PXP->OUT_PS_LRC =((w-1)<<16)|(h-1);

	//PXP_SetProcessSurfaceScaler(PXP,src_w,src_h,dst_w,dst_h);
	PXP->PS_CTRL &= ~((0x3<<10)|(0x3<<8));
	PXP->PS_SCALE = 0x10001000;

	as_cfg.bufferAddr =(uint32_t)bits;
	as_cfg.pitchBytes =width_bytes;
	as_cfg.pixelFormat =pixelFormat;
	PXP_SetAlphaSurfaceBufferConfig(PXP, &as_cfg);

	const pxp_as_blend_config_t asBlendConfig = {.alpha = 0U,          /* Don't care. */
	                                             .invertAlpha = false, /* Don't care. */
	                                             .alphaMode = kPXP_AlphaEmbedded,
	                                             .ropMode = kPXP_RopMaskAs};
	PXP_SetAlphaSurfaceBlendConfig(PXP, &asBlendConfig);
   // PXP_SetAlphaSurfacePosition(PXP, 0, 0, w, h);
	PXP->OUT_AS_ULC =((0)<<16)|(0);
	PXP->OUT_AS_LRC =((w-1)<<16)|(h-1);

    PXP_EnableAlphaSurfaceOverlayColorKey(PXP,FALSE);

	//out_cfg.pixelFormat =kPXP_OutputPixelFormatRGB565;
	out_cfg.width =w;
	out_cfg.height =h;
	out_cfg.pitchBytes =pSurf->WidthBytes;
	//out_cfg.buffer0Addr =(uint32_t)gdev_16bpp_set_addr(pSurf,x,y);
	out_cfg.buffer1Addr =(uint32_t)0;
	out_cfg.interlacedMode =kPXP_OutputProgressive;
	PXP_SetOutputBufferConfig(PXP,&out_cfg);

	PXP_Execu();
	PXP_WaitDone((uint32_t*)out_cfg.buffer0Addr,out_cfg.pitchBytes*out_cfg.height);

	return TRUE;

}



int	PXP_StretchBlt_SRCCOPY(
const SURFACE *dstSurf,int dst_x,int dst_y,int dst_w,int dst_h,
const SURFACE *srcSurf,int src_x,int src_y,int src_w,int src_h)
{
	pxp_ps_buffer_config_t ps_cfg;
	pxp_output_buffer_config_t out_cfg;

	switch(dstSurf->Format)
	{

	case SURF_RGB565:
		out_cfg.pixelFormat =kPXP_OutputPixelFormatRGB565;
		out_cfg.buffer0Addr =(uint32_t)dstSurf->GL->SetPos(dstSurf,dst_x,dst_y);
		break;

	case SURF_XRGB8888:
		out_cfg.pixelFormat =kPXP_OutputPixelFormatRGB888;
		out_cfg.buffer0Addr =(uint32_t)dstSurf->GL->SetPos(dstSurf,dst_x,dst_y);
		break;

	case SURF_ARGB4444:
		out_cfg.pixelFormat =kPXP_OutputPixelFormatARGB4444;
		out_cfg.buffer0Addr =(uint32_t)dstSurf->GL->SetPos(dstSurf,dst_x,dst_y);
		break;

	case SURF_ARGB8888:
		out_cfg.pixelFormat =kPXP_OutputPixelFormatARGB8888;
		out_cfg.buffer0Addr =(uint32_t)dstSurf->GL->SetPos(dstSurf,dst_x,dst_y);
		break;

	default:
		return FALSE;

	}

	switch(srcSurf->Format)
	{

	case SURF_RGB565:
		ps_cfg.pixelFormat =kPXP_PsPixelFormatRGB565;
		ps_cfg.bufferAddr =(uint32_t)srcSurf->GL->SetPos(srcSurf,src_x,src_y);
		break;

	case SURF_XRGB8888:
		ps_cfg.pixelFormat =kPXP_PsPixelFormatRGB888;
		ps_cfg.bufferAddr =(uint32_t)srcSurf->GL->SetPos(srcSurf,src_x,src_y);
		break;

	case SURF_ARGB4444:
	case SURF_ARGB8888:

	default:
		return FALSE;

	}



	PXP_WaitRdy();

 	//ps_cfg.pixelFormat =kPXP_PsPixelFormatRGB565;
	//ps_cfg.bufferAddr  =(uint32_t)bits;
	ps_cfg.pitchBytes  =srcSurf->WidthBytes;
	ps_cfg.swapByte =FALSE;
	PXP_SetProcessSurfaceBufferConfig(PXP,&ps_cfg);

	PXP_SetProcessSurfaceBackGroundColor(PXP,0x000000);
	PXP_SetProcessSurfacePosition(PXP,0,0,dst_w-1,dst_h-1);
	PXP_SetProcessSurfaceScaler(PXP,src_w,src_h,dst_w,dst_h);
	PXP_SetAlphaSurfacePosition(PXP, 0, 0, 0, 0);

	//out_cfg.pixelFormat =kPXP_OutputPixelFormatRGB565;
	out_cfg.width =dst_w;
	out_cfg.height =dst_h;
	out_cfg.pitchBytes =dstSurf->WidthBytes;
	//out_cfg.buffer0Addr =(uint32_t)gdev_16bpp_set_addr(pSurf,x,y);
	out_cfg.buffer1Addr =(uint32_t)0;
	out_cfg.interlacedMode =kPXP_OutputProgressive;
	PXP_SetOutputBufferConfig(PXP,&out_cfg);

	PXP_Execu();
	PXP_WaitDone((uint32_t*)out_cfg.buffer0Addr,out_cfg.pitchBytes*out_cfg.height);

	return TRUE;

}

BOOL	PXP_ScaleBitmap(const SURFACE *pSurf,int x,int y,int w,int h,const BITMAP *bm)
{
	pxp_ps_buffer_config_t ps_cfg;
	pxp_output_buffer_config_t out_cfg;
	int dst_w,dst_h;
	int src_w,src_h;

//	if((u32)bm->Bits < SDRAM_BASE)
//	{
//		return FALSE;
//	}

	if( (w*h) < (32*32))
	{
		return FALSE;
	}

	switch(pSurf->Format)
	{

	case SURF_RGB565:
		out_cfg.pixelFormat =kPXP_OutputPixelFormatRGB565;
		out_cfg.buffer0Addr =(uint32_t)pSurf->GL->SetPos(pSurf,x,y);
		break;

	case SURF_XRGB8888:
		out_cfg.pixelFormat =kPXP_OutputPixelFormatRGB888;
		out_cfg.buffer0Addr =(uint32_t)pSurf->GL->SetPos(pSurf,x,y);
		break;

	case SURF_ARGB4444:
		out_cfg.pixelFormat =kPXP_OutputPixelFormatARGB4444;
		out_cfg.buffer0Addr =(uint32_t)pSurf->GL->SetPos(pSurf,x,y);
		break;

	case SURF_ARGB8888:
		out_cfg.pixelFormat =kPXP_OutputPixelFormatARGB8888;
		out_cfg.buffer0Addr =(uint32_t)pSurf->GL->SetPos(pSurf,x,y);
		break;

	default:
		return FALSE;

	}

	switch(bm->Format)
	{

	case BM_RGB565:
		ps_cfg.pixelFormat =kPXP_PsPixelFormatRGB565;
		ps_cfg.bufferAddr =(uint32_t)bm->Bits;
		break;

	case BM_XRGB8888:
		ps_cfg.pixelFormat =kPXP_PsPixelFormatRGB888;
		ps_cfg.bufferAddr =(uint32_t)bm->Bits;
		break;

	case BM_ARGB4444:
	case BM_ARGB8888:

	default:
		return FALSE;

	}

	dst_w =w;
	dst_h =h;
	src_w =bm->Width;
	src_h =bm->Height;
	PXP_WaitRdy();

 	//ps_cfg.pixelFormat =kPXP_PsPixelFormatRGB565;
	//ps_cfg.bufferAddr  =(uint32_t)bits;
	ps_cfg.pitchBytes  =bm->WidthBytes;
	ps_cfg.swapByte =FALSE;
	PXP_SetProcessSurfaceBufferConfig(PXP,&ps_cfg);

	PXP_SetProcessSurfaceBackGroundColor(PXP,0x000000);
	PXP_SetProcessSurfacePosition(PXP,0,0,dst_w-1,dst_h-1);
	PXP_SetProcessSurfaceScaler(PXP,src_w,src_h,dst_w,dst_h);

	PXP_SetAlphaSurfacePosition(PXP, 0, 0, 0, 0);

	//out_cfg.pixelFormat =kPXP_OutputPixelFormatRGB565;
	out_cfg.width =dst_w;
	out_cfg.height =dst_h;
	out_cfg.pitchBytes =pSurf->WidthBytes;
	//out_cfg.buffer0Addr =(uint32_t)gdev_16bpp_set_addr(pSurf,x,y);
	out_cfg.buffer1Addr =(uint32_t)0;
	out_cfg.interlacedMode =kPXP_OutputProgressive;
	PXP_SetOutputBufferConfig(PXP,&out_cfg);

	PXP_Execu();
	PXP_WaitDone((uint32_t*)out_cfg.buffer0Addr,out_cfg.pitchBytes*out_cfg.height);

	return TRUE;

}


/*=========================================================================================*/

BOOL	PXP_draw_bitmap_RGB_Rotate(const SURFACE *pSurf,int x,int y,int w,int h,int width_bytes,const U8 *bits,pxp_ps_pixel_format_t pixelFormat)
{
	pxp_ps_buffer_config_t ps_cfg;
	pxp_output_buffer_config_t out_cfg;
	int dst_w,dst_h;
	int src_w,src_h;

//	if((u32)bits < SDRAM_BASE)
//	{
//		return FALSE;
//	}

	if( (w*h) < (128*128))
	{
		return FALSE;
	}

	switch(pSurf->Format)
	{

	case SURF_RGB565:
		out_cfg.pixelFormat =kPXP_OutputPixelFormatRGB565;
		out_cfg.buffer0Addr =(uint32_t)pSurf->GL->SetPos(pSurf,x,y);
		break;

	case SURF_XRGB8888:
		out_cfg.pixelFormat =kPXP_OutputPixelFormatRGB888;
		out_cfg.buffer0Addr =(uint32_t)pSurf->GL->SetPos(pSurf,x,y);
		break;

	case SURF_ARGB4444:
		out_cfg.pixelFormat =kPXP_OutputPixelFormatARGB4444;
		out_cfg.buffer0Addr =(uint32_t)pSurf->GL->SetPos(pSurf,x,y);
		break;

	case SURF_ARGB8888:
		out_cfg.pixelFormat =kPXP_OutputPixelFormatARGB8888;
		out_cfg.buffer0Addr =(uint32_t)pSurf->GL->SetPos(pSurf,x,y);
		break;

	default:
		return FALSE;

	}

	ps_cfg.pixelFormat =pixelFormat;
	ps_cfg.bufferAddr =(uint32_t)bits;

	dst_w =w;
	dst_h =h;
	src_w =w;
	src_h =h;
	PXP_WaitRdy();

 	//ps_cfg.pixelFormat =kPXP_PsPixelFormatRGB565;
	//ps_cfg.bufferAddr  =(uint32_t)bits;
	ps_cfg.pitchBytes  =width_bytes;
	ps_cfg.swapByte =FALSE;
	PXP_SetProcessSurfaceBufferConfig(PXP,&ps_cfg);

	PXP_SetProcessSurfaceBackGroundColor(PXP,0x000000);
	PXP_SetProcessSurfacePosition(PXP,0,0,dst_w-1,dst_h-1);
	PXP_SetProcessSurfaceScaler(PXP,src_w,src_h,dst_w,dst_h);
	PXP_SetAlphaSurfacePosition(PXP, 0, 0, 0, 0);

	//out_cfg.pixelFormat =kPXP_OutputPixelFormatRGB565;
	out_cfg.width =dst_w;
	out_cfg.height =dst_h;
	out_cfg.pitchBytes =pSurf->WidthBytes;
	//out_cfg.buffer0Addr =(uint32_t)gdev_16bpp_set_addr(pSurf,x,y);
	out_cfg.buffer1Addr =(uint32_t)0;
	out_cfg.interlacedMode =kPXP_OutputProgressive;
	PXP_SetOutputBufferConfig(PXP,&out_cfg);

	if(1)
	{
	volatile int pos;
	volatile int ro;
	volatile int filp;

	pos =kPXP_RotateOutputBuffer;
	ro =kPXP_Rotate90;
	filp =kPXP_FlipDisable;

	PXP_SetRotateConfig(PXP,pos,ro,filp);
	}

	PXP_Execu();
	PXP_WaitDone((uint32_t*)out_cfg.buffer0Addr,out_cfg.pitchBytes*out_cfg.height);

	return TRUE;

}

/*=========================================================================================*/

extern u8 *lcd_frame_buf;
//extern SURFACE	surf_screen;


void PXP_Test_ARGB(SURFACE *surf_screen)
{
	SURFACE *pSurf;
	HDC hdc,hdc_mem;
	RECT rc;
	u32 c;

	while(1)
	{
	rc.x=0;
	rc.y=0;
	rc.w =200;
	rc.h =150;

	hdc =GetDC(NULL);

	pSurf =CreateSurface(SURF_ARGB4444,rc.w,rc.h,-1,NULL);
	hdc_mem =CreateDC(pSurf,NULL);

	SetTextColor(hdc_mem,MapARGB(hdc_mem,255,250,10,10));
	SetPenColor(hdc_mem,MapARGB(hdc_mem,200,250,250,250));
	c =ARGB8888(160,250,250,250);
	SetBrushColor(hdc_mem,MapARGB8888(hdc_mem,c));
	//SetBrushColor(hdc_mem,c);
	DrawText(hdc_mem,L"ARGB",-1,&rc,DT_VCENTER|DT_CENTER|DT_BORDER|DT_BKGND);

	BitBlt(hdc,10,20,rc.w,rc.h,hdc_mem,0,0,SRCCOPY);


	PXP_draw_bitmap_ARGB(surf_screen,30,50,rc.w,rc.h,pSurf->WidthBytes,pSurf->Bits,kPXP_AsPixelFormatARGB4444);
	PXP_draw_bitmap_ARGB(surf_screen,70,90,rc.w,rc.h,pSurf->WidthBytes,pSurf->Bits,kPXP_AsPixelFormatARGB4444);

	DeleteDC(hdc_mem);
	DeleteSurface(pSurf);
	ReleaseDC(NULL,hdc);


		GUI_msleep(100);
		GUI_msleep(100);
	}

}

extern SURFACE	SurfSereen;

void PXP_Test(void)
{
	pxp_as_buffer_config_t as_cfg;
	pxp_ps_buffer_config_t ps_cfg;
	pxp_output_buffer_config_t out_cfg;

	SURFACE *pSurf;
	HDC hdc_mem;
	RECT rc;
	volatile int frame,t0,t1;

	return;

	PXP_DrvInit();
	PXP_Test_ARGB(&SurfSereen);

	pSurf =CreateSurface(SURF_RGB565,320,240,-1,NULL);
	hdc_mem =CreateDC(pSurf,NULL);

	ClrDisplay(hdc_mem,NULL,MapARGB(hdc_mem,100,250,250,250));
	//ClrDisplay(hdc_mem,NULL,ARGB8888(80,250,250,250));
	rc.x =0;
	rc.y =0;
	rc.w =320;
	rc.h =240;

	SetPenColor(hdc_mem,MapRGB(hdc_mem,250,0,0));
	DrawRect(hdc_mem,&rc);

	SetTextColor(hdc_mem,MapRGB(hdc_mem,250,0,0));
	TextOut(hdc_mem,10,20,L"PXP Test: 320x240 Scale to 800x480",-1);

	SetTextColor(hdc_mem,MapRGB(hdc_mem,0,0,250));
	TextOut(hdc_mem,10,40,L"PXP Test Scale - 2",-1);

#if 1
	PXP_DrvInit();

	SCB_CleanInvalidateDCache_by_Addr((uint32_t*)pSurf->Bits,pSurf->WidthBytes*pSurf->Height);


#if 0
    as_cfg.pixelFormat =kPXP_AsPixelFormatRGB565;
    as_cfg.bufferAddr  =(uint32_t)pSurf->Bits;
    as_cfg.pitchBytes  =pSurf->WidthBytes;
    PXP_SetAlphaSurfaceBufferConfig(PXP,&as_cfg);
#endif

#if 0
 	ps_cfg.pixelFormat =kPXP_PsPixelFormatRGB565;
	ps_cfg.bufferAddr  =(uint32_t)pSurf->Bits;
	ps_cfg.pitchBytes  =pSurf->WidthBytes;
	ps_cfg.swapByte =FALSE;
	PXP_SetProcessSurfaceBufferConfig(PXP,&ps_cfg);
	PXP_SetProcessSurfacePosition(PXP,0,0,800,480);
	PXP_SetProcessSurfaceScaler(PXP,320,240,800,480);
	PXP_SetProcessSurfaceBackGroundColor(PXP,0x0000000);

	out_cfg.pixelFormat =kPXP_OutputPixelFormatRGB565;
	out_cfg.width =800;
	out_cfg.height =480;
	out_cfg.pitchBytes =LCD_XSIZE*2;
	out_cfg.buffer0Addr =(uint32_t)lcd_frame_buf;
	out_cfg.buffer1Addr =(uint32_t)0;
	out_cfg.interlacedMode =kPXP_OutputProgressive;
	PXP_SetOutputBufferConfig(PXP,&out_cfg);

	if(0)
	{
		PXP_Type *pxp =PXP;
		pxp->OUT_CTRL &= ~(1<<23);
	}
#endif

	frame=0;
	t0 =GUI_GetTickCount();
	while(1)
	{
//		PXP_fill_rect(&surf_screen,10,20,256,128,RGB888(250,0,0));
//		PXP_draw_bitmap_RGB_Rotate(surf_screen,20,50,320,240,pSurf->WidthBytes,pSurf->Bits,kPXP_AsPixelFormatRGB565);
		//PXP_draw_bitmap_ARGB(&surf_screen,20,50,320,240,pSurf->WidthBytes,pSurf->Bits,kPXP_AsPixelFormatARGB8888);
		frame++;

		t1 =GUI_GetTickCount();
		if((t1-t0)>1000)
		{
			t0 =t1;
			frame=0;
		}

	}
#endif

}

/*=========================================================================================*/

/*=========================================================================================*/
