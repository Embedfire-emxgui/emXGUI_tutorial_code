/**
  ******************************************************************************
  * @file    bsp_systick.c
  * @author  fire
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   systick函数接口
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  i.MXRT1052开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */

#include "./systick/bsp_systick.h"
/* FreeRTOS头文件 */
#include "FreeRTOS.h"
#include "task.h"
/*==================================中断方式====================================*/

/**********************中断服务函数******************************/

extern void xPortSysTickHandler(void);
extern volatile uint32_t g_eventTimeMilliseconds;
/**
  * @brief  SysTick中断服务函数
  * @param  无
  * @retval 无
  * @attention
  */
void SysTick_Handler(void)
{
    #if (INCLUDE_xTaskGetSchedulerState  == 1 )
      if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
      {
    #endif  /* INCLUDE_xTaskGetSchedulerState */  
        xPortSysTickHandler();
    #if (INCLUDE_xTaskGetSchedulerState  == 1 )
      }
    #endif  /* INCLUDE_xTaskGetSchedulerState */
//#ifdef __CA7_REV
//    SystemClearSystickFlag();
//#endif
//    g_eventTimeMilliseconds++;      
}



/*********************************************END OF FILE**********************/
