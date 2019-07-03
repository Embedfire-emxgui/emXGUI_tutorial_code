

#include	"Include.h"
#include	"BSP.h"
//#include	"x_commdlg.h"

/*=========================================================================================*/

void WWDG_IRQHandler(void)
{
	volatile int i;
	i++;
	while(1);
}

void Board_OnTick(void)
{
	//lcd_backlight_ontick();
}

/*=========================================================================================*/

//void Board_HardInit(void);
//void KernelStartup(void);

//void Board_Startup(void)
//{
//	Board_HardInit();
//    KernelStartup();	//启动操作系统(该函数不会返回，多任务环境开始)
//}

/*=========================================================================================*/

BOOL	GUI_Startup(void);

void	GUI_Thread(void *argv)
{
    argv = NULL;
    GUI_msleep(100);
	GUI_Startup();

}

/*=========================================================================================*/

void OEM_Init(void)
{
	GUI_Thread_Create(GUI_Thread,NULL,8196,NULL,10,5);
}

/*=========================================================================================*/
int	GamepaperMain(HANDLE hInstance,void *argv);
int ChessMain(HANDLE hInstance,void *argv);

int InfoNES_WinMain(HANDLE hInstance,void *argv);
int	SensorTest_WinMain(void *argv);
//void	CDlg_AudioPlayer_Startup(HWND hwnd_prev);
void AudioPlayer(const WCHAR *Name,int x,int y,int w,int h);
void RadioPlayer(const WCHAR* Name,int x,int y,int w,int h);
void USB_OTGStartup(void);

void GUI_Demo(void)
{
////	GUI_DEMO_Rotate();
//	GUI_DEMO_Messagebox();
//	GUI_DEMO_MultiWindow();
//	GUI_DEMO_Listbox_OwnerDraw();

////	GUI_DEMO_BMP_Speed();
//	GUI_DEMO_BitBlt_Speed();

//	GUI_DEMO_TextOut();
////	GUI_DEMO_Drawbitmap();
////	GUI_DEMO_Rotatebitmap();
//	GUI_DEMO_ScaleBitmap();

////	GUI_DEMO_ShowWave();
//	GUI_DEMO_MultiWindow();
//	GUI_DEMO_Textbox();
//	GUI_DEMO_Button();
//	GUI_DEMO_Checkbox();
//	GUI_DEMO_Radiobox();
//	GUI_DEMO_Progressbar();
//	GUI_DEMO_Scrollbar();
//	GUI_DEMO_Listbox();
//	GUI_DEMO_Listbox_OwnerDraw();
//	GUI_DEMO_Messagebox();


}

void	GUI_UserAppStart(void)
{

#if 0
	int	i;
	GUI_msleep(100);

//	GUI_DEMO_RectSpeed();

	//CDlg_FileExpoler(NULL,20,30,400,300,L"File Expolorer","B:",NULL);
	//GUI_DEMO_ScaleBitmap();
	//GUI_DEMO_TextOut();


	if(0)
	{ //在SD卡上生成 .res文件.

		char input[256];
		char out[256];

		if(CDlg_FileExpoler(NULL,20,30,300,300,L"RES maker: Input DIR","B:",input))
		if(CDlg_FileExpoler(NULL,20,30,300,300,L"RES maker: Output File","B:",out))
		{

			Dlg_RES_Maker(0,0,GUI_XSIZE,GUI_YSIZE,out,input);
		}
		//Dlg_RES_Maker(0,0,240,280,"B:AAT233.res","B:AAT233_RES");
	}

	if(0)
	{ //把.res文件写到Flash中.

		char buf[256];

		if(CDlg_FileExpoler(NULL,20,30,300,300,L"RES file Write to flash...","B:",buf))
		{
			Dlg_Flash_Writer(0,0,GUI_XSIZE,GUI_YSIZE,buf,0x00200000);
		}
	}
	//Board_App_Main(0,0,GUI_XSIZE,GUI_YSIZE,L"STM32F103");

	//AAT233_WinMain(NULL,NULL);
	while(1)
	{

//		AudioPlayer(L"XPlayer",10,20,400,480);
//		GamePaperMain(0,0,400,400,L"Gamepager");
//		InfoNES_WinMain(NULL,"B:");

//		SensorTest_MainWin(NULL);
		GUI_Demo();
		//InfoNES_WinMain(NULL,NULL);
		//Metor_Demo();

//		Metor_Demo();
//		DialogWindow_Test();
	//	CPP_Entry();
	}
#endif
}

/*=========================================================================================*/
/*=========================================================================================*/
static	int	code_page=936;

void	x_set_codepage(int cp)
{
	code_page =cp;
}

/*============================================================================*/

typedef	struct
{
	int cp;
	int (*fun)(WCHAR *wchar,const char *mbchar,int count);
}fun_mbstowcs_tbl_t;

typedef	struct
{
	int cp;
	int (*fun)(char *mbchar,const WCHAR *wchar,int count);
}fun_wcstombs_tbl_t;


const	static	fun_mbstowcs_tbl_t mbstowcs_tbl[]={

#ifdef	CP437
	437,	x_mbstowcs_cp437,
#endif

#ifdef	CP720
	720,	x_mbstowcs_cp720,
#endif

#ifdef	CP737
	737,	x_mbstowcs_cp737,
#endif

#ifdef	CP775
	775,	x_mbstowcs_cp775,
#endif

#ifdef	CP850
	850,	x_mbstowcs_cp850,
#endif

#ifdef	CP852
	852,	x_mbstowcs_cp852,
#endif

#ifdef	CP855
	855,	x_mbstowcs_cp855,
#endif

#ifdef	CP858
	858,	x_mbstowcs_cp858,
#endif

#ifdef	CP862
	862,	x_mbstowcs_cp862,
#endif

#ifdef	CP866
	866,	x_mbstowcs_cp866,
#endif

#ifdef	CP874
	874,	x_mbstowcs_cp874,
#endif

#ifdef	CP1250
	1250,	x_mbstowcs_cp1250,
#endif

#ifdef	CP1251
	1251,	x_mbstowcs_cp1251,
#endif

#ifdef	CP1252
	1252,	x_mbstowcs_cp1252,
#endif

#ifdef	CP1253
	1253,	x_mbstowcs_cp1253,
#endif

#ifdef	CP1254
	1254,	x_mbstowcs_cp1254,
#endif

#ifdef	CP1255
	1255,	x_mbstowcs_cp1255,
#endif

#ifdef	CP1256
	1256,	x_mbstowcs_cp1256,
#endif

#ifdef	CP1257
	1257,	x_mbstowcs_cp1257,
#endif

#ifdef	CP1258
	1258,	x_mbstowcs_cp1258,
#endif

#ifdef	CP932
	932,	x_mbstowcs_cp932,
#endif

#ifdef	CP936
	936,	x_mbstowcs_cp936,
#endif

#ifdef	CP949
	949,	x_mbstowcs_cp949,
#endif

#ifdef	CP950
	950,	x_mbstowcs_cp950,
#endif

	0,		NULL

};
const	static	fun_wcstombs_tbl_t wcstombs_tbl[]={

#ifdef	CP437
	437,	x_wcstombs_cp437,
#endif

#ifdef	CP720
	720,	x_wcstombs_cp720,
#endif

#ifdef	CP737
	737,	x_wcstombs_cp737,
#endif

#ifdef	CP775
	775,	x_wcstombs_cp775,
#endif

#ifdef	CP850
	850,	x_wcstombs_cp850,
#endif

#ifdef	CP852
	852,	x_wcstombs_cp852,
#endif

#ifdef	CP855
	855,	x_wcstombs_cp855,
#endif

#ifdef	CP858
	858,	x_wcstombs_cp858,
#endif

#ifdef	CP862
	862,	x_wcstombs_cp862,
#endif

#ifdef	CP866
	866,	x_wcstombs_cp866,
#endif

#ifdef	CP874
	874,	x_wcstombs_cp874,
#endif

#ifdef	CP1250
	1250,	x_wcstombs_cp1250,
#endif

#ifdef	CP1251
	1251,	x_wcstombs_cp1251,
#endif

#ifdef	CP1252
	1252,	x_wcstombs_cp1252,
#endif

#ifdef	CP1253
	1253,	x_wcstombs_cp1253,
#endif

#ifdef	CP1254
	1254,	x_wcstombs_cp1254,
#endif

#ifdef	CP1255
	1255,	x_wcstombs_cp1255,
#endif

#ifdef	CP1256
	1256,	x_wcstombs_cp1256,
#endif

#ifdef	CP1257
	1257,	x_wcstombs_cp1257,
#endif

#ifdef	CP1258
	1258,	x_wcstombs_cp1258,
#endif

#ifdef	CP932
	932,	x_wcstombs_cp932,
#endif

#ifdef	CP936
	936,	x_wcstombs_cp936,
#endif

#ifdef	CP949
	949,	x_wcstombs_cp949,
#endif

#ifdef	CP950
	950,	x_wcstombs_cp950,
#endif

	0,		NULL

};


int	x_mbstowcs(WCHAR *wchar, const char *mbchar, int count)
{
   const fun_mbstowcs_tbl_t *p;

   p	=mbstowcs_tbl;

   while(p->fun!=NULL)
   {
   		if(p->cp == code_page)
   		{
   			return	p->fun(wchar,mbchar,count);
   		}
   		p++;

   }

 	return	x_mbstowcs_cp437(wchar,mbchar,count);
}

int	x_wcstombs(char *mbchar, const WCHAR *wchar, int count)
{
   const fun_wcstombs_tbl_t *p;

   p	=wcstombs_tbl;

   while(p->fun!=NULL)
   {
   		if(p->cp == code_page)
   		{
   			return	p->fun(mbchar,wchar,count);
   		}
   		p++;

   }

 	return	x_wcstombs_cp437(mbchar,wchar,count);

}

/*=========================================================================================*/
