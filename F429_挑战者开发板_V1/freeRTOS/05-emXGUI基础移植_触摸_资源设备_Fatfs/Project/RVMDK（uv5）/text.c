#include "text.h"

static 	 LRESULT  	Text_proc2(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	return TRUE;
}

void	Text_Create(void *param)
{
    HWND hwnd;
    WNDCLASS	wcex;
		MSG msg;

		wcex.Tag 		    = WNDCLASS_TAG;
		wcex.Style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= Text_proc2;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= NULL;//hInst;
		wcex.hIcon			= NULL;
		wcex.hCursor		= NULL;//LoadCursor(NULL, IDC_ARROW);

		RECT rc;//窗口大小
    GetClientRect(hwnd, &rc); //获得客户区矩形.
//  GUI_DEBUG("Create desktop");
	//创建桌面窗口.
  	hwnd = CreateWindowEx(	//WS_EX_LOCKPOS
	                            NULL,
                              &wcex,
                              _T("TEXT Window!"),
                              WS_CAPTION|WS_DLGFRAME|WS_BORDER|WS_CLIPCHILDREN,
                              10,10,300,300,
                              NULL,0,NULL,NULL);

	//GUI_DEBUG("HWND_Desktop=%08XH\r\n",	hwnd);

	//显示桌面窗口.
	ShowWindow(hwnd,SW_SHOW);
#if (GUI_SHOW_CURSOR_EN)
	//设置系统打开光标显示(可以按实际情况看是否需要).
	ShowCursor(TRUE);
#endif

  while(GetMessage(&msg,hwnd))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
	GUI_Thread_Delete(GUI_GetCurThreadHandle());
}
