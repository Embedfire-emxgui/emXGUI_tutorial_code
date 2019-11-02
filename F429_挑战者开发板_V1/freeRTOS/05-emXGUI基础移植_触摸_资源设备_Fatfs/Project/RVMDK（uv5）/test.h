#ifndef __TEST_H__
#define __TEST_H__

#include "emXGUI.h"

#define ID_EXIT 0x1000
#define ID_TEXT 0x1001
#define ID_TEXT_SON 0x1002
#define ID_TMR1 0x1003
#define ID_PROGRESSBAR 0x1004
#define ID_SCROLLBAR1 0x1005
static int count = 0;
static int prority =5;

void	GUI_Boot_Interface_Dialog(void *param);
static 	 LRESULT  	desktop_proc2(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
#endif
