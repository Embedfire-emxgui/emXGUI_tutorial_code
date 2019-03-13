#ifndef __BOARD_H__
#define __BOARD_H__

/*
*************************************************************************
*                             包含的头文件
*************************************************************************
*/
/* STM32 固件库头文件 */
#include "stm32f4xx.h"

/* 开发板硬件bsp头文件 */
#include "./led/bsp_led.h" 
#include "./lcd/bsp_lcd.h"
#include "./sdram/bsp_sdram.h" 
#include "./touch/bsp_i2c_touch.h"
#include "./touch/gt9xx.h"
#include "./usart/bsp_debug_usart.h"
#include "./flash/bsp_spi_flash.h"
#include "./font/fonts.h"



/*
*************************************************************************
*                               函数声明
*************************************************************************
*/
void rt_hw_board_init(void);
void SysTick_Handler(void);
	

#endif /* __BOARD_H__ */
