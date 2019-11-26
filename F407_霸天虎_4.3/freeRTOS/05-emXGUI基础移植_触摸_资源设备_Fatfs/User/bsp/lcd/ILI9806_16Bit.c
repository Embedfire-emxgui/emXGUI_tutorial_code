
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

/******************************* 定义 NT35510 常用命令 ********************************/
#define      CMD_SetCoordinateX		 		    0x2A00	     //设置X坐标
#define      CMD_SetCoordinateY		 		    0x2B00	     //设置Y坐标
#define      CMD_SetPixel		 		          0X2C00	     //填充像素

/*=========================================================================================*/

static void delay_ms(unsigned int t)
{
	volatile int i;
	while(t-- > 0)
	{
		for(i=100;i>0;i--);
	}
}

static	INLINE void write_cmd(u16 a)
{
	LCD_CMD =a;
}

static	INLINE void write_dat(u16 a)
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
	__lcd_write_cmd(CMD_SetCoordinateX);
	__lcd_write_dat(sx>>8);
  __lcd_write_cmd(CMD_SetCoordinateX + 1);
	__lcd_write_dat(sx);
  __lcd_write_cmd(CMD_SetCoordinateX + 2);
	__lcd_write_dat(ex>>8);
  __lcd_write_cmd(CMD_SetCoordinateX + 3);
	__lcd_write_dat(ex);

	__lcd_write_cmd(CMD_SetCoordinateY);
	__lcd_write_dat(sy>>8);
  __lcd_write_cmd(CMD_SetCoordinateY + 1);
	__lcd_write_dat(sy);
  __lcd_write_cmd(CMD_SetCoordinateY + 2);
	__lcd_write_dat(ey>>8);
  __lcd_write_cmd(CMD_SetCoordinateY + 3);
	__lcd_write_dat(ey);

	__lcd_write_cmd(CMD_SetPixel);
}


static INLINE void __lcd_read_start(u16 sx,u16 sy,u16 ex,u16 ey)
{
	volatile u16 c;

	__lcd_write_cmd(CMD_SetCoordinateX);
	__lcd_write_dat(sx>>8);
  __lcd_write_cmd(CMD_SetCoordinateX + 1);
	__lcd_write_dat(sx);
  __lcd_write_cmd(CMD_SetCoordinateX + 2);
	__lcd_write_dat(ex>>8);
  __lcd_write_cmd(CMD_SetCoordinateX + 3);
	__lcd_write_dat(ex);

	__lcd_write_cmd(CMD_SetCoordinateY);
	__lcd_write_dat(sy>>8);
  __lcd_write_cmd(CMD_SetCoordinateY + 1);
	__lcd_write_dat(sy);
  __lcd_write_cmd(CMD_SetCoordinateY + 2);
	__lcd_write_dat(ey>>8);
  __lcd_write_cmd(CMD_SetCoordinateY + 3);
	__lcd_write_dat(ey);

	__lcd_write_cmd(0x2E00);
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
			write_cmd(0x3600); // Memory Access Control
			write_dat((0<<7)|(1<<6)|(0<<5)|(0<<3)|(0<<2)|(1<<1));	// 0
			return TRUE;
			////

		case ROTATE_90:
			write_cmd(0x3600); // Memory Access Control
			write_dat((0<<7)|(0<<6)|(1<<5)|(0<<3)|(0<<2)|(1<<1));	// 90
			return TRUE;
			////

		case ROTATE_180:
			write_cmd(0x3600); // Memory Access Control
			write_dat((1<<7)|(0<<6)|(0<<5)|(0<<3)|(0<<2)|(1<<1));	// 180
			return TRUE;
			////

		case ROTATE_270:
			write_cmd(0x3600); // Memory Access Control
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
///NT35510-HSD43
  //PAGE1
  write_cmd(0xF000);    write_dat(0x0055);
  write_cmd(0xF001);    write_dat(0x00AA);
  write_cmd(0xF002);    write_dat(0x0052);
  write_cmd(0xF003);    write_dat(0x0008);
  write_cmd(0xF004);    write_dat(0x0001);

  //Set AVDD 5.2V
  write_cmd(0xB000);    write_dat(0x000D);
  write_cmd(0xB001);    write_dat(0x000D);
  write_cmd(0xB002);    write_dat(0x000D);

  //Set AVEE 5.2V
  write_cmd(0xB100);    write_dat(0x000D);
  write_cmd(0xB101);    write_dat(0x000D);
  write_cmd(0xB102);    write_dat(0x000D);

  //Set VCL -2.5V
  write_cmd(0xB200);    write_dat(0x0000);
  write_cmd(0xB201);    write_dat(0x0000);
  write_cmd(0xB202);    write_dat(0x0000);				

  //Set AVDD Ratio
  write_cmd(0xB600);    write_dat(0x0044);
  write_cmd(0xB601);    write_dat(0x0044);
  write_cmd(0xB602);    write_dat(0x0044);

  //Set AVEE Ratio
  write_cmd(0xB700);    write_dat(0x0034);
  write_cmd(0xB701);    write_dat(0x0034);
  write_cmd(0xB702);    write_dat(0x0034);

  //Set VCL -2.5V
  write_cmd(0xB800);    write_dat(0x0034);
  write_cmd(0xB801);    write_dat(0x0034);
  write_cmd(0xB802);    write_dat(0x0034);
        
  //Control VGH booster voltage rang
  write_cmd(0xBF00);    write_dat(0x0001); //VGH:7~18V	

  //VGH=15V(1V/step)	Free pump
  write_cmd(0xB300);    write_dat(0x000f);		//08
  write_cmd(0xB301);    write_dat(0x000f);		//08
  write_cmd(0xB302);    write_dat(0x000f);		//08

  //VGH Ratio
  write_cmd(0xB900);    write_dat(0x0034);
  write_cmd(0xB901);    write_dat(0x0034);
  write_cmd(0xB902);    write_dat(0x0034);

  //VGL_REG=-10(1V/step)
  write_cmd(0xB500);    write_dat(0x0008);
  write_cmd(0xB501);    write_dat(0x0008);
  write_cmd(0xB502);    write_dat(0x0008);

  write_cmd(0xC200);    write_dat(0x0003);

  //VGLX Ratio
  write_cmd(0xBA00);    write_dat(0x0034);
  write_cmd(0xBA01);    write_dat(0x0034);
  write_cmd(0xBA02);    write_dat(0x0034);

    //VGMP/VGSP=4.5V/0V
  write_cmd(0xBC00);    write_dat(0x0000);		//00
  write_cmd(0xBC01);    write_dat(0x0078);		//C8 =5.5V/90=4.8V
  write_cmd(0xBC02);    write_dat(0x0000);		//01

  //VGMN/VGSN=-4.5V/0V
  write_cmd(0xBD00);    write_dat(0x0000); //00
  write_cmd(0xBD01);    write_dat(0x0078); //90
  write_cmd(0xBD02);    write_dat(0x0000);

  //Vcom=-1.4V(12.5mV/step)
  write_cmd(0xBE00);    write_dat(0x0000);
  write_cmd(0xBE01);    write_dat(0x0064); //HSD:64;Novatek:50=-1.0V, 80  5f

  //Gamma (R+)
  write_cmd(0xD100);    write_dat(0x0000);
  write_cmd(0xD101);    write_dat(0x0033);
  write_cmd(0xD102);    write_dat(0x0000);
  write_cmd(0xD103);    write_dat(0x0034);
  write_cmd(0xD104);    write_dat(0x0000);
  write_cmd(0xD105);    write_dat(0x003A);
  write_cmd(0xD106);    write_dat(0x0000);
  write_cmd(0xD107);    write_dat(0x004A);
  write_cmd(0xD108);    write_dat(0x0000);
  write_cmd(0xD109);    write_dat(0x005C);
  write_cmd(0xD10A);    write_dat(0x0000);
  write_cmd(0xD10B);    write_dat(0x0081);
  write_cmd(0xD10C);    write_dat(0x0000);
  write_cmd(0xD10D);    write_dat(0x00A6);
  write_cmd(0xD10E);    write_dat(0x0000);
  write_cmd(0xD10F);    write_dat(0x00E5);
  write_cmd(0xD110);    write_dat(0x0001);
  write_cmd(0xD111);    write_dat(0x0013);
  write_cmd(0xD112);    write_dat(0x0001);
  write_cmd(0xD113);    write_dat(0x0054);
  write_cmd(0xD114);    write_dat(0x0001);
  write_cmd(0xD115);    write_dat(0x0082);
  write_cmd(0xD116);    write_dat(0x0001);
  write_cmd(0xD117);    write_dat(0x00CA);
  write_cmd(0xD118);    write_dat(0x0002);
  write_cmd(0xD119);    write_dat(0x0000);
  write_cmd(0xD11A);    write_dat(0x0002);
  write_cmd(0xD11B);    write_dat(0x0001);
  write_cmd(0xD11C);    write_dat(0x0002);
  write_cmd(0xD11D);    write_dat(0x0034);
  write_cmd(0xD11E);    write_dat(0x0002);
  write_cmd(0xD11F);    write_dat(0x0067);
  write_cmd(0xD120);    write_dat(0x0002);
  write_cmd(0xD121);    write_dat(0x0084);
  write_cmd(0xD122);    write_dat(0x0002);
  write_cmd(0xD123);    write_dat(0x00A4);
  write_cmd(0xD124);    write_dat(0x0002);
  write_cmd(0xD125);    write_dat(0x00B7);
  write_cmd(0xD126);    write_dat(0x0002);
  write_cmd(0xD127);    write_dat(0x00CF);
  write_cmd(0xD128);    write_dat(0x0002);
  write_cmd(0xD129);    write_dat(0x00DE);
  write_cmd(0xD12A);    write_dat(0x0002);
  write_cmd(0xD12B);    write_dat(0x00F2);
  write_cmd(0xD12C);    write_dat(0x0002);
  write_cmd(0xD12D);    write_dat(0x00FE);
  write_cmd(0xD12E);    write_dat(0x0003);
  write_cmd(0xD12F);    write_dat(0x0010);
  write_cmd(0xD130);    write_dat(0x0003);
  write_cmd(0xD131);    write_dat(0x0033);
  write_cmd(0xD132);    write_dat(0x0003);
  write_cmd(0xD133);    write_dat(0x006D);

  //Gamma (G+)
  write_cmd(0xD200);    write_dat(0x0000);
  write_cmd(0xD201);    write_dat(0x0033);
  write_cmd(0xD202);    write_dat(0x0000);
  write_cmd(0xD203);    write_dat(0x0034);
  write_cmd(0xD204);    write_dat(0x0000);
  write_cmd(0xD205);    write_dat(0x003A);
  write_cmd(0xD206);    write_dat(0x0000);
  write_cmd(0xD207);    write_dat(0x004A);
  write_cmd(0xD208);    write_dat(0x0000);
  write_cmd(0xD209);    write_dat(0x005C);
  write_cmd(0xD20A);    write_dat(0x0000);
  write_cmd(0xD20B);    write_dat(0x0081);
  write_cmd(0xD20C);    write_dat(0x0000);
  write_cmd(0xD20D);    write_dat(0x00A6);
  write_cmd(0xD20E);    write_dat(0x0000);
  write_cmd(0xD20F);    write_dat(0x00E5);
  write_cmd(0xD210);    write_dat(0x0001);
  write_cmd(0xD211);    write_dat(0x0013);
  write_cmd(0xD212);    write_dat(0x0001);
  write_cmd(0xD213);    write_dat(0x0054);
  write_cmd(0xD214);    write_dat(0x0001);
  write_cmd(0xD215);    write_dat(0x0082);
  write_cmd(0xD216);    write_dat(0x0001);
  write_cmd(0xD217);    write_dat(0x00CA);
  write_cmd(0xD218);    write_dat(0x0002);
  write_cmd(0xD219);    write_dat(0x0000);
  write_cmd(0xD21A);    write_dat(0x0002);
  write_cmd(0xD21B);    write_dat(0x0001);
  write_cmd(0xD21C);    write_dat(0x0002);
  write_cmd(0xD21D);    write_dat(0x0034);
  write_cmd(0xD21E);    write_dat(0x0002);
  write_cmd(0xD21F);    write_dat(0x0067);
  write_cmd(0xD220);    write_dat(0x0002);
  write_cmd(0xD221);    write_dat(0x0084);
  write_cmd(0xD222);    write_dat(0x0002);
  write_cmd(0xD223);    write_dat(0x00A4);
  write_cmd(0xD224);    write_dat(0x0002);
  write_cmd(0xD225);    write_dat(0x00B7);
  write_cmd(0xD226);    write_dat(0x0002);
  write_cmd(0xD227);    write_dat(0x00CF);
  write_cmd(0xD228);    write_dat(0x0002);
  write_cmd(0xD229);    write_dat(0x00DE);
  write_cmd(0xD22A);    write_dat(0x0002);
  write_cmd(0xD22B);    write_dat(0x00F2);
  write_cmd(0xD22C);    write_dat(0x0002);
  write_cmd(0xD22D);    write_dat(0x00FE);
  write_cmd(0xD22E);    write_dat(0x0003);
  write_cmd(0xD22F);    write_dat(0x0010);
  write_cmd(0xD230);    write_dat(0x0003);
  write_cmd(0xD231);    write_dat(0x0033);
  write_cmd(0xD232);    write_dat(0x0003);
  write_cmd(0xD233);    write_dat(0x006D);

  //Gamma (B+)
  write_cmd(0xD300);    write_dat(0x0000);
  write_cmd(0xD301);    write_dat(0x0033);
  write_cmd(0xD302);    write_dat(0x0000);
  write_cmd(0xD303);    write_dat(0x0034);
  write_cmd(0xD304);    write_dat(0x0000);
  write_cmd(0xD305);    write_dat(0x003A);
  write_cmd(0xD306);    write_dat(0x0000);
  write_cmd(0xD307);    write_dat(0x004A);
  write_cmd(0xD308);    write_dat(0x0000);
  write_cmd(0xD309);    write_dat(0x005C);
  write_cmd(0xD30A);    write_dat(0x0000);
  write_cmd(0xD30B);    write_dat(0x0081);
  write_cmd(0xD30C);    write_dat(0x0000);
  write_cmd(0xD30D);    write_dat(0x00A6);
  write_cmd(0xD30E);    write_dat(0x0000);
  write_cmd(0xD30F);    write_dat(0x00E5);
  write_cmd(0xD310);    write_dat(0x0001);
  write_cmd(0xD311);    write_dat(0x0013);
  write_cmd(0xD312);    write_dat(0x0001);
  write_cmd(0xD313);    write_dat(0x0054);
  write_cmd(0xD314);    write_dat(0x0001);
  write_cmd(0xD315);    write_dat(0x0082);
  write_cmd(0xD316);    write_dat(0x0001);
  write_cmd(0xD317);    write_dat(0x00CA);
  write_cmd(0xD318);    write_dat(0x0002);
  write_cmd(0xD319);    write_dat(0x0000);
  write_cmd(0xD31A);    write_dat(0x0002);
  write_cmd(0xD31B);    write_dat(0x0001);
  write_cmd(0xD31C);    write_dat(0x0002);
  write_cmd(0xD31D);    write_dat(0x0034);
  write_cmd(0xD31E);    write_dat(0x0002);
  write_cmd(0xD31F);    write_dat(0x0067);
  write_cmd(0xD320);    write_dat(0x0002);
  write_cmd(0xD321);    write_dat(0x0084);
  write_cmd(0xD322);    write_dat(0x0002);
  write_cmd(0xD323);    write_dat(0x00A4);
  write_cmd(0xD324);    write_dat(0x0002);
  write_cmd(0xD325);    write_dat(0x00B7);
  write_cmd(0xD326);    write_dat(0x0002);
  write_cmd(0xD327);    write_dat(0x00CF);
  write_cmd(0xD328);    write_dat(0x0002);
  write_cmd(0xD329);    write_dat(0x00DE);
  write_cmd(0xD32A);    write_dat(0x0002);
  write_cmd(0xD32B);    write_dat(0x00F2);
  write_cmd(0xD32C);    write_dat(0x0002);
  write_cmd(0xD32D);    write_dat(0x00FE);
  write_cmd(0xD32E);    write_dat(0x0003);
  write_cmd(0xD32F);    write_dat(0x0010);
  write_cmd(0xD330);    write_dat(0x0003);
  write_cmd(0xD331);    write_dat(0x0033);
  write_cmd(0xD332);    write_dat(0x0003);
  write_cmd(0xD333);    write_dat(0x006D);

  //Gamma (R-)
  write_cmd(0xD400);    write_dat(0x0000);
  write_cmd(0xD401);    write_dat(0x0033);
  write_cmd(0xD402);    write_dat(0x0000);
  write_cmd(0xD403);    write_dat(0x0034);
  write_cmd(0xD404);    write_dat(0x0000);
  write_cmd(0xD405);    write_dat(0x003A);
  write_cmd(0xD406);    write_dat(0x0000);
  write_cmd(0xD407);    write_dat(0x004A);
  write_cmd(0xD408);    write_dat(0x0000);
  write_cmd(0xD409);    write_dat(0x005C);
  write_cmd(0xD40A);    write_dat(0x0000);
  write_cmd(0xD40B);    write_dat(0x0081);
  write_cmd(0xD40C);    write_dat(0x0000);
  write_cmd(0xD40D);    write_dat(0x00A6);
  write_cmd(0xD40E);    write_dat(0x0000);
  write_cmd(0xD40F);    write_dat(0x00E5);
  write_cmd(0xD410);    write_dat(0x0001);
  write_cmd(0xD411);    write_dat(0x0013);
  write_cmd(0xD412);    write_dat(0x0001);
  write_cmd(0xD413);    write_dat(0x0054);
  write_cmd(0xD414);    write_dat(0x0001);
  write_cmd(0xD415);    write_dat(0x0082);
  write_cmd(0xD416);    write_dat(0x0001);
  write_cmd(0xD417);    write_dat(0x00CA);
  write_cmd(0xD418);    write_dat(0x0002);
  write_cmd(0xD419);    write_dat(0x0000);
  write_cmd(0xD41A);    write_dat(0x0002);
  write_cmd(0xD41B);    write_dat(0x0001);
  write_cmd(0xD41C);    write_dat(0x0002);
  write_cmd(0xD41D);    write_dat(0x0034);
  write_cmd(0xD41E);    write_dat(0x0002);
  write_cmd(0xD41F);    write_dat(0x0067);
  write_cmd(0xD420);    write_dat(0x0002);
  write_cmd(0xD421);    write_dat(0x0084);
  write_cmd(0xD422);    write_dat(0x0002);
  write_cmd(0xD423);    write_dat(0x00A4);
  write_cmd(0xD424);    write_dat(0x0002);
  write_cmd(0xD425);    write_dat(0x00B7);
  write_cmd(0xD426);    write_dat(0x0002);
  write_cmd(0xD427);    write_dat(0x00CF);
  write_cmd(0xD428);    write_dat(0x0002);
  write_cmd(0xD429);    write_dat(0x00DE);
  write_cmd(0xD42A);    write_dat(0x0002);
  write_cmd(0xD42B);    write_dat(0x00F2);
  write_cmd(0xD42C);    write_dat(0x0002);
  write_cmd(0xD42D);    write_dat(0x00FE);
  write_cmd(0xD42E);    write_dat(0x0003);
  write_cmd(0xD42F);    write_dat(0x0010);
  write_cmd(0xD430);    write_dat(0x0003);
  write_cmd(0xD431);    write_dat(0x0033);
  write_cmd(0xD432);    write_dat(0x0003);
  write_cmd(0xD433);    write_dat(0x006D);

  //Gamma (G-)
  write_cmd(0xD500);    write_dat(0x0000);
  write_cmd(0xD501);    write_dat(0x0033);
  write_cmd(0xD502);    write_dat(0x0000);
  write_cmd(0xD503);    write_dat(0x0034);
  write_cmd(0xD504);    write_dat(0x0000);
  write_cmd(0xD505);    write_dat(0x003A);
  write_cmd(0xD506);    write_dat(0x0000);
  write_cmd(0xD507);    write_dat(0x004A);
  write_cmd(0xD508);    write_dat(0x0000);
  write_cmd(0xD509);    write_dat(0x005C);
  write_cmd(0xD50A);    write_dat(0x0000);
  write_cmd(0xD50B);    write_dat(0x0081);
  write_cmd(0xD50C);    write_dat(0x0000);
  write_cmd(0xD50D);    write_dat(0x00A6);
  write_cmd(0xD50E);    write_dat(0x0000);
  write_cmd(0xD50F);    write_dat(0x00E5);
  write_cmd(0xD510);    write_dat(0x0001);
  write_cmd(0xD511);    write_dat(0x0013);
  write_cmd(0xD512);    write_dat(0x0001);
  write_cmd(0xD513);    write_dat(0x0054);
  write_cmd(0xD514);    write_dat(0x0001);
  write_cmd(0xD515);    write_dat(0x0082);
  write_cmd(0xD516);    write_dat(0x0001);
  write_cmd(0xD517);    write_dat(0x00CA);
  write_cmd(0xD518);    write_dat(0x0002);
  write_cmd(0xD519);    write_dat(0x0000);
  write_cmd(0xD51A);    write_dat(0x0002);
  write_cmd(0xD51B);    write_dat(0x0001);
  write_cmd(0xD51C);    write_dat(0x0002);
  write_cmd(0xD51D);    write_dat(0x0034);
  write_cmd(0xD51E);    write_dat(0x0002);
  write_cmd(0xD51F);    write_dat(0x0067);
  write_cmd(0xD520);    write_dat(0x0002);
  write_cmd(0xD521);    write_dat(0x0084);
  write_cmd(0xD522);    write_dat(0x0002);
  write_cmd(0xD523);    write_dat(0x00A4);
  write_cmd(0xD524);    write_dat(0x0002);
  write_cmd(0xD525);    write_dat(0x00B7);
  write_cmd(0xD526);    write_dat(0x0002);
  write_cmd(0xD527);    write_dat(0x00CF);
  write_cmd(0xD528);    write_dat(0x0002);
  write_cmd(0xD529);    write_dat(0x00DE);
  write_cmd(0xD52A);    write_dat(0x0002);
  write_cmd(0xD52B);    write_dat(0x00F2);
  write_cmd(0xD52C);    write_dat(0x0002);
  write_cmd(0xD52D);    write_dat(0x00FE);
  write_cmd(0xD52E);    write_dat(0x0003);
  write_cmd(0xD52F);    write_dat(0x0010);
  write_cmd(0xD530);    write_dat(0x0003);
  write_cmd(0xD531);    write_dat(0x0033);
  write_cmd(0xD532);    write_dat(0x0003);
  write_cmd(0xD533);    write_dat(0x006D);

  //Gamma (B-)
  write_cmd(0xD600);    write_dat(0x0000);
  write_cmd(0xD601);    write_dat(0x0033);
  write_cmd(0xD602);    write_dat(0x0000);
  write_cmd(0xD603);    write_dat(0x0034);
  write_cmd(0xD604);    write_dat(0x0000);
  write_cmd(0xD605);    write_dat(0x003A);
  write_cmd(0xD606);    write_dat(0x0000);
  write_cmd(0xD607);    write_dat(0x004A);
  write_cmd(0xD608);    write_dat(0x0000);
  write_cmd(0xD609);    write_dat(0x005C);
  write_cmd(0xD60A);    write_dat(0x0000);
  write_cmd(0xD60B);    write_dat(0x0081);
  write_cmd(0xD60C);    write_dat(0x0000);
  write_cmd(0xD60D);    write_dat(0x00A6);
  write_cmd(0xD60E);    write_dat(0x0000);
  write_cmd(0xD60F);    write_dat(0x00E5);
  write_cmd(0xD610);    write_dat(0x0001);
  write_cmd(0xD611);    write_dat(0x0013);
  write_cmd(0xD612);    write_dat(0x0001);
  write_cmd(0xD613);    write_dat(0x0054);
  write_cmd(0xD614);    write_dat(0x0001);
  write_cmd(0xD615);    write_dat(0x0082);
  write_cmd(0xD616);    write_dat(0x0001);
  write_cmd(0xD617);    write_dat(0x00CA);
  write_cmd(0xD618);    write_dat(0x0002);
  write_cmd(0xD619);    write_dat(0x0000);
  write_cmd(0xD61A);    write_dat(0x0002);
  write_cmd(0xD61B);    write_dat(0x0001);
  write_cmd(0xD61C);    write_dat(0x0002);
  write_cmd(0xD61D);    write_dat(0x0034);
  write_cmd(0xD61E);    write_dat(0x0002);
  write_cmd(0xD61F);    write_dat(0x0067);
  write_cmd(0xD620);    write_dat(0x0002);
  write_cmd(0xD621);    write_dat(0x0084);
  write_cmd(0xD622);    write_dat(0x0002);
  write_cmd(0xD623);    write_dat(0x00A4);
  write_cmd(0xD624);    write_dat(0x0002);
  write_cmd(0xD625);    write_dat(0x00B7);
  write_cmd(0xD626);    write_dat(0x0002);
  write_cmd(0xD627);    write_dat(0x00CF);
  write_cmd(0xD628);    write_dat(0x0002);
  write_cmd(0xD629);    write_dat(0x00DE);
  write_cmd(0xD62A);    write_dat(0x0002);
  write_cmd(0xD62B);    write_dat(0x00F2);
  write_cmd(0xD62C);    write_dat(0x0002);
  write_cmd(0xD62D);    write_dat(0x00FE);
  write_cmd(0xD62E);    write_dat(0x0003);
  write_cmd(0xD62F);    write_dat(0x0010);
  write_cmd(0xD630);    write_dat(0x0003);
  write_cmd(0xD631);    write_dat(0x0033);
  write_cmd(0xD632);    write_dat(0x0003);
  write_cmd(0xD633);    write_dat(0x006D);

  //PAGE0
  write_cmd(0xF000);    write_dat(0x0055);
  write_cmd(0xF001);    write_dat(0x00AA);
  write_cmd(0xF002);    write_dat(0x0052);
  write_cmd(0xF003);    write_dat(0x0008);	
  write_cmd(0xF004);    write_dat(0x0000); 

  //480x800
  write_cmd(0xB500);    write_dat(0x0050);

  //write_cmd(0x2C00);    write_dat(0x0006); //8BIT 6-6-6?

  //Dispay control
  write_cmd(0xB100);    write_dat(0x00CC);	
  write_cmd(0xB101);    write_dat(0x0000); // S1->S1440:00;S1440->S1:02

  //Source hold time (Nova non-used)
  write_cmd(0xB600);    write_dat(0x0005);

  //Gate EQ control	 (Nova non-used)
  write_cmd(0xB700);    write_dat(0x0077);  //HSD:70;Nova:77	 
  write_cmd(0xB701);    write_dat(0x0077);	//HSD:70;Nova:77

  //Source EQ control (Nova non-used)
  write_cmd(0xB800);    write_dat(0x0001);  
  write_cmd(0xB801);    write_dat(0x0003);	//HSD:05;Nova:07
  write_cmd(0xB802);    write_dat(0x0003);	//HSD:05;Nova:07
  write_cmd(0xB803);    write_dat(0x0003);	//HSD:05;Nova:07

  //Inversion mode: column
  write_cmd(0xBC00);    write_dat(0x0002);	//00: column
  write_cmd(0xBC01);    write_dat(0x0000);	//01:1dot
  write_cmd(0xBC02);    write_dat(0x0000); 

  //Frame rate	(Nova non-used)
  write_cmd(0xBD00);    write_dat(0x0001);
  write_cmd(0xBD01);    write_dat(0x0084);
  write_cmd(0xBD02);    write_dat(0x001c); //HSD:06;Nova:1C
  write_cmd(0xBD03);    write_dat(0x001c); //HSD:04;Nova:1C
  write_cmd(0xBD04);    write_dat(0x0000);

  //LGD timing control(4H/4-delay_ms)
  write_cmd(0xC900);    write_dat(0x00D0);	//3H:0x50;4H:0xD0	 //D
  write_cmd(0xC901);    write_dat(0x0002);  //HSD:05;Nova:02
  write_cmd(0xC902);    write_dat(0x0050);	//HSD:05;Nova:50
  write_cmd(0xC903);    write_dat(0x0050);	//HSD:05;Nova:50	;STV delay_ms time
  write_cmd(0xC904);    write_dat(0x0050);	//HSD:05;Nova:50	;CLK delay_ms time

  write_cmd(0x3600);    write_dat(0x0000);
  write_cmd(0x3500);    write_dat(0x0000);

  write_cmd(0xFF00);    write_dat(0x00AA);
  write_cmd(0xFF01);    write_dat(0x0055);
  write_cmd(0xFF02);    write_dat(0x0025);
  write_cmd(0xFF03);    write_dat(0x0001);

  write_cmd(0xFC00);    write_dat(0x0016);
  write_cmd(0xFC01);    write_dat(0x00A2);
  write_cmd(0xFC02);    write_dat(0x0026);
  write_cmd(0x3A00);    write_dat(0x0006);

  write_cmd(0x3A00);    write_dat(0x0055);
  //Sleep out
  write_cmd(0x1100);	   //?
  delay_ms(1600);

  //Display on
  write_cmd(0x2900);
  
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


/*=========================================================================================*/
