
#include "stm32f10x.h"
#include "GUI_Drv.h"

/*============================================================================*/

#define	LCD_RST_PIN	GPIOG,GPIO_Pin_11
#define	LCD_BL_PIN	GPIOG,GPIO_Pin_6

void	LCD_Init(void);

void LCD_HardInit(void)
{
	GPIO_InitTypeDef gpio_init;

	gpio_init.GPIO_Mode  = GPIO_Mode_Out_PP; //复用输出
	gpio_init.GPIO_Speed = GPIO_Speed_50MHz; //50MHz

	//PG6 - LCD BackLight: 0:ON; 1:OFF
	gpio_init.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOG, &gpio_init); //初始化

	//PG11 - LCD_nRST:
	gpio_init.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOG, &gpio_init); //初始化

	GPIO_SetBits(LCD_RST_PIN);
	GUI_msleep(50);
	GPIO_ResetBits(LCD_RST_PIN);
	GUI_msleep(50);
	GPIO_SetBits(LCD_RST_PIN);
	GUI_msleep(50);

	LCD_Init();
}


void LCD_BkLight(int on)
{
	if(on)
	{
		GPIO_ResetBits(LCD_BL_PIN);
	}
	else
	{
		GPIO_SetBits(LCD_BL_PIN);
	}
}

/*===================================================================================*/


#if 0

BOOL	LCD_SetRotate(int rotate)
{

	return FALSE;
}

/*===================================================================================*/

BOOL	LCD_SetRotate(int rotate);

BOOL	gdrvSetRotate(int rotate)
{
	BOOL res=FALSE;

	switch(rotate)
	{
		case ROTATE_0:
			if(LCD_SetRotate(ROTATE_0))
			{
				disp_rotate =rotate;

				surf_screen.Width =LCD_XSIZE;
				surf_screen.Height =LCD_YSIZE;
				surf_screen.WidthBytes =surf_screen.Width*2;

				disp_xmax =surf_screen.Width-1;
				disp_ymax =surf_screen.Height-1;

				res =TRUE;
			}
			break;
			////

		case ROTATE_90:
			if(LCD_SetRotate(ROTATE_90))
			{
				disp_rotate =rotate;

				surf_screen.Width =LCD_YSIZE;
				surf_screen.Height =LCD_XSIZE;
				surf_screen.WidthBytes =surf_screen.Width*2;

				disp_xmax =surf_screen.Width-1;
				disp_ymax =surf_screen.Height-1;

				res =TRUE;
			}
			break;
			////

		case ROTATE_180:
			if(LCD_SetRotate(ROTATE_180))
			{
				disp_rotate =rotate;

				surf_screen.Width =LCD_XSIZE;
				surf_screen.Height =LCD_YSIZE;
				surf_screen.WidthBytes =surf_screen.Width*2;

				disp_xmax =surf_screen.Width-1;
				disp_ymax =surf_screen.Height-1;

				res =TRUE;
			}
			break;
			////

		case ROTATE_270:
			if(LCD_SetRotate(ROTATE_270))
			{
				disp_rotate =rotate;

				surf_screen.Width =LCD_YSIZE;
				surf_screen.Height =LCD_XSIZE;
				surf_screen.WidthBytes =surf_screen.Width*2;

				disp_xmax =surf_screen.Width-1;
				disp_ymax =surf_screen.Height-1;

				res =TRUE;
			}
			break;
			////

		default:
			 break;

	}
	return res;
}
#endif

