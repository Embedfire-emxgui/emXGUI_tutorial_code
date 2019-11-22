
#include	"BSP.h"
#include	"emXGUI.h"

#include	"GUI_Drv.h"

#include 	"stm32f10x_rcc.h"
#include 	"stm32f10x_gpio.h"
#include 	"stm32f10x_fsmc.h"

/*=========================================================================================*/
//野火的4.5寸屏854x480


#define	LCD_CMD_ADDR	EXT_LCD_BASE
#define	LCD_DAT_ADDR	(EXT_LCD_BASE+0x03FFFFFE)//0xFFFE)

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

//背光引脚
#define      ILI9806G_BK_CLK                RCC_APB2Periph_GPIOG   
#define      ILI9806G_BK_PORT               GPIOG
#define      ILI9806G_BK_PIN                GPIO_Pin_6

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
#define	LCD_RST_PIN	GPIOG,GPIO_Pin_11
#define	LCD_BL_PIN	GPIOG,GPIO_Pin_6

void	LCD_Init(void)
{
  
  GPIO_InitTypeDef gpio_init;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
  
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


/*=========================================================================================*/
