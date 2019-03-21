#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include "fsl_common.h"

/******************************************************************
 * 宏定义
  ******************************************************************/
//WAUP按键
#define CORE_BOARD_WAUP_KEY_GPIO        GPIO5
#define CORE_BOARD_WAUP_KEY_GPIO_PIN    (0U)
#define CORE_BOARD_WAUP_KEY_IOMUXC       IOMUXC_SNVS_WAKEUP_GPIO5_IO00
#define CORE_BOARD_WAUP_KEY_NAME         "CORE_BORE_WAUP_KEY"

//MODE按键
#define CORE_BOARD_MODE_KEY_GPIO        GPIO1
#define CORE_BOARD_MODE_KEY_GPIO_PIN    (5U)
#define CORE_BOARD_MODE_KEY_IOMUXC      IOMUXC_GPIO_AD_B0_05_GPIO1_IO05
#define CORE_BOARD_MODE_KEY_NAME        "CORE_BORE_MODE_KEY"

#define KEY_ON      0   //低电平表示按下按键
#define KEY_OFF     1   

/* 兼容的宏接口 */
#define KEY1_GPIO_PORT      CORE_BOARD_WAUP_KEY_GPIO
#define KEY1_PIN             CORE_BOARD_WAUP_KEY_GPIO_PIN

#define KEY2_GPIO_PORT      CORE_BOARD_MODE_KEY_GPIO
#define KEY2_PIN             CORE_BOARD_MODE_KEY_GPIO_PIN

/*************状态机检测使用的定义****************/
#define KEY_LONG_PRESS_COUNT  3000000 //长按检测时间
#define KEY_FILTERING_COUNT   500     //消抖时间


typedef enum {
  KEY_NOT_PRESS,          //无按下，初始状态
  KEY_PRESSING,           //正在被短按下
  KEY_LONG_PRESSING,      //正在被长按下
  KEY_PRESS_RELEASE,      //短按下操作释放
  KEY_LONG_PRESS_RELEASE, //长按下操作释放
}Key_State;

/******************************************************************
 * 声明
 ******************************************************************/
void Key_GPIO_Config(void);
Key_State Key_Scan_Machine(GPIO_Type* base, uint32_t pin);
uint8_t Key_Scan(GPIO_Type* base, uint32_t pin);

#endif /* __BSP_KEY_H */
