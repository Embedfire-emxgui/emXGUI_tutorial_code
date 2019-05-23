#ifndef __I2C_TOUCH_H
#define	__I2C_TOUCH_H

#include "fsl_common.h"
#include "fsl_lpi2c.h"

extern lpi2c_master_handle_t g_m_handle;
extern volatile bool g_MasterCompletionFlag ;
extern volatile bool g_TouchPadInputSignal;



/* Select USB1 PLL (480 MHz) as master lpi2c clock source */
#define LPI2C_CLOCK_SOURCE_SELECT (0U)
/* Clock divider for master lpi2c clock source */
#define LPI2C_CLOCK_SOURCE_DIVIDER (5U)
/* Get frequency of lpi2c clock */
#define LPI2C_CLOCK_FREQUENCY ((CLOCK_GetFreq(kCLOCK_Usb1PllClk) / 8) / (LPI2C_CLOCK_SOURCE_DIVIDER + 1U))

#define LPI2C_MASTER_CLOCK_FREQUENCY  LPI2C_CLOCK_FREQUENCY

#define GTP_I2C_MASTER_BASE   (LPI2C1_BASE)
#define GTP_I2C_MASTER        ((LPI2C_Type *)GTP_I2C_MASTER_BASE)

#define GTP_I2C_BAUDRATE      400000U

/* 等待超时时间 */
#define I2CT_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define I2CT_LONG_TIMEOUT         ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))


/*! @brief 触摸芯片引脚定义 */

#define TOUCH_PAD_SCL_IOMUXC			  IOMUXC_GPIO_AD_B1_00_LPI2C1_SCL
#define TOUCH_PAD_SDA_IOMUXC			  IOMUXC_GPIO_AD_B1_01_LPI2C1_SDA

#define TOUCH_PAD_RST_GPIO 			    GPIO1
#define TOUCH_PAD_RST_GPIO_PIN 	    (2U)
#define TOUCH_PAD_RST_IOMUXC			  IOMUXC_GPIO_AD_B0_02_GPIO1_IO02

#define TOUCH_PAD_INT_GPIO 			    GPIO1
#define TOUCH_PAD_INT_GPIO_PIN 	    (11U)
#define TOUCH_PAD_INT_IOMUXC			  IOMUXC_GPIO_AD_B0_11_GPIO1_IO11

#define TOUCH_PAD_INT_IRQ 			    GPIO1_Combined_0_15_IRQn
#define TOUCH_PAD_IRQHANDLER        GPIO1_Combined_0_15_IRQHandler



//函数接口
int32_t GTP_I2C_ReadBytes(uint8_t client_addr, uint8_t *buf, int32_t len);

void I2C_Touch_Init(void);
uint32_t I2C_WriteBytes(uint8_t ClientAddr,uint8_t* pBuffer,  uint8_t NumByteToWrite);
uint32_t I2C_ReadBytes(uint8_t ClientAddr,uint8_t* pBuffer, uint16_t NumByteToRead);
void GTP_ResetChip(void);
void GTP_IRQDisable(void);
void GTP_IRQEnable(void);



#endif /* __I2C_TOUCH_H */
