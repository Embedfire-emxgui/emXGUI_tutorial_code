/**
  ******************************************************************
  * @file    lcd_test.c
  * @author  fire
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   lcd测试应用接口
  ******************************************************************
  * @attention
  *
  * 实验平台:野火  i.MXRT1052开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************
  */
#include <stdio.h>
 
#include "fsl_elcdif.h"

#include "./lcd/bsp_lcd.h" 


/* 帧率，直接使用上一秒的总帧数
*  使用时需要开启eLCDIF的帧中断，
*  并在systick中进行更新
*/
extern __IO uint32_t s_frame_rate;

/**
 * @note 本函数在不同的优化模式下延时时间不同，
 *       如flexspi_nor_debug和flexspi_nor_release版本的程序中，
 *       flexspi_nor_release版本的延时要短得多  
 */ 
static void delay(uint32_t count)
{
    volatile uint32_t i = 0;
    for (i = 0; i < count; ++i)
    {
        __asm("NOP"); /* 调用nop空指令 */
    }
}

/**
* @brief  往液晶缓冲区填充测试图像
* @param  无
* @retval 无
*/
void LCD_FillFrameBuffer(pixel_t frameBuffer[LCD_MAX_PIXEL_HEIGHT][LCD_MAX_PIXEL_WIDTH])
{
    /* 方块移动速度 */
    #define   SPEED     10
  
    /* Background color. */
    static const pixel_t bgColor = 0U;
    /* Foreground color. */
    static uint8_t fgColorIndex = 0U;
    static const pixel_t fgColorTable[] = {CL_BLUE, CL_GREEN, CL_CYAN, CL_RED,
                                            CL_MAGENTA, CL_YELLOW, CL_WHITE};
    pixel_t fgColor = fgColorTable[fgColorIndex];

    /* Position of the foreground rectangle. */
    static uint16_t upperLeftX = 0U;
    static uint16_t upperLeftY = 0U;
    static uint16_t lowerRightX = (LCD_MIN_PIXEL_WIDTH - 1U) / 2U;
    static uint16_t lowerRightY = (LCD_MIN_PIXEL_HEIGHT - 1U) / 2U;

    static int8_t incX = SPEED;
    static int8_t incY = SPEED;

    /* Change color in next forame or not. */
    static bool changeColor = false;

    uint32_t i, j;

    /* Background color. */
    for (i = 0; i < LCD_PIXEL_HEIGHT; i++)
    {
        for (j = 0; j < LCD_PIXEL_WIDTH; j++)
        {
            frameBuffer[i][j] = bgColor;
        }
    }

    /* Foreground color. */
    for (i = upperLeftY; i < lowerRightY; i++)
    {
        for (j = upperLeftX; j < lowerRightX; j++)
        {
            frameBuffer[i][j] = fgColor;
        }
    }

    /* Update the format: color and rectangle position. */
    upperLeftX += incX;
    upperLeftY += incY;
    lowerRightX += incX;
    lowerRightY += incY;

    changeColor = false;

    if (0U == upperLeftX)
    {
        incX = SPEED;
        changeColor = true;
    }
    else if (LCD_PIXEL_WIDTH - 1 == lowerRightX)
    {
        incX = -SPEED;
        changeColor = true;
    }

    if (0U == upperLeftY)
    {
        incY = SPEED;
        changeColor = true;
    }
    else if (LCD_PIXEL_HEIGHT - 1 == lowerRightY)
    {
        incY = -SPEED;
        changeColor = true;
    }

    if (changeColor)
    {
        fgColorIndex++;

        if (ARRAY_SIZE(fgColorTable) == fgColorIndex)
        {
            fgColorIndex = 0U;
        }
    }
}

/**
* @brief  往液晶缓冲区填充测试图像
* @param  无
* @retval 无
*/
void LCD_ChangeAndSetNextBuffer(void)
{
  static uint8_t frameBufferIndex = 0;

  /* 切换缓冲区号 */
  frameBufferIndex ^= 1U;

  /* 填充下一个缓冲区 */
  LCD_FillFrameBuffer(s_psBufferLcd[frameBufferIndex]);

  /* 设置ELCDIF的下一个缓冲区地址 */
  ELCDIF_SetNextBufferAddr(LCDIF, (uint32_t)s_psBufferLcd[frameBufferIndex]);

  /* 更新中断标志 */
  s_frameDone = false;
  /* 等待直至中断完成 */
  while (!s_frameDone)
  {
  }
}




/*用于测试各种液晶的函数*/
void LCD_Test(void)
{
	/*演示显示变量*/
	static uint8_t testCNT = 0;	
	char dispBuff[100];
	
	testCNT++;	
	
  LCD_Clear(CL_BLACK);	/* 清屏，显示全黑 */

	/*设置字体颜色及字体的背景颜色*/
  LCD_SetColors(CL_WHITE,CL_BLACK);
	
	/*选择字体*/
  LCD_SetFont(&Font24x48);

  LCD_DisplayStringLine(LINE(0),(uint8_t* )"YH 5.0/7.0 inch LCD demo");
  LCD_DisplayStringLine(LINE(1),(uint8_t* )"Image resolution:800x480 px");
  
	if(s_frame_rate)
	{
		/*使用c标准库把变量转化成字符串*/
		sprintf(dispBuff,"Frame Rate: %d Hz",s_frame_rate);
		LCD_DisplayStringLine(LINE(2),(uint8_t* )dispBuff);
	}
	else
	{
	  LCD_DisplayStringLine(LINE(2),(uint8_t* )"Use RT1052-ELCDIF driver");
	}
    
  /*选择字体*/
  LCD_SetFont(&Font16x32);
  LCD_SetTextColor(CL_RED);


	/*使用c标准库把变量转化成字符串*/
	sprintf(dispBuff,"Display value demo: testCount = %d ",testCNT);
	LCD_ClearLine(LINE(5));
	
	/*然后显示该字符串即可，其它变量也是这样处理*/
	LCD_DisplayStringLine(LINE(5),(uint8_t* )dispBuff);


  /* 画直线 */
  LCD_SetTextColor(CL_BLUE);

	LCD_ClearLine(LINE(6));
  LCD_DisplayStringLine(LINE(6),(uint8_t* )"Draw line:");
  
	LCD_SetColors(CL_RED,CL_BLACK);
  LCD_DrawUniLine(50,250,750,250);  
  LCD_DrawUniLine(50,300,750,300);
  
	LCD_SetColors(CL_GREEN,CL_BLACK);
  LCD_DrawUniLine(300,250,400,400);  
  LCD_DrawUniLine(600,250,600,400);
  
  delay(0xFFFFFFF);
  
	LCD_SetColors(CL_BLACK,CL_BLACK);
  LCD_DrawFullRect(0,200,LCD_PIXEL_WIDTH,LCD_PIXEL_HEIGHT-200);
  
  
  /*画矩形*/
  LCD_SetTextColor(CL_BLUE);
	LCD_ClearLine(LINE(6));
  LCD_DisplayStringLine(LINE(6),(uint8_t* )"Draw Rect:");
	
	LCD_SetColors(CL_RED,CL_BLACK);
  LCD_DrawRect(200,250,200,100);
	
	LCD_SetColors(CL_GREEN,CL_BLACK);
  LCD_DrawRect(350,250,200,50);
	
	LCD_SetColors(CL_BLUE,CL_BLACK);
  LCD_DrawRect(200,350,50,100);
  
  delay(0xFFFFFFF);
  
  
	LCD_SetColors(CL_BLACK,CL_BLACK);
  LCD_DrawFullRect(0,200,LCD_PIXEL_WIDTH,LCD_PIXEL_HEIGHT-200);
  

  /*填充矩形*/
  LCD_SetTextColor(CL_BLUE);
	LCD_ClearLine(LINE(6));
	LCD_DisplayStringLine(LINE(6),(uint8_t* )"Draw Full Rect:");

 	LCD_SetColors(CL_RED,CL_BLACK);
  LCD_DrawFullRect(200,250,200,100);
	
	LCD_SetColors(CL_GREEN,CL_BLACK);
  LCD_DrawFullRect(350,250,200,50);
	
	LCD_SetColors(CL_BLUE,CL_BLACK);
  LCD_DrawFullRect(200,350,50,100);
  
  delay(0xFFFFFFF);
  
	LCD_SetColors(CL_BLACK,CL_BLACK);
  LCD_DrawFullRect(0,200,LCD_PIXEL_WIDTH,LCD_PIXEL_HEIGHT-200);
	
  /* 画圆 */
	LCD_SetTextColor(CL_BLUE);
	LCD_ClearLine(LINE(6));
	LCD_DisplayStringLine(LINE(6),(uint8_t* )"Draw circle:");
  
	LCD_SetColors(CL_RED,CL_RED);
  LCD_DrawCircle(200,350,50);
	
	LCD_SetColors(CL_GREEN,CL_GREEN);
  LCD_DrawCircle(350,350,75);
  
  delay(0xFFFFFFF);
  
	LCD_SetColors(CL_BLACK,CL_BLACK);
  LCD_DrawFullRect(0,200,LCD_PIXEL_WIDTH,LCD_PIXEL_HEIGHT-200);


  /*填充圆*/
	LCD_SetTextColor(CL_BLUE);
	LCD_ClearLine(LINE(6));
	LCD_DisplayStringLine(LINE(6),(uint8_t* )"Draw full circle:");
  
	LCD_SetColors(CL_RED,CL_BLACK);
  LCD_DrawFullCircle(300,350,50);
	
	LCD_SetColors(CL_GREEN,CL_BLACK);
  LCD_DrawFullCircle(450,350,75);
  
  delay(0xFFFFFFF);
  
	LCD_SetColors(CL_BLACK,CL_BLACK);
  LCD_DrawFullRect(0,200,LCD_PIXEL_WIDTH,LCD_PIXEL_HEIGHT-200);
	
	LCD_ClearLine(LINE(6));	
 
  delay(0xFFFFFF);
	
	LCD_SetColors(CL_BLACK,CL_BLACK);
  LCD_DrawFullRect(0,200,LCD_PIXEL_WIDTH,LCD_PIXEL_HEIGHT-200);


}
/*********************************************END OF FILE**********************/
