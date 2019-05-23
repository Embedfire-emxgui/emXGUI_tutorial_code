/**
  ******************************************************************
  * @file    bsp_key.c
  * @author  fire
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   按键应用函数接口
  ******************************************************************
  * @attention
  *
  * 实验平台:野火  i.MXRT1052开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************
  */
#include "fsl_iomuxc.h"
#include "fsl_gpio.h" 

#include "pad_config.h" 
#include "./key/bsp_key.h"   

/*******************************************************************
 * 变量定义
 *******************************************************************/
/* GPIO 外设基地址数组 */
static GPIO_Type *const s_gpioBases[] = GPIO_BASE_PTRS;



/******************************************************************
 * 宏
  ******************************************************************/
/* 所有引脚均使用同样的PAD配置 */
#define KEY_PAD_CONFIG_DATA            (SRE_0_SLOW_SLEW_RATE| \
                                        DSE_0_OUTPUT_DRIVER_DISABLED| \
                                        SPEED_2_MEDIUM_100MHz| \
                                        ODE_0_OPEN_DRAIN_DISABLED| \
                                        PKE_1_PULL_KEEPER_ENABLED| \
                                        PUE_1_PULL_SELECTED| \
                                        PUS_3_22K_OHM_PULL_UP| \
                                        HYS_1_HYSTERESIS_ENABLED)   
    /* 配置说明 : */
    /* 转换速率: 转换速率慢
      驱动强度: 关闭
      速度配置 : medium(100MHz)
      开漏配置: 关闭 
      拉/保持器配置: 使能
      拉/保持器选择: 上下拉
      上拉/下拉选择: 22K欧姆上拉
      滞回器配置: 开启 （仅输入时有效，施密特触发器，使能后可以过滤输入噪声）*/

/******************************************************************
 * 声明
  ******************************************************************/
static void Key_IOMUXC_MUX_Config(void);
static void Key_IOMUXC_PAD_Config(void);
static void Key_GPIO_Mode_Config(void);

/******************************************************************
 * 函数代码
  ******************************************************************/
/**
* @brief  初始化按键相关IOMUXC的MUX复用配置
* @param  无
* @retval 无
*/
static void Key_IOMUXC_MUX_Config(void)
{
  /* 设置按键引脚的复用模式为GPIO，不使用SION功能 */
  IOMUXC_SetPinMux(CORE_BOARD_WAUP_KEY_IOMUXC, 0U);
  IOMUXC_SetPinMux(CORE_BOARD_MODE_KEY_IOMUXC, 0U); 
}

/**
* @brief  初始化按键相关IOMUXC的MUX复用配置
* @param  无
* @retval 无
*/
static void Key_IOMUXC_PAD_Config(void)
{
  /* 设置按键引脚属性功能 */    
  IOMUXC_SetPinConfig(CORE_BOARD_WAUP_KEY_IOMUXC, KEY_PAD_CONFIG_DATA); 
  IOMUXC_SetPinConfig(CORE_BOARD_MODE_KEY_IOMUXC, KEY_PAD_CONFIG_DATA); 
}

 /**
  * @brief  初始化按键相关的GPIO模式
  * @param  无
  * @retval 无
  */
static void Key_GPIO_Mode_Config(void)
{     
  /* 定义gpio初始化配置结构体 */
  gpio_pin_config_t key_config; 
    
  /** 核心板的按键，GPIO配置 **/       
  key_config.direction = kGPIO_DigitalInput; //输入模式
  key_config.outputLogic =  1;                //默认高电平（输入模式时无效）
  key_config.interruptMode = kGPIO_NoIntmode; //不使用中断
  
  /* 初始化按键 GPIO. */
  GPIO_PinInit(CORE_BOARD_WAUP_KEY_GPIO, CORE_BOARD_WAUP_KEY_GPIO_PIN, &key_config);
  GPIO_PinInit(CORE_BOARD_MODE_KEY_GPIO, CORE_BOARD_MODE_KEY_GPIO_PIN, &key_config);
}


 /**
  * @brief  初始化控制KEY的IO
  * @param  无
  * @retval 无
  */
void Key_GPIO_Config(void)
{
  /* 初始化GPIO复用、属性、模式 */
  Key_IOMUXC_MUX_Config();
  Key_IOMUXC_PAD_Config();
  Key_GPIO_Mode_Config();
}


/**
  * @brief   检测是否有按键按下 
  * @note   本函数在按键按下时会阻塞，直至释放
  * @param  base:具体的端口
  * @param  pin:具体的引脚号
  * @retval  按键的状态
  *   @arg KEY_ON:按键按下
  *   @arg KEY_OFF:按键没按下
  */
uint8_t Key_Scan(GPIO_Type* base, uint32_t pin)
{     
  /*检测是否有按键按下 */
  if(KEY_ON == GPIO_PinRead(base, pin))
  {  
    /*等待按键释放 */
    while(KEY_ON == GPIO_PinRead(base, pin));   
    return  KEY_ON;  
  }
  else
    return KEY_OFF;
}

/******** 使用状态机的检测方法,不要求掌握*************/

/**
* @brief GPIO base 获取GPIO端口编号
*        本函数从fsl_gpio.c文件复制过来，
*        因该函数是static类型，无法在外部文件调用，
*        又为了保持库文件的原本性，不修改库文件，直接复制至此
*
* @param base GPIO外设基地址指针
* @retval GPIO端口编号
*/
static uint32_t GPIO_GetInstance(GPIO_Type *base)
{
    uint32_t instance;
  
    /* 根据base指针查找出GPIO端口编号 */
    for (instance = 0; instance < ARRAY_SIZE(s_gpioBases); instance++)
    {
        if (s_gpioBases[instance] == base)
        {
            break;
        }
    }
    assert(instance < ARRAY_SIZE(s_gpioBases));
    return instance;
}

 /**
  * @brief  按键检测状态机
  * @note   本函数需要在循环或定时被调用，通过返回值可以获按键状态
  * @param  base:具体的端口
  * @param  pin:具体的引脚号
  * @retval Key_State
  */
Key_State Key_Scan_Machine(GPIO_Type* base, uint32_t pin)
{
  /* 为支持多个按键检测，每个按键有独立的静态变量  */
  static Key_State state[5][16] ={ KEY_NOT_PRESS };
  static uint32_t press_count[5][16] = { 0 };
  static uint32_t filtering_count[5][16] = { 0 };

  switch(state[GPIO_GetInstance(base)-1][pin])
  {
    case KEY_PRESS_RELEASE:
    case KEY_LONG_PRESS_RELEASE:
      //按键释放状态更新为无按下
      state[GPIO_GetInstance(base)-1][pin] = KEY_NOT_PRESS;
      break;
    
    case KEY_NOT_PRESS:
        //检测按下
        if(KEY_ON == GPIO_PinRead(base, pin))
        {
          __asm("NOP"); /* delay */

          //消抖
          if(filtering_count[GPIO_GetInstance(base)-1][pin]++ > KEY_FILTERING_COUNT)
          {
            state[GPIO_GetInstance(base)-1][pin] = KEY_PRESSING; //检测COUNT次后转换状态
            filtering_count[GPIO_GetInstance(base)-1][pin] = 0;
          }
        }   
      break;
        
    case KEY_PRESSING:
        //检测按键释放
        if(KEY_OFF == GPIO_PinRead(base, pin))
        {
          __asm("NOP"); /* delay */

          if(filtering_count[GPIO_GetInstance(base)-1][pin]++ > KEY_FILTERING_COUNT)
          {
            state[GPIO_GetInstance(base)-1][pin] = KEY_PRESS_RELEASE; //检测COUNT次后转换状态
            filtering_count[GPIO_GetInstance(base)-1][pin] = 0;
          }       
        }
        //长按检测
        else if(KEY_ON == GPIO_PinRead(base, pin))
        {
          __asm("NOP"); /* delay */

          if(press_count[GPIO_GetInstance(base)-1][pin]++ > KEY_LONG_PRESS_COUNT)
          {
            state[GPIO_GetInstance(base)-1][pin] = KEY_LONG_PRESSING;//检测COUNT次后转换状态
            press_count[GPIO_GetInstance(base)-1][pin] = 0;
          }
        }   
      break;
        
    case KEY_LONG_PRESSING:
        //检测按键释放
        if(KEY_OFF == GPIO_PinRead(base, pin))
        {
          __asm("NOP"); /* delay */

          if(filtering_count[GPIO_GetInstance(base)-1][pin]++ > KEY_FILTERING_COUNT)
          {
            state[GPIO_GetInstance(base)-1][pin] = KEY_LONG_PRESS_RELEASE; //检测COUNT次后转换状态
            filtering_count[GPIO_GetInstance(base)-1][pin] = 0;
          }       
        }
      break;
  }
  
  return state[GPIO_GetInstance(base)-1][pin];
}

/*********************************************END OF FILE**********************/
