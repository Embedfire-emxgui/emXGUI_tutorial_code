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

/* 帧数 */
extern __IO uint32_t s_frame_count ;

/* 帧率，直接使用上一秒的总帧数 */
__IO uint32_t s_frame_rate = 0;

/* 进行帧率更新的时间，1000毫秒一次 */
__IO uint32_t s_frame_task_count = 1000;

/*==================================中断方式====================================*/
static __IO uint32_t TimingDelay;
 
/**
  * @brief  启动系统滴答定时器 SysTick
  * @param  无
  * @retval 无
  */
void SysTick_Init(void)
{
  /* SystemFrequency / 1000    1ms中断一次
   * SystemFrequency / 100000  10us中断一次
   * SystemFrequency / 1000000 1us中断一次
   */
  if (SysTick_Config(SystemCoreClock / 1000))
  { 
    /* 错误处理 */ 
    while (1);
  }
}

/**
  * @brief   ms延时程序
  * @param  
  *   @arg nTime: 需要延时多少ms
  * @retval  无
  */
void Delay_ms(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  /* TimingDelay是一个全局变量，在SysTick中断服务函数递减 */
  while(TimingDelay != 0);
}

/**********************中断服务函数******************************/

/**
  * @brief  SysTick中断服务函数
  * @param  无
  * @retval 无
  * @attention
  */
void SysTick_Handler(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
	if(s_frame_task_count != 0)
	{
		s_frame_task_count--;
	}
	else
	{
		s_frame_task_count = 1000;
		s_frame_rate = s_frame_count  ;
		s_frame_count = 0;
	}
}


#if 0
// SysTick_Config在 core_cm7.h中实现
static __INLINE uint32_t SysTick_Config(uint32_t ticks)
{ 
  // reload 寄存器为24bit，最大值为2^24
  if (ticks > SysTick_LOAD_RELOAD_Msk)  return (1);
  
  // 配置 reload 寄存器的初始值  
  SysTick->LOAD  = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;
  
  // 配置中断优先级为 1<<4-1 = 15，优先级为最低
  NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1); 
  
  // 配置 counter 计数器的值
  SysTick->VAL   = 0;
  
  // 配置systick 的时钟为 528M
  // 使能中断
  // 使能systick
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | 
                   SysTick_CTRL_TICKINT_Msk   | 
                   SysTick_CTRL_ENABLE_Msk;                    
  return (0); 
}
#endif

/*==================================查询方式==================================*/
 /*
  * couter 减1的时间 等于 1/systick_clk
  * 当counter 从 reload 的值减小到0的时候，为一个循环，如果开启了中断则执行中断服务程序，
  * 同时 CTRL 的 countflag 位会置1
  * 这一个循环的时间为 reload * (1/systick_clk)
  */

/**
  * @brief  SysTick us延时函数
  * @param  无
  *   @arg us: 需要延时多少us
  * @retval 无
  * @attention
  */
void SysTick_Delay_Us( __IO uint32_t us)
{
  uint32_t i;
  SysTick_Config(SystemCoreClock/1000000);
  
  for(i=0;i<us;i++)
  {
    /* 当计数器的值减小到0的时候，CRTL寄存器的位16会置1 */
    while( !((SysTick->CTRL)&(1<<16)) );
  }
  /* 关闭SysTick定时器 */
  SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;
}

/**
  * @brief  SysTick ms延时函数
  * @param  无
  *   @arg ms: 需要延时多少ms
  * @retval 无
  * @attention
  */
void SysTick_Delay_Ms( __IO uint32_t ms)
{
  uint32_t i; 
  SysTick_Config(SystemCoreClock/1000);
  
  for(i=0;i<ms;i++)
  {
    /* 当计数器的值减小到0的时候，CRTL寄存器的位16会置1
       当置1时，读取该位会清0 */
    while( !((SysTick->CTRL)&(1<<16)) );
  }
  /* 关闭SysTick定时器 */
  SysTick->CTRL &=~ SysTick_CTRL_ENABLE_Msk;
}


/*********************************************END OF FILE**********************/
