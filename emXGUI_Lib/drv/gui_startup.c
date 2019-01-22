
#include <string.h>
#include "gui_drv.h"


/*============================================================================*/
extern BOOL	GUI_Arch_Init(void);
extern void GUI_DesktopStartup(void);

static BOOL GUI_LowLevelInit(void);



/**
  * @brief  GUI低级别的初始化,这是GUI的第一个初始化函数
  * @param  无
  * @retval TRUE:成功; FALSE：失败.
  */
static BOOL GUI_LowLevelInit(void)
{

  //GUI Core内存管理初始化
  GUI_MEM_Init();

#if(GUI_VMEM_EN)    
   //vmem内存管理初始化
	GUI_VMEM_Init();
#endif  
  
  //初始化日志接口
  if(GUI_Log_Init() != TRUE)
  {
  
  }
    
  /* 直接返回TRUE，为了部分设备初始化不正常不影响后续运行 */
	return TRUE;
}

/**
  * @brief  启动GUI，包含各种内存、液晶、输入设备的初始化
  * @param  无
  * @retval 无
  */
void	GUI_Startup(void)
{
	SURFACE *pSurf=NULL;
	HFONT hFont=NULL;

	if(!GUI_LowLevelInit()) //GUI低级初始化.
	{
    GUI_ERROR("GUI_LowLevelInit Failed.");
		return;
	}

	if(!GUI_Arch_Init())   //GUI架构适配层初始化.
	{
    GUI_ERROR("GUI_Arch_Init Failed.");
		return;
	}

	if(!X_GUI_Init())	   //GUI内核初始化.
	{
    GUI_ERROR("X_GUI_Init Failed.");
		return;
	}
  
	pSurf =GUI_DisplayInit(); //显示设备初始化
	if(pSurf==NULL)
	{
    GUI_ERROR("GUI_DisplayInit Failed.");
		return;
	}
	GUI_SetScreenSurface(pSurf); //设置屏幕Surface对象
  
#if(GUI_RES_DEV_EN)  
   //资源设备初始化（FLASH）
  if(RES_DevInit() != TRUE)
  {
    GUI_ERROR("RES_DevInit Failed.");
  }
#endif   

#if(GUI_INPUT_DEV_EN)    
  //初始化输入设备
  if(GUI_InputInit() != TRUE)
  {
    GUI_ERROR("GUI_InputInit Failed.");
  } 

	GL_CursorInit(pSurf,pSurf->Width>>1,pSurf->Height>>1); //初始化光标
#endif
  
	hFont =GUI_Default_FontInit(); //初始化默认的字体
	if(hFont==NULL)
	{
    GUI_ERROR("GUI_Default_FontInit Failed.");
		return;
	}
	GUI_SetDefFont(hFont);  //设置默认的字体

	GUI_DesktopStartup();	//启动桌面窗口(该函数不会返回).

}

/********************************END OF FILE****************************/

