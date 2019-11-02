#ifndef __BSP_LCD_H
#define	__BSP_LCD_H

#include "stm32h7xx.h"
/** @addtogroup Utilities
  * @{
  */

/** 
  * @brief  LCD液晶参数
  */   
typedef struct
{
  /*根据液晶数据手册的参数配置*/
  uint8_t hbp;  //HSYNC后的无效像素
  uint8_t vbp;  //VSYNC后的无效行数

  uint8_t hsw;  	//HSYNC宽度
  uint8_t vsw;   //VSYNC宽度

  uint8_t hfp;  	//HSYNC前的无效像素
  uint8_t vfp;  	//VSYNC前的无效行数
  
  uint8_t comment_clock_2byte; //rgb565/argb4444等双字节像素时推荐使用的液晶时钟频率
  uint8_t comment_clock_4byte; //Argb8888等四字节像素时推荐使用的液晶时钟频率

  uint16_t lcd_pixel_width; //液晶分辨率，宽
  uint16_t lcd_pixel_height;//液晶分辨率，高

}LCD_PARAM_TypeDef;


/** 
  * @brief  LCD液晶类型
  */   
typedef enum
{ 
  INCH_5  = 0x00, /* 野火5寸屏 */
  INCH_7,     /* 野火7寸屏 */
  INCH_4_3,  /* 野火4.3寸屏 */
  
  LCD_TYPE_NUM /* LCD类型总数*/
}LCD_TypeDef;

/* 当前使用的LCD，默认为5寸屏 */
extern LCD_TypeDef cur_lcd;
/* 不同液晶屏的参数 */
extern const LCD_PARAM_TypeDef lcd_param[];
/**
  * @brief  Initializes the LCD.
  * @param  None
  * @retval None
  */
/*根据液晶数据手册的参数配置*/
#define HBP  lcd_param[cur_lcd].hbp		//HSYNC后的无效像素
#define VBP  lcd_param[cur_lcd].vbp		//VSYNC后的无效行数

#define HSW  lcd_param[cur_lcd].hsw		//HSYNC宽度
#define VSW  lcd_param[cur_lcd].vsw		//VSYNC宽度

#define HFP  lcd_param[cur_lcd].hfp		//HSYNC前的无效像素
#define VFP  lcd_param[cur_lcd].vfp		//VSYNC前的无效行数


/* LCD Size (Width and Height) */
#define  LCD_PIXEL_WIDTH          lcd_param[cur_lcd].lcd_pixel_width
#define  LCD_PIXEL_HEIGHT         lcd_param[cur_lcd].lcd_pixel_height

/* 使用的各个屏幕中最大的分辨率 */
#define  LCD_MAX_PIXEL_WIDTH    ((uint16_t)800)  
#define  LCD_MAX_PIXEL_HEIGHT   ((uint16_t)480)  

#define  LCD_BUFFER         ((uint32_t)0xD0000000)



//红色数据线
#define LTDC_R0_GPIO_PORT        	GPIOI
#define LTDC_R0_GPIO_CLK_ENABLE()   __GPIOI_CLK_ENABLE()
#define LTDC_R0_GPIO_PIN         	GPIO_PIN_15
#define LTDC_R0_AF			        	GPIO_AF14_LTDC

#define LTDC_R1_GPIO_PORT        	GPIOJ
#define LTDC_R1_GPIO_CLK_ENABLE()   __GPIOJ_CLK_ENABLE()
#define LTDC_R1_GPIO_PIN         	GPIO_PIN_0
#define LTDC_R1_AF			        	GPIO_AF14_LTDC

#define LTDC_R2_GPIO_PORT        	GPIOJ
#define LTDC_R2_GPIO_CLK_ENABLE()	__GPIOJ_CLK_ENABLE()
#define LTDC_R2_GPIO_PIN         	GPIO_PIN_1
#define LTDC_R2_AF			        	GPIO_AF14_LTDC

#define LTDC_R3_GPIO_PORT        	GPIOJ
#define LTDC_R3_GPIO_CLK_ENABLE()	__GPIOJ_CLK_ENABLE()
#define LTDC_R3_GPIO_PIN         	GPIO_PIN_2
#define LTDC_R3_AF			        	GPIO_AF14_LTDC

#define LTDC_R4_GPIO_PORT        	GPIOJ
#define LTDC_R4_GPIO_CLK_ENABLE()	__GPIOJ_CLK_ENABLE()
#define LTDC_R4_GPIO_PIN         	GPIO_PIN_3
#define LTDC_R4_AF			        	GPIO_AF14_LTDC

#define LTDC_R5_GPIO_PORT        	GPIOJ
#define LTDC_R5_GPIO_CLK_ENABLE()	__GPIOJ_CLK_ENABLE()
#define LTDC_R5_GPIO_PIN         	GPIO_PIN_4
#define LTDC_R5_AF			        	GPIO_AF14_LTDC

#define LTDC_R6_GPIO_PORT        	GPIOJ
#define LTDC_R6_GPIO_CLK_ENABLE()	__GPIOJ_CLK_ENABLE()
#define LTDC_R6_GPIO_PIN         	GPIO_PIN_5
#define LTDC_R6_AF			        	GPIO_AF14_LTDC

#define LTDC_R7_GPIO_PORT        	GPIOJ
#define LTDC_R7_GPIO_CLK_ENABLE()	__GPIOJ_CLK_ENABLE()
#define LTDC_R7_GPIO_PIN         	GPIO_PIN_6
#define LTDC_R7_AF			        	GPIO_AF14_LTDC
//绿色数据线
#define LTDC_G0_GPIO_PORT        	GPIOJ
#define LTDC_G0_GPIO_CLK_ENABLE()	__GPIOJ_CLK_ENABLE()
#define LTDC_G0_GPIO_PIN         	GPIO_PIN_7
#define LTDC_G0_AF			        	GPIO_AF14_LTDC

#define LTDC_G1_GPIO_PORT        	GPIOJ
#define LTDC_G1_GPIO_CLK_ENABLE()	__GPIOJ_CLK_ENABLE()
#define LTDC_G1_GPIO_PIN         	GPIO_PIN_8
#define LTDC_G1_AF			        	GPIO_AF14_LTDC

#define LTDC_G2_GPIO_PORT        	GPIOJ
#define LTDC_G2_GPIO_CLK_ENABLE() 	__GPIOJ_CLK_ENABLE()
#define LTDC_G2_GPIO_PIN         	GPIO_PIN_9
#define LTDC_G2_AF			        	GPIO_AF14_LTDC

#define LTDC_G3_GPIO_PORT        	GPIOJ
#define LTDC_G3_GPIO_CLK_ENABLE()	__GPIOJ_CLK_ENABLE()
#define LTDC_G3_GPIO_PIN         	GPIO_PIN_10
#define LTDC_G3_AF			        	GPIO_AF14_LTDC

#define LTDC_G4_GPIO_PORT        	GPIOJ
#define LTDC_G4_GPIO_CLK_ENABLE()	__GPIOJ_CLK_ENABLE()
#define LTDC_G4_GPIO_PIN         	GPIO_PIN_11
#define LTDC_G4_AF			        	GPIO_AF14_LTDC

#define LTDC_G5_GPIO_PORT        	GPIOK
#define LTDC_G5_GPIO_CLK_ENABLE()	__GPIOK_CLK_ENABLE()
#define LTDC_G5_GPIO_PIN         	GPIO_PIN_0
#define LTDC_G5_AF			        	GPIO_AF14_LTDC

#define LTDC_G6_GPIO_PORT        	GPIOK
#define LTDC_G6_GPIO_CLK_ENABLE()	__GPIOK_CLK_ENABLE()
#define LTDC_G6_GPIO_PIN         	GPIO_PIN_1
#define LTDC_G6_AF			        	GPIO_AF14_LTDC

#define LTDC_G7_GPIO_PORT        	GPIOK
#define LTDC_G7_GPIO_CLK_ENABLE() 	__GPIOK_CLK_ENABLE()
#define LTDC_G7_GPIO_PIN         	GPIO_PIN_2
#define LTDC_G7_AF			        	GPIO_AF14_LTDC

//蓝色数据线
#define LTDC_B0_GPIO_PORT        	GPIOJ
#define LTDC_B0_GPIO_CLK_ENABLE()  	__GPIOJ_CLK_ENABLE()
#define LTDC_B0_GPIO_PIN         	GPIO_PIN_12
#define LTDC_B0_AF			        	GPIO_AF14_LTDC

#define LTDC_B1_GPIO_PORT        	GPIOJ
#define LTDC_B1_GPIO_CLK_ENABLE()	__GPIOJ_CLK_ENABLE()
#define LTDC_B1_GPIO_PIN         	GPIO_PIN_13
#define LTDC_B1_AF			        	GPIO_AF14_LTDC

#define LTDC_B2_GPIO_PORT        	GPIOJ
#define LTDC_B2_GPIO_CLK_ENABLE()	__GPIOJ_CLK_ENABLE()
#define LTDC_B2_GPIO_PIN         	GPIO_PIN_14
#define LTDC_B2_AF			        	GPIO_AF14_LTDC

#define LTDC_B3_GPIO_PORT        	GPIOJ
#define LTDC_B3_GPIO_CLK_ENABLE() 	__GPIOJ_CLK_ENABLE()
#define LTDC_B3_GPIO_PIN         	GPIO_PIN_15
#define LTDC_B3_AF			        	GPIO_AF14_LTDC

#define LTDC_B4_GPIO_PORT        	GPIOK
#define LTDC_B4_GPIO_CLK_ENABLE() 	__GPIOK_CLK_ENABLE()
#define LTDC_B4_GPIO_PIN         	GPIO_PIN_3
#define LTDC_B4_AF			        	GPIO_AF14_LTDC

#define LTDC_B5_GPIO_PORT        	GPIOK
#define LTDC_B5_GPIO_CLK_ENABLE()	__GPIOK_CLK_ENABLE()
#define LTDC_B5_GPIO_PIN         	GPIO_PIN_4
#define LTDC_B5_AF			        	GPIO_AF14_LTDC

#define LTDC_B6_GPIO_PORT        	GPIOK
#define LTDC_B6_GPIO_CLK_ENABLE() 	__GPIOK_CLK_ENABLE()
#define LTDC_B6_GPIO_PIN         	GPIO_PIN_5
#define LTDC_B6_AF			        	GPIO_AF14_LTDC

#define LTDC_B7_GPIO_PORT        	GPIOK
#define LTDC_B7_GPIO_CLK_ENABLE()	__GPIOK_CLK_ENABLE()
#define LTDC_B7_GPIO_PIN         	GPIO_PIN_6
#define LTDC_B7_AF			        	GPIO_AF14_LTDC

//控制信号线
/*像素时钟CLK*/
#define LTDC_CLK_GPIO_PORT              GPIOI
#define LTDC_CLK_GPIO_CLK_ENABLE()      __GPIOI_CLK_ENABLE()
#define LTDC_CLK_GPIO_PIN               GPIO_PIN_14
#define LTDC_CLK_AF			            		GPIO_AF14_LTDC
/*水平同步信号HSYNC*/
#define LTDC_HSYNC_GPIO_PORT            GPIOI
#define LTDC_HSYNC_GPIO_CLK_ENABLE()    __GPIOI_CLK_ENABLE()
#define LTDC_HSYNC_GPIO_PIN             GPIO_PIN_12
#define LTDC_HSYNC_AF			       				GPIO_AF14_LTDC
/*垂直同步信号VSYNC*/
#define LTDC_VSYNC_GPIO_PORT            GPIOI
#define LTDC_VSYNC_GPIO_CLK_ENABLE()    __GPIOI_CLK_ENABLE()
#define LTDC_VSYNC_GPIO_PIN             GPIO_PIN_13
#define LTDC_VSYNC_AF			        			GPIO_AF14_LTDC

/*数据使能信号DE*/
#define LTDC_DE_GPIO_PORT               GPIOK
#define LTDC_DE_GPIO_CLK_ENABLE()       __GPIOK_CLK_ENABLE()
#define LTDC_DE_GPIO_PIN                GPIO_PIN_7
#define LTDC_DE_AF			            		GPIO_AF14_LTDC

/*液晶屏背光信号，高电平使能*/
#define LTDC_BL_GPIO_PORT               GPIOD
#define LTDC_BL_GPIO_CLK_ENABLE()       __GPIOD_CLK_ENABLE()
#define LTDC_BL_GPIO_PIN                GPIO_PIN_13

void LCD_Init(uint32_t fb_addr, int lcd_clk_mhz, uint32_t pixel_format );
void LCD_BackLed_Control ( int on );

#endif /* __BSP_LCD_H */
