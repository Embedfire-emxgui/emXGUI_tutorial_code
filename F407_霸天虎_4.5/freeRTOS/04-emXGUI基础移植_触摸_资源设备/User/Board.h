#ifndef		__BOARD_H___
#define		__BOARD_H___

#ifdef	__cplusplus
extern "C"{
#endif

#include <stdio.h>
#include <stdarg.h>

#include "def.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_flash.h"
#include "stm32f4xx_fsmc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_pwr.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_rtc.h"
#include "stm32f4xx_sdio.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_usart.h"

#include "misc.h" /* High level functions for NVIC and SysTick (add-on to CMSIS functions) */

#include "system_stm32f4xx.h"


//#include "drv_inc/bsp_spi_flash.h"
//#include "drv_inc/bsp_eeprom_24xx.h"
//#include "drv_inc/audio_drv.h"
//#include "drv_inc/adc_drv.h"
//#include "spi_flash/bsp_flash_spi.h"
#include "./led/bsp_led.h" 
#include "./uart/bsp_debug_usart.h"
#include "./key/bsp_key.h" 
#include "./touch/gt5xx.h"
#include "./flash/bsp_spi_flash.h"


//#include "Common/drv_inc/my_iic.h"
//#include "Common/drv_inc/my_uart.h"

//#include "Common/SYS/sys.h"
//#include "Common/SDMMC/SDMMC.h"
//#include "Common/I2S/bsp_i2s.h"
//#include "Common/DMA/DMA_LCD.h"

//#include "Components/WM8978/WM8978.h"

#include "gui_drv_cfg.h"

/*=========================================================================================*/

#define	KB	(1024)
#define	MB	(1024*KB)

/*=========================================================================================*/

#define	BOARD_V30	//3.0°æ
//#define	BOARD_V31	//3.1°æ

/*=========================================================================================*/

#define	CCM_BASE				0x10000000
#define	CCM_SIZE				(64*KB)

#define	ONCHIP_SRAM1_BASE		0x20000000
#define	ONCHIP_SRAM1_SIZE		(112*KB)

#define	ONCHIP_SRAM2_BASE		0x2001C000
#define	ONCHIP_SRAM2_SIZE		(16*KB)

#define	FSMC_BANK1_BASE			0x60000000
#define	FSMC_BANK2_BASE			0x64000000
#define	FSMC_BANK3_BASE			0x68000000
#define	FSMC_BANK4_BASE			0x6C000000

#define	EXT_SRAM_BASE	  		FSMC_BANK4_BASE
#define	EXT_SRAM_SIZE			(1024*KB)

#define	EXT_LCD_BASE			FSMC_BANK3_BASE


#define	EXT_SRAM_FSMC_BANK	FSMC_Bank1_NORSRAM4
#define	EXT_LCD_FSMC_BANK	FSMC_Bank1_NORSRAM3

//#define RES_BASE 0x00200000

/*=========================================================================================*/

extern const struct	i2c_ops I2C_GPD7_GPD3;
extern const struct	i2c_ops I2C_GPB8_GPB9;

/*=========================================================================================*/

void* dma_mem_alloc(u32 size);
void  dma_mem_free(void *p);

/*=========================================================================================*/


extern const char TargetBoard_IO[];

/*=========================================================================================*/

#ifdef	__cplusplus
}
#endif

#endif	/*__BOARD_H___*/
