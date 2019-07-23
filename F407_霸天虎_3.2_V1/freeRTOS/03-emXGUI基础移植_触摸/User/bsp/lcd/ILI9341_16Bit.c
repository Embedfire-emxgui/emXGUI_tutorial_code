
//#include	"BSP.h"
#include	"emXGUI.h"

#include	"GUI_Drv.h"

#include 	"stm32f4xx_rcc.h"
#include 	"stm32f4xx_gpio.h"
#include 	"stm32f4xx_fsmc.h"

/*=========================================================================================*/
/*
 * 野火STM32F103 3.2寸LCD (ILI9341)
 */

#define	LCD_CMD_ADDR	EXT_LCD_BASE
#define	LCD_DAT_ADDR	(EXT_LCD_BASE+(0x03FFFFFE))

#define	LCD_CMD	(*(volatile u16*)(LCD_CMD_ADDR))
#define	LCD_DAT	(*(volatile u16*)(LCD_DAT_ADDR))


/*=========================================================================================*/

static void delay_ms(unsigned int t)
{
	volatile int i;
	while(t-- > 0)
	{
		for(i=100;i>0;i--);
	}
}

static	INLINE void write_cmd(u8 a)
{
	LCD_CMD =a;
}

static	INLINE void write_dat(u8 a)
{
 	LCD_DAT =a;
}

/*=========================================================================================*/

#define	__lcd_write_cmd(cmd)    LCD_CMD =cmd
#define	__lcd_write_dat(dat) 	LCD_DAT =dat
#define	__lcd_read_dat()		LCD_DAT

#define	__lcd_map_rgb(r,g,b)	RGB565(r>>3,g>>2,b>>3)


void __lcd_write_start(u16 sx,u16 sy,u16 ex,u16 ey)
{
	__lcd_write_cmd(0x2A);
	__lcd_write_dat(sx>>8);
	__lcd_write_dat(sx);
	__lcd_write_dat(ex>>8);
	__lcd_write_dat(ex);

	__lcd_write_cmd(0x2B);
	__lcd_write_dat(sy>>8);
	__lcd_write_dat(sy);
	__lcd_write_dat(ey>>8);
	__lcd_write_dat(ey);

	__lcd_write_cmd(0x2C);
}

void __lcd_read_start(u16 sx,u16 sy,u16 ex,u16 ey)
{
	volatile u16 c;

	__lcd_write_cmd(0x2A);
	__lcd_write_dat(sx>>8);
	__lcd_write_dat(sx);
	__lcd_write_dat(ex>>8);
	__lcd_write_dat(ex);

	__lcd_write_cmd(0x2B);
	__lcd_write_dat(sy>>8);
	__lcd_write_dat(sy);
	__lcd_write_dat(ey>>8);
	__lcd_write_dat(ey);

	__lcd_write_cmd(0x2E);
	c =__lcd_read_dat(); //DummyRead
	for(c=0;c<2;c++);
}

void __lcd_write_rgb(U8 r,U8 g,U8 b)
{
	__lcd_write_dat(__lcd_map_rgb(r,g,b));
}

u16 __lcd_read_pixel(void)
{

	u16 c1,c2;

	c1 =__lcd_read_dat(); //RG
	c2 =__lcd_read_dat(); //BX

	return	__lcd_map_rgb(c1>>8,c1,c2>>8);
}

void __lcd_read_rgb(u8 *r,u8 *g,u8 *b)
{
	u16 c1,c2;

	c1 =__lcd_read_dat(); //RG
	c2 =__lcd_read_dat(); //BX

	*r =c1>>8;
	*g =c1;
	*b =c2>>8;
}

/*=========================================================================================*/

BOOL LCD_SetRotate(int rotate)
{

	switch(rotate)
	{
		case ROTATE_0:
			write_cmd(0x36); // Memory Access Control
    write_dat( 0x08 |(3<<5));//write_dat((0<<7)|(1<<6)|(0<<5)|(1<<3)|(0<<2));	// 0
			return TRUE;
			////

		case ROTATE_90:
			write_cmd(0x36); // Memory Access Control
			write_dat((0<<7)|(0<<6)|(1<<5)|(1<<3)|(0<<2));	// 90
			return TRUE;
			////

		case ROTATE_180:
			write_cmd(0x36); // Memory Access Control
			write_dat((1<<7)|(0<<6)|(0<<5)|(1<<3)|(0<<2));	// 180
			return TRUE;
			////

		case ROTATE_270:
			write_cmd(0x36); // Memory Access Control
			write_dat((1<<7)|(1<<6)|(1<<5)|(1<<3)|(0<<2));	// 270
			return TRUE;
			////

		default:
			return FALSE;

	}
}

/*=========================================================================================*/


static void macDEBUG_DELAY(void)
{
	delay_ms(50);
}

static void ILI9341_Init ( void )
{

#define	ILI9341_Write_Cmd write_cmd
#define	ILI9341_Write_Data	write_dat


	/******************************* ?¨ò? ILI934 3￡ó??üá? ********************************/
	#define      macCMD_SetCoordinateX		 		    0x2A	     //éè??X×?±ê
	#define      macCMD_SetCoordinateY		 		    0x2B	     //éè??Y×?±ê
	#define      macCMD_SetPixel		 		        0x2C	     //ì?3?????

	/*  Power control B (CFh)  */
	macDEBUG_DELAY  ();
	ILI9341_Write_Cmd ( 0xCF  );
	ILI9341_Write_Data ( 0x00  );
	ILI9341_Write_Data ( 0x81  );
	ILI9341_Write_Data ( 0x30  );

	/*  Power on sequence control (EDh) */
	macDEBUG_DELAY ();
	ILI9341_Write_Cmd ( 0xED );
	ILI9341_Write_Data ( 0x64 );
	ILI9341_Write_Data ( 0x03 );
	ILI9341_Write_Data ( 0x12 );
	ILI9341_Write_Data ( 0x81 );

	/*  Driver timing control A (E8h) */
	macDEBUG_DELAY ();
	ILI9341_Write_Cmd ( 0xE8 );
	ILI9341_Write_Data ( 0x85 );
	ILI9341_Write_Data ( 0x10 );
	ILI9341_Write_Data ( 0x78 );

	/*  Power control A (CBh) */
	macDEBUG_DELAY ();
	ILI9341_Write_Cmd ( 0xCB );
	ILI9341_Write_Data ( 0x39 );
	ILI9341_Write_Data ( 0x2C );
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0x34 );
	ILI9341_Write_Data ( 0x02 );

	/* Pump ratio control (F7h) */
	macDEBUG_DELAY ();
	ILI9341_Write_Cmd ( 0xF7 );
	ILI9341_Write_Data ( 0x20 );

	/* Driver timing control B */
	macDEBUG_DELAY ();
	ILI9341_Write_Cmd ( 0xEA );
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0x00 );


	/* Frame Rate Control (In Normal Mode/Full Colors) (B1h) */
	macDEBUG_DELAY ();
	ILI9341_Write_Cmd ( 0xB1 );
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0x1B );

	/*  Display Function Control (B6h) */
	macDEBUG_DELAY ();
	ILI9341_Write_Cmd ( 0xB6 );
	ILI9341_Write_Data ( 0x0A );
	ILI9341_Write_Data ( 0xA2 );


	/* Power Control 1 (C0h) */
	macDEBUG_DELAY ();
	ILI9341_Write_Cmd ( 0xC0 );
	ILI9341_Write_Data ( 0x25 ); //0x35

	/* Power Control 2 (C1h) */
	macDEBUG_DELAY ();
	ILI9341_Write_Cmd ( 0xC1 );
	ILI9341_Write_Data ( 0x10 ); //0x11

	/* VCOM Control 1 (C5h) */
	ILI9341_Write_Cmd ( 0xC5 );
	ILI9341_Write_Data ( 0x45 );
	ILI9341_Write_Data ( 0x45 );

	/*  VCOM Control 2 (C7h)  */
	ILI9341_Write_Cmd ( 0xC7 );
	ILI9341_Write_Data ( 0xA2 );

	/* Enable 3G (F2h) */
	ILI9341_Write_Cmd ( 0xF2 );
	ILI9341_Write_Data ( 0x00 );

	/* Gamma Set (26h) */
	ILI9341_Write_Cmd ( 0x26 );
	ILI9341_Write_Data ( 0x01 );
	macDEBUG_DELAY ();

	/* Positive Gamma Correction */
	ILI9341_Write_Cmd ( 0xE0 ); //Set Gamma
	ILI9341_Write_Data ( 0x0F );
	ILI9341_Write_Data ( 0x26 );
	ILI9341_Write_Data ( 0x24 );
	ILI9341_Write_Data ( 0x0B );
	ILI9341_Write_Data ( 0x0E );
	ILI9341_Write_Data ( 0x09 );
	ILI9341_Write_Data ( 0x54 );
	ILI9341_Write_Data ( 0xA8 );
	ILI9341_Write_Data ( 0x46 );
	ILI9341_Write_Data ( 0x0C );
	ILI9341_Write_Data ( 0x17 );
	ILI9341_Write_Data ( 0x09 );
	ILI9341_Write_Data ( 0x0F );
	ILI9341_Write_Data ( 0x07 );
	ILI9341_Write_Data ( 0x00 );

	/* Negative Gamma Correction (E1h) */
	ILI9341_Write_Cmd ( 0XE1 ); //Set Gamma
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0x19 );
	ILI9341_Write_Data ( 0x1B );
	ILI9341_Write_Data ( 0x04 );
	ILI9341_Write_Data ( 0x10 );
	ILI9341_Write_Data ( 0x07 );
	ILI9341_Write_Data ( 0x2A );
	ILI9341_Write_Data ( 0x47 );
	ILI9341_Write_Data ( 0x39 );
	ILI9341_Write_Data ( 0x03 );
	ILI9341_Write_Data ( 0x06 );
	ILI9341_Write_Data ( 0x06 );
	ILI9341_Write_Data ( 0x30 );
	ILI9341_Write_Data ( 0x38 );
	ILI9341_Write_Data ( 0x0F );

	/* memory access control set */
	macDEBUG_DELAY ();
	ILI9341_Write_Cmd ( 0x36 );
	ILI9341_Write_Data ( 0xC8 );    /*êú?á  ×óé???μ? (?eμ?)μ?óò???? (??μ?)é¨?è·?ê?*/
	macDEBUG_DELAY ();

	/* column address control set */
	ILI9341_Write_Cmd ( macCMD_SetCoordinateX );
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0xEF );

	/* page address control set */
	macDEBUG_DELAY ();
	ILI9341_Write_Cmd ( macCMD_SetCoordinateY );
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0x01 );
	ILI9341_Write_Data ( 0x3F );

	/*  Pixel Format Set (3Ah)  */
	macDEBUG_DELAY ();
	ILI9341_Write_Cmd ( 0x3a );
	ILI9341_Write_Data ( 0x55 );

	/* Sleep Out (11h)  */
	ILI9341_Write_Cmd ( 0x11 );
	//ILI9341_Delay ( 0xAFFf<<2 );
	macDEBUG_DELAY ();

	/* Display ON (29h) */
	ILI9341_Write_Cmd ( 0x29 );
}

/*=========================================================================================*/
/********************管脚宏定义**********************************/
#define      ILI9806G_BK_CLK                RCC_AHB1Periph_GPIOF   
#define      ILI9806G_BK_PORT               GPIOF
#define      ILI9806G_BK_PIN                GPIO_Pin_9

#define      ILI9806G_RST_CLK                RCC_AHB1Periph_GPIOF  
#define      ILI9806G_RST_PORT               GPIOF
#define      ILI9806G_RST_PIN                GPIO_Pin_11

#define	LCD_RST_PIN	ILI9806G_RST_PORT,ILI9806G_RST_PIN
#define	LCD_BL_PIN	ILI9806G_BK_PORT,ILI9806G_BK_PIN

#if 1

#define		EXT_LCD_ARCH
//#define		EXT_LCD_DMA
#include 	"EXT_LCD_Arch.c"

#endif

/*=========================================================================================*/


void	LCD_Init(void)
{
  GPIO_InitTypeDef gpio_init;
  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
  
	gpio_init.GPIO_Mode  = GPIO_Mode_OUT; //复用输出
  gpio_init.GPIO_OType = GPIO_OType_PP;//推挽输出
	gpio_init.GPIO_Speed = GPIO_Speed_50MHz; //50MHz
  gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;//上拉

	//PG6 - LCD BackLight: 0:ON; 1:OFF
	gpio_init.GPIO_Pin = ILI9806G_BK_PIN;
	GPIO_Init(ILI9806G_BK_PORT, &gpio_init); //初始化

	//PG11 - LCD_nRST:
	gpio_init.GPIO_Pin = ILI9806G_RST_PIN;
	GPIO_Init(ILI9806G_RST_PORT, &gpio_init); //初始化

	GPIO_SetBits(LCD_RST_PIN);
	GUI_msleep(50);
	GPIO_ResetBits(LCD_RST_PIN);
	GUI_msleep(50);
	GPIO_SetBits(LCD_RST_PIN);
	GUI_msleep(50);
  
	ILI9341_Init();
	LCD_SetRotate(ROTATE_0);

#ifdef	EXT_LCD_DMA
	LCD_DMA_Init(LCD_DAT_ADDR);
#endif

}

void LCD_BackLed_Control(int on)
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

/*=========================================================================================*/

#if 0
#include	"emXGUI.h"

#include	"GUI_Drv.h"

#include 	"stm32f4xx_rcc.h"
#include 	"stm32f4xx_gpio.h"
#include 	"stm32f4xx_fsmc.h"

/*=========================================================================================*/
//野火的4.5寸屏854x480


#define	LCD_CMD_ADDR	EXT_LCD_BASE
#define	LCD_DAT_ADDR	(EXT_LCD_BASE+0xFFFE)//)0x03FFFFFE

#define	LCD_CMD	(*(volatile u16*)(LCD_CMD_ADDR))
#define	LCD_DAT	(*(volatile u16*)(LCD_DAT_ADDR))


/*=========================================================================================*/

static void delay_ms(unsigned int t)
{
	volatile int i;
	while(t-- > 0)
	{
		for(i=100;i>0;i--);
	}
}

static	INLINE void write_cmd(u8 a)
{
	LCD_CMD =a;
}

static	INLINE void write_dat(u8 a)
{
 	LCD_DAT =a;
}

/*=========================================================================================*/

#define	__lcd_write_cmd(cmd)    LCD_CMD =cmd
#define	__lcd_write_dat(dat) 	LCD_DAT =dat
#define	__lcd_read_dat()		LCD_DAT

#define	__lcd_map_rgb(r,g,b)	RGB565(r>>3,g>>2,b>>3)


static INLINE void __lcd_write_start(u16 sx,u16 sy,u16 ex,u16 ey)
{
	__lcd_write_cmd(0x2A);
	__lcd_write_dat(sx>>8);
	__lcd_write_dat(sx);
	__lcd_write_dat(ex>>8);
	__lcd_write_dat(ex);

	__lcd_write_cmd(0x2B);
	__lcd_write_dat(sy>>8);
	__lcd_write_dat(sy);
	__lcd_write_dat(ey>>8);
	__lcd_write_dat(ey);

	__lcd_write_cmd(0x2C);
}


static INLINE void __lcd_read_start(u16 sx,u16 sy,u16 ex,u16 ey)
{
	volatile u16 c;

	__lcd_write_cmd(0x2A);
	__lcd_write_dat(sx>>8);
	__lcd_write_dat(sx);
	__lcd_write_dat(ex>>8);
	__lcd_write_dat(ex);

	__lcd_write_cmd(0x2B);
	__lcd_write_dat(sy>>8);
	__lcd_write_dat(sy);
	__lcd_write_dat(ey>>8);
	__lcd_write_dat(ey);

	__lcd_write_cmd(0x2E);
	c =__lcd_read_dat(); //DummyRead
	for(c=0;c<2;c++);
}

static INLINE	void __lcd_write_rgb(U8 r,U8 g,U8 b)
{
	__lcd_write_dat(__lcd_map_rgb(r,g,b));
}


static INLINE u16 __lcd_read_pixel(void)
{

	u16 c1,c2;

	c1 =__lcd_read_dat(); //RG
	c2 =__lcd_read_dat(); //BX

	return	__lcd_map_rgb(c1>>8,c1,c2>>8);
}

static INLINE void __lcd_read_rgb(u8 *r,u8 *g,u8 *b)
{
	u16 c1,c2;

	c1 =__lcd_read_dat(); //RG
	c2 =__lcd_read_dat(); //BX

	*r =c1>>8;
	*g =c1;
	*b =c2>>8;
}



/*=========================================================================================*/

/*=========================================================================================*/

BOOL	LCD_SetRotate(int rotate)
{

	switch(rotate)
	{
		case ROTATE_0:
			write_cmd(0x36); // Memory Access Control
			write_dat((0<<7)|(1<<6)|(0<<5)|(0<<3)|(0<<2)|(1<<1));	// 0
			return TRUE;
			////

		case ROTATE_90:
			write_cmd(0x36); // Memory Access Control
			write_dat((0<<7)|(0<<6)|(1<<5)|(0<<3)|(0<<2)|(1<<1));	// 90
			return TRUE;
			////

		case ROTATE_180:
			write_cmd(0x36); // Memory Access Control
			write_dat((1<<7)|(0<<6)|(0<<5)|(0<<3)|(0<<2)|(1<<1));	// 180
			return TRUE;
			////

		case ROTATE_270:
			write_cmd(0x36); // Memory Access Control
			write_dat((1<<7)|(1<<6)|(1<<5)|(0<<3)|(0<<2)|(1<<1));	// 270
			return TRUE;
			////

		default:
			return FALSE;
	}
}

/*=========================================================================================*/

static void DEBUG_DELAY(void)
{
	GUI_msleep(50);
}

static void ILI9806_Init ( void )
{
	//液晶厂商提供了两种版本的屏幕，性能一样，它们的驱动配置稍有区别，
	//本驱动通过#if #else #endif来设置，若屏幕显示花屏，请把#if 0改成#if 1，或1改成0
	//在2017-12-14日后购买的产品，使用#if 0
#if 0
	//旧版
	/* EXTC Command Set enable register */
	DEBUG_DELAY  ();
	write_cmd ( 0xFF  );
	write_dat ( 0xFF  );
	write_dat ( 0x98  );
	write_dat ( 0x06  );

	/* GIP 1(BCh)  */
	DEBUG_DELAY ();
	write_cmd(0xBC);
	write_dat(0x01);
	write_dat(0x0E);
	write_dat(0x61);
	write_dat(0xFB);
	write_dat(0x10);
	write_dat(0x10);
	write_dat(0x0B);
	write_dat(0x0F);
	write_dat(0x2E);
	write_dat(0x73);
	write_dat(0xFF);
	write_dat(0xFF);
	write_dat(0x0E);
	write_dat(0x0E);
	write_dat(0x00);
	write_dat(0x03);
	write_dat(0x66);
	write_dat(0x63);
	write_dat(0x01);
	write_dat(0x00);
	write_dat(0x00);

	/* GIP 2 (BDh) */
	DEBUG_DELAY ();
	write_cmd(0xBD);
	write_dat(0x01);
	write_dat(0x23);
	write_dat(0x45);
	write_dat(0x67);
	write_dat(0x01);
	write_dat(0x23);
	write_dat(0x45);
	write_dat(0x67);

	/* GIP 3 (BEh) */
	DEBUG_DELAY ();
	write_cmd(0xBE);
	write_dat(0x00);
	write_dat(0x21);
	write_dat(0xAB);
	write_dat(0x60);
	write_dat(0x22);
	write_dat(0x22);
	write_dat(0x22);
	write_dat(0x22);
	write_dat(0x22);

	/* Vcom  (C7h) */
	DEBUG_DELAY ();
	write_cmd ( 0xC7 );
	write_dat ( 0x6F );

	/* EN_volt_reg (EDh)*/
	DEBUG_DELAY ();
	write_cmd ( 0xED );
	write_dat ( 0x7F );
	write_dat ( 0x0F );
	write_dat ( 0x00 );

	/* Power Control 1 (C0h) */
	DEBUG_DELAY ();
	write_cmd ( 0xC0 );
	write_dat ( 0x37 );
	write_dat ( 0x0B );
	write_dat ( 0x0A );

	/* LVGL (FCh) */
	DEBUG_DELAY ();
	write_cmd ( 0xFC );
	write_dat ( 0x0A );

	/* Engineering Setting (DFh) */
	DEBUG_DELAY ();
	write_cmd ( 0xDF );
	write_dat ( 0x00 );
	write_dat ( 0x00 );
	write_dat ( 0x00 );
	write_dat ( 0x00 );
	write_dat ( 0x00 );
	write_dat ( 0x20 );

	/* DVDD Voltage Setting(F3h) */
	DEBUG_DELAY ();
	write_cmd ( 0xF3 );
	write_dat ( 0x74 );

	/* Display Inversion Control (B4h) */
	write_cmd ( 0xB4 );
	write_dat ( 0x00 );
	write_dat ( 0x00 );
	write_dat ( 0x00 );

	/* 480x854 (F7h)  */
	write_cmd ( 0xF7 );
	write_dat ( 0x89 );

	/* Frame Rate (B1h) */
	write_cmd ( 0xB1 );
	write_dat ( 0x00 );
	write_dat ( 0x12 );
	write_dat ( 0x10 );

	/* Panel Timing Control (F2h) */
	write_cmd ( 0xF2 );
	write_dat ( 0x80 );
	write_dat ( 0x5B );
	write_dat ( 0x40 );
	write_dat ( 0x28 );

	DEBUG_DELAY ();

	/* Power Control 2 (C1h) */
	write_cmd ( 0xC1 );
	write_dat ( 0x17 );
	write_dat ( 0x7D );
	write_dat ( 0x7A );
	write_dat ( 0x20 );

	DEBUG_DELAY ();

	write_cmd(0xE0);
	write_dat(0x00); //P1
	write_dat(0x11); //P2
	write_dat(0x1C); //P3
	write_dat(0x0E); //P4
	write_dat(0x0F); //P5
	write_dat(0x0C); //P6
	write_dat(0xC7); //P7
	write_dat(0x06); //P8
	write_dat(0x06); //P9
	write_dat(0x0A); //P10
	write_dat(0x10); //P11
	write_dat(0x12); //P12
	write_dat(0x0A); //P13
	write_dat(0x10); //P14
	write_dat(0x02); //P15
	write_dat(0x00); //P16

	DEBUG_DELAY ();

	write_cmd(0xE1);
	write_dat(0x00); //P1
	write_dat(0x12); //P2
	write_dat(0x18); //P3
	write_dat(0x0C); //P4
	write_dat(0x0F); //P5
	write_dat(0x0A); //P6
	write_dat(0x77); //P7
	write_dat(0x06); //P8
	write_dat(0x07); //P9
	write_dat(0x0A); //P10
	write_dat(0x0E); //P11
	write_dat(0x0B); //P12
	write_dat(0x10); //P13
	write_dat(0x1D); //P14
	write_dat(0x17); //P15
	write_dat(0x00); //P16

	/* Tearing Effect ON (35h)  */
	write_cmd ( 0x35 );
	write_dat ( 0x00 );

	write_cmd ( 0x3A );
	write_dat ( 0x55 );

	write_cmd ( 0x11 );
	DEBUG_DELAY ();
	write_cmd ( 0x29 );

#else
	//新版
	DEBUG_DELAY();
	write_cmd(0xFF);
	write_dat(0xFF);
	write_dat(0x98);
	write_dat(0x06);
	DEBUG_DELAY();
	write_cmd(0xBA);
	write_dat(0x60);
	DEBUG_DELAY();
	write_cmd(0xBC);
	write_dat(0x03);
	write_dat(0x0E);
	write_dat(0x61);
	write_dat(0xFF);
	write_dat(0x05);
	write_dat(0x05);
	write_dat(0x1B);
	write_dat(0x10);
	write_dat(0x73);
	write_dat(0x63);
	write_dat(0xFF);
	write_dat(0xFF);
	write_dat(0x05);
	write_dat(0x05);
	write_dat(0x00);
	write_dat(0x00);
	write_dat(0xD5);
	write_dat(0xD0);
	write_dat(0x01);
	write_dat(0x00);
	write_dat(0x40);
	DEBUG_DELAY();
	write_cmd(0xBD);
	write_dat(0x01);
	write_dat(0x23);
	write_dat(0x45);
	write_dat(0x67);
	write_dat(0x01);
	write_dat(0x23);
	write_dat(0x45);
	write_dat(0x67);
	DEBUG_DELAY();
	write_cmd(0xBE);
	write_dat(0x01);
	write_dat(0x2D);
	write_dat(0xCB);
	write_dat(0xA2);
	write_dat(0x62);
	write_dat(0xF2);
	write_dat(0xE2);
	write_dat(0x22);
	write_dat(0x22);
	DEBUG_DELAY();
	write_cmd(0xC7);
	write_dat(0x63);
	DEBUG_DELAY();
	write_cmd(0xED);
	write_dat(0x7F);
	write_dat(0x0F);
	write_dat(0x00);
	DEBUG_DELAY();
	write_cmd(0xC0);
	write_dat(0x03);
	write_dat(0x0B);
	write_dat(0x00);
	DEBUG_DELAY();
	write_cmd(0xFC);
	write_dat(0x08);
	DEBUG_DELAY();
	write_cmd(0xDF);
	write_dat(0x00);
	write_dat(0x00);
	write_dat(0x00);
	write_dat(0x00);
	write_dat(0x00);
	write_dat(0x20);
	DEBUG_DELAY();
	write_cmd(0xF3);
	write_dat(0x74);
	DEBUG_DELAY();
	write_cmd(0xF9);
	write_dat(0x00);
	write_dat(0xFD);
	write_dat(0x80);
	write_dat(0x80);
	write_dat(0xC0);
	DEBUG_DELAY();
	write_cmd(0xB4);
	write_dat(0x02);
	write_dat(0x02);
	write_dat(0x02);
	DEBUG_DELAY();
	write_cmd(0xF7);
	write_dat(0x81);
	DEBUG_DELAY();
	write_cmd(0xB1);
	write_dat(0x00);
	write_dat(0x13);
	write_dat(0x13);
	DEBUG_DELAY();
	write_cmd(0xF2);
	write_dat(0xC0);
	write_dat(0x02);
	write_dat(0x40);
	write_dat(0x28);
	DEBUG_DELAY();
	write_cmd(0xC1);
	write_dat(0x17);
	write_dat(0x75);
	write_dat(0x75);
	write_dat(0x20);
	DEBUG_DELAY();
	write_cmd(0xE0);
	write_dat(0x00);
	write_dat(0x05);
	write_dat(0x08);
	write_dat(0x0C);
	write_dat(0x0F);
	write_dat(0x15);
	write_dat(0x09);
	write_dat(0x07);
	write_dat(0x01);
	write_dat(0x06);
	write_dat(0x09);
	write_dat(0x16);
	write_dat(0x14);
	write_dat(0x3E);
	write_dat(0x3E);
	write_dat(0x00);
	DEBUG_DELAY();
	write_cmd(0xE1);
	write_dat(0x00);
	write_dat(0x09);
	write_dat(0x12);
	write_dat(0x12);
	write_dat(0x13);
	write_dat(0x1c);
	write_dat(0x07);
	write_dat(0x08);
	write_dat(0x05);
	write_dat(0x08);
	write_dat(0x03);
	write_dat(0x02);
	write_dat(0x04);
	write_dat(0x1E);
	write_dat(0x1B);
	write_dat(0x00);
	DEBUG_DELAY();
	write_cmd(0x3A);
	write_dat(0x55);
	DEBUG_DELAY();
	write_cmd(0x35);
	write_dat(0x00);
	DEBUG_DELAY();
	write_cmd(0x11);
	DEBUG_DELAY() ;
	write_cmd(0x29);
	DEBUG_DELAY()  ;
#endif

	LCD_SetRotate(ROTATE_90);
}

/********************管脚宏定义**********************************/
#define      ILI9806G_BK_CLK                RCC_AHB1Periph_GPIOF   
#define      ILI9806G_BK_PORT               GPIOF
#define      ILI9806G_BK_PIN                GPIO_Pin_9

#define      ILI9806G_RST_CLK                RCC_AHB1Periph_GPIOF  
#define      ILI9806G_RST_PORT               GPIOF
#define      ILI9806G_RST_PIN                GPIO_Pin_11

#define	LCD_RST_PIN	ILI9806G_RST_PORT,ILI9806G_RST_PIN
#define	LCD_BL_PIN	ILI9806G_BK_PORT,ILI9806G_BK_PIN

void LCD_BackLed_Control ( int  on )
{
	if ( on )
		 GPIO_SetBits( ILI9806G_BK_PORT, ILI9806G_BK_PIN );	
	else
		 GPIO_ResetBits( ILI9806G_BK_PORT, ILI9806G_BK_PIN );
		
}

/*=========================================================================================*/

#if 1

#define		EXT_LCD_ARCH
//#define		EXT_LCD_DMA

#include 	"EXT_LCD_Arch.c"

#endif


/*=========================================================================================*/


void	LCD_Init(void)
{
  
  GPIO_InitTypeDef gpio_init;
  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
  
	gpio_init.GPIO_Mode  = GPIO_Mode_OUT; //复用输出
  gpio_init.GPIO_OType = GPIO_OType_PP;//推挽输出
	gpio_init.GPIO_Speed = GPIO_Speed_50MHz; //50MHz
  gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;//上拉

	//PG6 - LCD BackLight: 0:ON; 1:OFF
	gpio_init.GPIO_Pin = ILI9806G_BK_PIN;
	GPIO_Init(ILI9806G_BK_PORT, &gpio_init); //初始化

	//PG11 - LCD_nRST:
	gpio_init.GPIO_Pin = ILI9806G_RST_PIN;
	GPIO_Init(ILI9806G_RST_PORT, &gpio_init); //初始化

	GPIO_SetBits(LCD_RST_PIN);
	GUI_msleep(50);
	GPIO_ResetBits(LCD_RST_PIN);
	GUI_msleep(50);
	GPIO_SetBits(LCD_RST_PIN);
	GUI_msleep(50);
  
	ILI9806_Init();

#ifdef	EXT_LCD_DMA
	LCD_DMA_Init(LCD_DAT_ADDR);
#endif

//	LCD_BkLight(TRUE); //打开背光
#if 0
	__lcd_set_window(10,20,240,100);
	__lcd_write_start();
	__lcd_write_pixels(RGB565(0,63,0),240*100);
	SYS_msleep(1000);


	while(0)
	{
		__lcd_set_window(0,0,LCD_XSIZE,LCD_YSIZE);
		__lcd_write_start();
		LCD_DMA_WritePixels(RGB565(31,0,0),LCD_XSIZE*LCD_YSIZE);
		SYS_msleep(100);

		__lcd_set_window(0,0,LCD_XSIZE,LCD_YSIZE);
		__lcd_write_start();
		LCD_DMA_WritePixels(RGB565(0,0,31),LCD_XSIZE*LCD_YSIZE);
		SYS_msleep(100);
		break;

	}
#endif
}
#endif

/*=========================================================================================*/
