
#include <stdio.h>
#include "emXGUI.h"
#include "x_libc.h"
#include "GUI_AppDef.h"
#include "emxgui_png.h"
#include "gui_font_port.h"


/**********************�ֽ���*********************/

HWND GUI_Boot_hwnd;
/* ����ؼ�ID */
enum eID
{
  ID_LOGO,
  ID_TEXT1,
  ID_TEXT2,
  ID_PROGBAR,
};
/* �ⲿͼƬ���� */
extern char bootlogo[];
/* �ⲿͼƬ���ݴ�С */
extern unsigned int bootlogo_size(void);
HWND Boot_progbar = NULL;

/**
  * @brief  ������Դ�߳�
  */
static void App_Load_Res(void )
{
  static int thread=0;
  static HANDLE h_load;

  if(thread==0)
  { 
    /* �����߳������Լ� */
    h_load = GUI_Thread_Create((void(*)(void*))App_Load_Res,  /* ������ں��� */
                                    "Load Res",/* �������� */
                                    5*1024,  /* ����ջ��С */
                                    NULL, /* ������ں������� */
                                    1,    /* ��������ȼ� */
                                    10); /* ����ʱ��Ƭ����������֧�� */
    thread =1;

    return;
  }
  while(thread) //�߳��Ѵ�����
  {     
    HFONT hFont;
 
    /* �������嵽�ⲿSDRAM������defaultFont */    
    hFont = GUI_Init_Extern_Font();
    if(hFont==NULL)
    {
      GUI_ERROR("GUI Extern Default Font Init Failed.");

      Load_state = FALSE;
    }
    else
    {   
      Load_state = TRUE;
      /* ����Ĭ������ */
      GUI_SetDefFont(hFont);  
    }    
    
    //����Ϣ���������ڣ��ر�
    SendMessage(GUI_Boot_hwnd,WM_CLOSE,0,0);
    thread = 0;       

    GUI_Thread_Delete(h_load);

  }
  return;
}

/**
  * @brief  ��������ص�����
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
      RECT rc;

      GetClientRect(hwnd,&rc); //��ô��ڵĿͻ�������

      /* ����ͼƬ���ݴ���PNG_DEC��� */
      png_dec = PNG_Open((u8 *)bootlogo, bootlogo_size());
      /* ��ͼƬת����bitmap */
      PNG_GetBitmap(png_dec, &png_bm);
      CreateWindow(TEXTBOX, L"emXGUI booting", WS_VISIBLE, 
                    0,260,800,40,
                    hwnd, ID_TEXT1, NULL, NULL);
      SendMessage(GetDlgItem(hwnd, ID_TEXT1),TBM_SET_TEXTFLAG,0,
                    DT_SINGLELINE|DT_CENTER|DT_VCENTER|DT_BKGND); 

      CreateWindow(TEXTBOX, L"Copying FontLIB form SPIFALSH to SDRAM", WS_VISIBLE, 
                    0,300,800,40,
                    hwnd, ID_TEXT2, NULL, NULL);
      SendMessage(GetDlgItem(hwnd, ID_TEXT2),TBM_SET_TEXTFLAG,0,
                    DT_SINGLELINE|DT_CENTER|DT_VCENTER|DT_BKGND); 


      //PROGRESSBAR_CFG�ṹ��Ĵ�С
      cfg.cbSize	 = sizeof(PROGRESSBAR_CFG);
      //�������еĹ���
      cfg.fMask    = PB_CFG_ALL;
      //���ָ�ʽˮƽ����ֱ����
      cfg.TextFlag = DT_VCENTER|DT_CENTER;  

      Boot_progbar = CreateWindow(PROGRESSBAR,L"Loading",
                                     PBS_TEXT|PBS_ALIGN_LEFT|WS_VISIBLE,
                                    50, 380, 700, 40 ,hwnd,ID_PROGBAR,NULL,NULL);

      SendMessage(Boot_progbar,PBM_GET_CFG,TRUE,(LPARAM)&cfg);
      SendMessage(Boot_progbar,PBM_SET_CFG,TRUE,(LPARAM)&cfg);
      SendMessage(Boot_progbar,PBM_SET_RANGLE,TRUE, FONT_NUM);
      SendMessage(Boot_progbar,PBM_SET_VALUE,TRUE,0); 
      SetTimer(hwnd, 1, 20, TMR_SINGLE|TMR_START, NULL);
      
      break;
    }
    
    case WM_TIMER:
    {
      /* �������洴����timerʱ���ſ�ʼ���� */
      App_Load_Res();
      break;         
    }
    case WM_ERASEBKGND:
    {
      HDC hdc =(HDC)wParam;
      RECT rc =*(RECT*)lParam;

      SetBrushColor(hdc, MapRGB(hdc, 0, 0, 0));
      FillRect(hdc, &rc);           
      /* ��ʾͼƬ */
      DrawBitmap(hdc, 250, 80, &png_bm, NULL);  
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
        cr->TextColor =RGB888(255,255,255);//������ɫ��RGB888��ɫ��ʽ)
        cr->BackColor =RGB888(0,0,0);//������ɫ��RGB888��ɫ��ʽ)
        //cr->BorderColor =RGB888(255,10,10);//�߿���ɫ��RGB888��ɫ��ʽ)
        return TRUE;
      }

      break;
    }  
    case WM_CLOSE: //��������ʱ�����Զ���������Ϣ����������һЩ��Դ�ͷŵĲ���.
    {
      /* �ر�PNG_DEC��� */
      PNG_Close(png_dec);
      DestroyWindow(hwnd); 
      Boot_progbar = NULL;
      return TRUE; //����PostQuitMessage��ʹ�������ڽ������˳���Ϣѭ��.
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
  
  /* ��Ĭ������ΪASCII �ڲ�flash�ֿ⣬��ֹ���� */
  GUI_SetDefFont(defaultFontEn);  

  wcex.Tag 		    = WNDCLASS_TAG;

  wcex.Style			= CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc	= win_proc;
  wcex.cbClsExtra		= 0;
  wcex.cbWndExtra		= 0;
  wcex.hInstance		= NULL;//hInst;
  wcex.hIcon			= NULL;
  wcex.hCursor		= NULL;//LoadCursor(NULL, IDC_ARROW);

  //����������ʾ
  GUI_Boot_hwnd = CreateWindowEx(	WS_EX_LOCKPOS|WS_EX_FRAMEBUFFER,
                              &wcex,
                              L"Booting",
                              WS_VISIBLE|WS_CLIPCHILDREN|WS_OVERLAPPED,
                              0,0,GUI_XSIZE,GUI_YSIZE,
                              NULL,0,NULL,NULL);


  //��ʾ����.
  ShowWindow(GUI_Boot_hwnd,SW_SHOW);

  while(GetMessage(&msg,GUI_Boot_hwnd))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  
  /* ���������ڼ�������Դ���رգ�ִ�����´��룬����Ӧ���߳� */
//  {   
    res_not_found_flag = TRUE;  
     if(res_not_found_flag)
     {
        GUI_INFO("�ⲿSPI FLASHȱ����Դ��������ʼ��¼��Դ����...");

        /* ���Ҳ�����Դ��������Դ��¼Ӧ�� */      
        GUI_Thread_Create(GUI_RES_Writer_Dialog,  /* ������ں��� */
                              "GUI_FLASH_WRITER",/* �������� */
                              8*1024,  /* ����ջ��С */
                              NULL, /* ������ں������� */
                              5,    /* ��������ȼ� */
                              10); /* ����ʱ��Ƭ����������֧�� */


     }
//     else
//     {	
//        /* �ҵ���Դ��������Ӧ��*/ 
//     
//        h=rt_thread_create("GUI_APP",GUI_Board_App_Desktop,NULL,8*1024,5,5);
//        rt_thread_startup(h);			
//        h=rt_thread_create("GUI_SLIDE_WIN",GUI_DEMO_SlideWindow,NULL,4096,5,5);
//        rt_thread_startup(h);
//     }   
//  } 


}