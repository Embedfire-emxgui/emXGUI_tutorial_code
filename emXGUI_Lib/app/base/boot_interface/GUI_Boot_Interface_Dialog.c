
#include <stdio.h>
#include "emXGUI.h"
#include "x_libc.h"
#include "GUI_AppDef.h"
#include "emxgui_png.h"
#include "gui_font_port.h"


/**********************分界线*********************/

HWND GUI_Boot_hwnd;
/* 各类控件ID */
enum eID
{
  ID_LOGO,
  ID_TEXT1,
  ID_TEXT2,
  ID_PROGBAR,
};
/* 外部图片数据 */
extern char bootlogo[];
/* 外部图片数据大小 */
extern unsigned int bootlogo_size(void);
HWND Boot_progbar = NULL;

/**
  * @brief  加载资源线程
  */
static void App_Load_Res(void )
{
  static int thread=0;

  if(thread==0)
  { 
    /* 创建线程运行自己 */
    GUI_Thread_Create((void(*)(void*))App_Load_Res,  /* 任务入口函数 */
                        "Load Res",/* 任务名字 */
                        5*1024,  /* 任务栈大小 */
                        NULL, /* 任务入口函数参数 */
                        1,    /* 任务的优先级 */
                        10); /* 任务时间片，部分任务不支持 */
    thread =1;
    return;
  }
  while(thread) //线程已创建了
  { 
    HFONT hFont;

    /* 加载字体到外部SDRAM，返回defaultFont */    
    hFont = GUI_Init_Extern_Font();
    if(hFont==NULL)
    {
      GUI_ERROR("GUI Extern Default Font Init Failed.");

      Load_state = FALSE;
    }
    else
    {   
      Load_state = TRUE;
      /* 重设默认字体 */
      GUI_SetDefFont(hFont);  
    }    
    
    //发消息给启动窗口，关闭
    SendMessage(GUI_Boot_hwnd,WM_CLOSE,0,0);
    thread = 0;  

    /* 删除线程自己 */
    GUI_Thread_Delete(GUI_GetCurThreadHandle());
  }
  return;
}

/**
  * @brief  启动界面回调函数
  */
static	LRESULT	win_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  static  BITMAP png_bm;
  static  PNG_DEC *png_dec; 
  PROGRESSBAR_CFG cfg;
  switch (msg)
  {  
    case WM_CREATE:
    {
      RECT rc,rc0;

      GetClientRect(hwnd,&rc); //获得窗口的客户区矩形
      CopyRect(&rc0,&rc);
      
      /* 本窗口垂直分为2份 */

      /* 根据图片数据创建PNG_DEC句柄 */
      png_dec = PNG_Open((u8 *)bootlogo, bootlogo_size());
      /* 把图片转换成bitmap */
      PNG_GetBitmap(png_dec, &png_bm);
      
      rc0.x = (rc.w - png_bm.Width)/2;
      rc0.y = rc.h/2 - png_bm.Height - 10;
      rc0.w = rc.w;
//      DrawBitmap(hdc, 250, 80, &png_bm, NULL); 
      
      OffsetRect(&rc0,0,png_bm.Height);
      rc0.x = 0;
      rc0.y = rc.h/2;
      rc0.h = 30;      
      rc0.w = rc.w;

      CreateWindow(TEXTBOX, L"emXGUI booting", WS_VISIBLE, 
                    rc0.x,rc0.y,rc0.w,rc0.h,
                    hwnd, ID_TEXT1, NULL, NULL);
      SendMessage(GetDlgItem(hwnd, ID_TEXT1),TBM_SET_TEXTFLAG,0,
                    DT_SINGLELINE|DT_CENTER|DT_VCENTER|DT_BKGND); 

      OffsetRect(&rc0,0,rc0.h);

      CreateWindow(TEXTBOX, L"Copying FontLIB from SPIFLASH to SDRAM", WS_VISIBLE, 
                    rc0.x,rc0.y,rc0.w,rc0.h,
                    hwnd, ID_TEXT2, NULL, NULL);
      SendMessage(GetDlgItem(hwnd, ID_TEXT2),TBM_SET_TEXTFLAG,0,
                    DT_SINGLELINE|DT_CENTER|DT_VCENTER|DT_BKGND); 

      OffsetRect(&rc0,0,rc0.h+10);

      rc0.x = 10;
      rc0.h = 30;
      rc0.w = rc.w - 2*rc0.x;

      //PROGRESSBAR_CFG结构体的大小
      cfg.cbSize	 = sizeof(PROGRESSBAR_CFG);
      //开启所有的功能
      cfg.fMask    = PB_CFG_ALL;
      //文字格式水平，垂直居中
      cfg.TextFlag = DT_VCENTER|DT_CENTER;  

      Boot_progbar = CreateWindow(PROGRESSBAR,L"Loading",
                                     PBS_TEXT|PBS_ALIGN_LEFT|WS_VISIBLE,
                                    rc0.x,rc0.y,rc0.w,rc0.h,hwnd,ID_PROGBAR,NULL,NULL);

      SendMessage(Boot_progbar,PBM_GET_CFG,TRUE,(LPARAM)&cfg);
      SendMessage(Boot_progbar,PBM_SET_CFG,TRUE,(LPARAM)&cfg);
      SendMessage(Boot_progbar,PBM_SET_RANGLE,TRUE, FONT_NUM);
      SendMessage(Boot_progbar,PBM_SET_VALUE,TRUE,0); 
      SetTimer(hwnd, 1, 20, TMR_SINGLE|TMR_START, NULL);
      
      break;
    }
    
    case WM_TIMER:
    {
      /* 启动界面创建后timer时间后才开始加载 */
      App_Load_Res();
      break;         
    }
    case WM_ERASEBKGND:
    {
      HDC hdc =(HDC)wParam;
      RECT rc =*(RECT*)lParam;

      GetClientRect(hwnd,&rc); //获得窗口的客户区矩形

      SetBrushColor(hdc, MapRGB(hdc, 0, 0, 0));
      FillRect(hdc, &rc);    
      
      rc.x = (rc.w - png_bm.Width)/2;
      rc.y = rc.h/2 - png_bm.Height - 10;;
      /* 显示图片 */
      DrawBitmap(hdc, rc.x, rc.y, &png_bm, NULL);  
      return TRUE;

    }


    case	WM_CTLCOLOR:
    {
      u16 id;
      CTLCOLOR *cr;
      id =LOWORD(wParam);				
      cr =(CTLCOLOR*)lParam;
      if(id == ID_TEXT1 || id == ID_TEXT2)
      {
        cr->TextColor =RGB888(255,255,255);//文字颜色（RGB888颜色格式)
        cr->BackColor =RGB888(0,0,0);//背景颜色（RGB888颜色格式)
        //cr->BorderColor =RGB888(255,10,10);//边框颜色（RGB888颜色格式)
        return TRUE;
      }

      break;
    }  
    case WM_CLOSE: //窗口销毁时，会自动产生该消息，在这里做一些资源释放的操作.
    {
      /* 关闭PNG_DEC句柄 */
      PNG_Close(png_dec);
      DestroyWindow(hwnd); 
      Boot_progbar = NULL;
      return TRUE; //调用PostQuitMessage，使用主窗口结束并退出消息循环.
    }      
    default:
      return	DefWindowProc(hwnd, msg, wParam, lParam);
  }
  return	WM_NULL;                                     
}

extern void 	GUI_Board_App_Desktop(void);
extern void	GUI_RES_Writer_Dialog(void *param);
extern void	GUI_DEMO_SlideWindow(void);

void	GUI_Boot_Interface_Dialog(void *param)
{

  WNDCLASS	wcex;
  MSG msg;
  
  /* 设默认字体为ASCII 内部flash字库，防止出错 */
  GUI_SetDefFont(defaultFontEn);  

  wcex.Tag 		    = WNDCLASS_TAG;

  wcex.Style			= CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc	= win_proc;
  wcex.cbClsExtra		= 0;
  wcex.cbWndExtra		= 0;
  wcex.hInstance		= NULL;//hInst;
  wcex.hIcon			= NULL;
  wcex.hCursor		= NULL;//LoadCursor(NULL, IDC_ARROW);

  //创建启动提示
  GUI_Boot_hwnd = CreateWindowEx(	WS_EX_LOCKPOS|WS_EX_FRAMEBUFFER,
                              &wcex,
                              L"Booting",
                              WS_VISIBLE|WS_CLIPCHILDREN|WS_OVERLAPPED,
                              0,0,GUI_XSIZE,GUI_YSIZE,
                              NULL,0,NULL,NULL);


  //显示窗口.
  ShowWindow(GUI_Boot_hwnd,SW_SHOW);

  while(GetMessage(&msg,GUI_Boot_hwnd))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  /* 启动界面在加载完资源后会关闭，执行以下代码，创建应用线程 */
//  {  
#if (GUI_APP_RES_WRITER_EN )  
    /* 人为设置为TRUE，测试用 */
//    res_not_found_flag = TRUE; 
  
     if(res_not_found_flag)
     {
        GUI_INFO("外部SPI FLASH缺少资源，即将开始烧录资源内容...");

        /* 若找不到资源，进入资源烧录应用 */      
        GUI_Thread_Create(GUI_RES_Writer_Dialog,  /* 任务入口函数 */
                              "GUI_FLASH_WRITER",/* 任务名字 */
                              8*1024,  /* 任务栈大小 */
                              NULL, /* 任务入口函数参数 */
                              5,    /* 任务的优先级 */
                              10); /* 任务时间片，部分任务不支持 */


     }
#endif     
//     else
//     {	
//        /* 找到资源，正常跑应用*/ 
//     
//        h=rt_thread_create("GUI_APP",GUI_Board_App_Desktop,NULL,8*1024,5,5);
//        rt_thread_startup(h);			
//        h=rt_thread_create("GUI_SLIDE_WIN",GUI_DEMO_SlideWindow,NULL,4096,5,5);
//        rt_thread_startup(h);
//     }   
//  } 

    /* 部分操作系统在退出任务函数时，必须删除线程自己 */
    GUI_Thread_Delete(GUI_GetCurThreadHandle());

}
