#include "test.h"

extern void	Text_Create(void *param);

static 	 LRESULT  	desktop_proc2(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
    /* 桌面创建时,会产生该消息,可以在这里做一些初始化工作. */
		case	WM_CREATE:
	{
		/* 获取主窗口矩形. */
		RECT rc;
		HWND wnd;
		GetClientRect(hwnd,&rc);
		
		/* 创建退出按钮. */
		CreateWindow(BUTTON, L"EXIT", WS_VISIBLE,rc.x,rc.y, 100, 40, hwnd, ID_EXIT, NULL, NULL);//退出按钮
		/* 创建创建文本框按钮. */
		CreateWindow(BUTTON, L"TEXT", WS_VISIBLE,rc.x+200,rc.y, 100, 40, hwnd, ID_TEXT, NULL, NULL);//创建文本框按钮
		
		/* 创建进度条. */
		PROGRESSBAR_CFG Pcfg;
		Pcfg.cbSize = sizeof(PROGRESSBAR_CFG);
		Pcfg.Rangle = 100;
		Pcfg.Value = 0;
		Pcfg.fMask    = PB_CFG_ALL;
		
		wnd = CreateWindow(PROGRESSBAR, L"PROGRESSBAR",WS_VISIBLE| PBS_FLAT|PBS_ALIGN_BOTTOM,rc.x+200,rc.y+40, 20, 200, hwnd, ID_PROGRESSBAR, NULL, NULL);//进度条

		SendMessage(wnd,PBM_GET_CFG,TRUE,(LPARAM)&Pcfg);		
		
		/* 创建滚动条. */
		SCROLLINFO Scfg;
		Scfg.cbSize = sizeof(Scfg);
		Scfg.fMask =SIF_ALL;
		Scfg.nMin = 0;
		Scfg.nMax = 100;
		Scfg.nValue = 50;
		Scfg.TrackSize = 30;
		Scfg.ArrowSize = 30;

		wnd = CreateWindow(SCROLLBAR,L"VScroll",SBS_HORZ|WS_VISIBLE,\
                              0,240,200,30,hwnd,ID_SCROLLBAR1,NULL,NULL);
    SendMessage(wnd,SBM_SETSCROLLINFO,TRUE,(LPARAM)&Scfg);
		
		/* 创建定时器. */
		SetTimer(hwnd,ID_TMR1,1000,TMR_START,NULL);//延时1S
		
		printf("子窗口被创建了!\r\n");
	}
			break;

		/* 窗口重绘 */
		case	WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc;
			RECT rc;//窗口大小
      GetClientRect(hwnd, &rc); //获得客户区矩形.
      hdc = BeginPaint(hwnd, &ps);
      //背景
      SetBrushColor(hdc, MapRGB(hdc, 255,255,255));
      FillRect(hdc, &rc); 
			EndPaint(hwnd,&ps);
			return TRUE;
		}
		
		case WM_TIMER:
		{
		  uint16_t id;
			id = LOWORD(wParam);
			if(id == ID_TMR1 && GetDlgItem(hwnd,ID_TEXT_SON)!= NULL)
			{
				HWND wnd;
				WCHAR wbuf[20];
				count++;
				x_wsprintf(wbuf,L"%d",count);
				wnd =GetDlgItem(hwnd,ID_TEXT_SON);//获取文本窗口句柄
				SetWindowText(wnd,wbuf);//设置文本显示
			}
			if(id == ID_TMR1 && GetDlgItem(hwnd,ID_PROGRESSBAR)!= NULL)
			{
				HWND wnd;
				wnd =GetDlgItem(hwnd,ID_PROGRESSBAR);//获取进度条句柄
				if(count <= 100)
				{
				  SendMessage(wnd,PBM_SET_VALUE,TRUE,count);
				}
			}
		}
        
     /* 消息处理 */    
    case WM_NOTIFY:
		{
      uint16_t code,id;
			
			id   = LOWORD(wParam);
			code = HIWORD(wParam);
			
			if(code == BN_CLICKED && id == ID_EXIT )
			{
				int ret;
				const WCHAR *btn[] ={L"YES",L"NO",};
				/* 创建对话框. */
    		MSGBOX_OPTIONS cfg;
    		cfg.ButtonCount = 2;
				cfg.pButtonText =btn;
	    	cfg.Flag = MB_ICONQUESTION | MB_BTN_WIDTH(80);
				
				ret=MessageBox(hwnd,10,20,320,150,L"CLOSE WINDOW?",L"MsgBox",&cfg);
				if(ret == 0)
				{
					PostCloseMessage(hwnd);
				}
			}
			
			if(code == BN_CLICKED && id == ID_TEXT )//创建一个文本框测试
			{
//		    PAINTSTRUCT ps;
//	    	HDC hdc;
		    RECT rc;//窗口大小
        GetClientRect(hwnd, &rc); //获得客户区矩形.
			  CreateWindow(TEXTBOX, L"TEXT1", WS_VISIBLE,rc.x,rc.y+40, 200, 200, hwnd, ID_TEXT_SON, NULL, NULL);
				printf("文本窗口被创建了!\r\n");
			}
		}
		break;

    /* 客户区背景需要被擦除 */
		case	WM_ERASEBKGND:
		{   
      RECT rc = *(RECT*)lParam;
			HDC hdc =(HDC)wParam; 
      
        /* 字体资源加载完成后才显示正常界面，刚开始时只显示纯色 */
       if(TRUE)
       {
          //_EraseBackgnd(hdc,NULL,hwnd);
       }
       else
       {
          SetBrushColor(hdc, MapRGB(hdc, 138, 255, 0));
          FillRect(hdc, &rc);
       }
		}
		return TRUE;  
	
		case WM_CLOSE:
 {
   DestroyWindow(hwnd); //??DestroyWindow???????(??????WM_DESTROY??)?
   return TRUE; 
 }
    /* 用户不关心的信息，由系统处理 */
		default:
				return	DefDesktopProc(hwnd,msg,wParam,lParam);
	}

	return WM_NULL;

}

void	GUI_Boot_Interface_Dialog(void *param)
{
		HWND hwndhandle;
    WNDCLASS	wcex;
		MSG msg;

		wcex.Tag 		    = WNDCLASS_TAG;
		wcex.Style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= desktop_proc2;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= NULL;//hInst;
		wcex.hIcon			= NULL;
		wcex.hCursor		= NULL;//LoadCursor(NULL, IDC_ARROW);

//  GUI_DEBUG("Create desktop");
	//创建桌面窗口.
	
  	hwndhandle = CreateWindowEx(	//WS_EX_LOCKPOS
	                            NULL,
                              &wcex,
                              _T("This is a son Window!"),
                              WS_CAPTION|WS_DLGFRAME|WS_BORDER|WS_CLIPCHILDREN,
                              10,10,300,300,
                              NULL,0,NULL,NULL);

	//GUI_DEBUG("HWND_Desktop=%08XH\r\n",	hwnd);

	//显示桌面窗口.
	ShowWindow(hwndhandle,SW_SHOW);
#if (GUI_SHOW_CURSOR_EN)
	//设置系统打开光标显示(可以按实际情况看是否需要).
	ShowCursor(TRUE);
#endif

  while(GetMessage(&msg,hwndhandle))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
	GUI_Thread_Delete(GUI_GetCurThreadHandle());
}

