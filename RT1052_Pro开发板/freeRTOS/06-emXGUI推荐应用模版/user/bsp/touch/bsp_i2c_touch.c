/**
  ******************************************************************************
  * @file    bsp_i2c_touch.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   电容触摸屏的专用iic驱动
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  i.MXRT1052开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
#include "fsl_debug_console.h"	

#include "fsl_iomuxc.h"
#include "pin_mux.h"
#include "fsl_gpio.h"
#include "fsl_lpi2c.h"

#include "./delay/core_delay.h"
#include "./touch/bsp_i2c_touch.h"
#include "./touch/bsp_touch_gtxx.h"
#include "./pad_config.h"


/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* I2C的SCL和SDA引脚使用同样的PAD配置 */
#define I2C_PAD_CONFIG_DATA            (SRE_0_SLOW_SLEW_RATE| \
                                        DSE_6_R0_6| \
                                        SPEED_1_MEDIUM_100MHz| \
                                        ODE_0_OPEN_DRAIN_DISABLED| \
                                        PKE_1_PULL_KEEPER_ENABLED| \
                                        PUE_0_KEEPER_SELECTED| \
                                        PUS_3_22K_OHM_PULL_UP| \
                                        HYS_0_HYSTERESIS_DISABLED)   
    /* 配置说明 : */
    /* 转换速率: 转换速率慢
        驱动强度: R0/6 
        带宽配置 : medium(100MHz)
        开漏配置: 关闭 
        拉/保持器配置: 使能
        拉/保持器选择: 保持器
        上拉/下拉选择: 22K欧姆上拉(选择了保持器此配置无效)
        滞回器配置: 禁止 */ 
        

/* 触摸芯片的RST和INT引脚使用同样的PAD配置 */
#define GTP_RST_INT_PAD_CONFIG_DATA            (SRE_0_SLOW_SLEW_RATE| \
                                                DSE_6_R0_6| \
                                                SPEED_1_MEDIUM_100MHz| \
                                                ODE_0_OPEN_DRAIN_DISABLED| \
                                                PKE_1_PULL_KEEPER_ENABLED| \
                                                PUE_0_KEEPER_SELECTED| \
                                                PUS_2_100K_OHM_PULL_UP| \
                                                HYS_0_HYSTERESIS_DISABLED)   
    /* 配置说明 : */
    /* 转换速率: 转换速率慢
        驱动强度: R0/6 
        带宽配置 : medium(100MHz)
        开漏配置: 关闭 
        拉/保持器配置: 使能
        拉/保持器选择: 保持器
        上拉/下拉选择: 100K欧姆上拉(选择了保持器此配置无效)
        滞回器配置: 禁止 */   

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void I2C_GTP_IOMUXC_MUX_Config(void);
static void I2C_GTP_IOMUXC_PAD_Config(void);
static void GTP_I2C_ModeInit(void);

static void I2C_Master_Callback(LPI2C_Type *base, lpi2c_master_handle_t *handle, status_t status, void *userData);
static  uint32_t I2C_Timeout_Callback(uint8_t errorCode);

/*******************************************************************************
 * Variables
 ******************************************************************************/

lpi2c_master_handle_t g_m_handle;
volatile bool g_MasterCompletionFlag = false;
volatile bool g_TouchPadInputSignal = false;
/*******************************************************************************
 * Code
 ******************************************************************************/

/**
  * @brief  对GT91xx芯片进行复位
  * @param  无
  * @retval 无
  */
void GTP_ResetChip(void)
{
	/* 先把RST INT配置为输出模式 */
	gpio_pin_config_t rst_int_config = {kGPIO_DigitalOutput, 0, kGPIO_NoIntmode};

	/* 初始化 RST INT 引脚 */
	GPIO_PinInit(TOUCH_PAD_RST_GPIO, TOUCH_PAD_RST_GPIO_PIN, &rst_int_config);
	GPIO_PinInit(TOUCH_PAD_INT_GPIO, TOUCH_PAD_INT_GPIO_PIN, &rst_int_config);

  /*把gt9157的设备地址被配置为0xBA：
    1.RST、INT低电平
    2.至少延时100us
    3.RST切换为高电平
    4.至少延时5ms
    5.INT切换为浮空输入 */
  
	/*复位为低电平，为初始化做准备*/
	GPIO_PinWrite(TOUCH_PAD_INT_GPIO, TOUCH_PAD_INT_GPIO_PIN, 0U);
	GPIO_PinWrite(TOUCH_PAD_RST_GPIO, TOUCH_PAD_RST_GPIO_PIN, 0U);

	CPU_TS_Tmr_Delay_US(200);

	/*拉高一段时间，进行初始化*/
	GPIO_PinWrite(TOUCH_PAD_RST_GPIO, TOUCH_PAD_RST_GPIO_PIN, 1U);

	CPU_TS_Tmr_Delay_MS(20);

	//INT配置成中断输入
	rst_int_config.direction = kGPIO_DigitalInput;
	rst_int_config.outputLogic = 0;
	rst_int_config.interruptMode = kGPIO_IntRisingEdge;

	GPIO_PinInit(TOUCH_PAD_INT_GPIO, TOUCH_PAD_INT_GPIO_PIN, &rst_int_config);

	/* 使能引脚中断 */  
	GPIO_PortEnableInterrupts(TOUCH_PAD_INT_GPIO, 1U << TOUCH_PAD_INT_GPIO_PIN);
}

/**
* @brief  禁止触摸芯片的中断
* @param  无
* @retval 无
*/
void GTP_IRQDisable(void)
{
	DisableIRQ(TOUCH_PAD_INT_IRQ);
}

/**
* @brief  使能触摸芯片的中断
* @param  无
* @retval 无
*/
void GTP_IRQEnable(void)
{
  gpio_pin_config_t rst_int_config;
   
  //INT配置成中断输入
	rst_int_config.direction = kGPIO_DigitalInput;
	rst_int_config.outputLogic = 0;
	rst_int_config.interruptMode = kGPIO_IntRisingEdge;

	GPIO_PinInit(TOUCH_PAD_INT_GPIO, TOUCH_PAD_INT_GPIO_PIN, &rst_int_config);

	/* 使能引脚中断 */  
	GPIO_PortEnableInterrupts(TOUCH_PAD_INT_GPIO, 1U << TOUCH_PAD_INT_GPIO_PIN);

  /* 使能中断IRQ */  
	EnableIRQ(TOUCH_PAD_INT_IRQ);
}


/**
* @brief  初始化触摸相关IOMUXC的MUX复用配置
* @param  无
* @retval 无
*/
static void I2C_GTP_IOMUXC_MUX_Config(void)
{
  /* SCL和SDA引脚，需要使能SION以接收数据 */
  IOMUXC_SetPinMux(TOUCH_PAD_SCL_IOMUXC, 1U);                                   
  IOMUXC_SetPinMux(TOUCH_PAD_SDA_IOMUXC, 1U);  
	
  /* RST和INT引脚 */
	IOMUXC_SetPinMux(TOUCH_PAD_RST_IOMUXC, 0U);                                   
  IOMUXC_SetPinMux(TOUCH_PAD_INT_IOMUXC, 0U);
}

/**
* @brief  初始化触摸相关IOMUXC的PAD属性配置
* @param  无
* @retval 无
*/
static void I2C_GTP_IOMUXC_PAD_Config(void)
{
  /* SCL和SDA引脚 */
  IOMUXC_SetPinConfig(TOUCH_PAD_SCL_IOMUXC, I2C_PAD_CONFIG_DATA);                               
  IOMUXC_SetPinConfig(TOUCH_PAD_SDA_IOMUXC, I2C_PAD_CONFIG_DATA); 
  
  /* RST和INT引脚 */
  IOMUXC_SetPinConfig(TOUCH_PAD_RST_IOMUXC, GTP_RST_INT_PAD_CONFIG_DATA); 
  IOMUXC_SetPinConfig(TOUCH_PAD_INT_IOMUXC, GTP_RST_INT_PAD_CONFIG_DATA);	    
}


/**
* @brief  初始化触摸芯片使用的I2C外设
* @param  无
* @retval 无
*/	
void GTP_I2C_ModeInit(void)
{
	lpi2c_master_config_t masterConfig;	

	/* 配置时钟 LPI2C */
	CLOCK_SetMux(kCLOCK_Lpi2cMux, LPI2C_CLOCK_SOURCE_SELECT);
	CLOCK_SetDiv(kCLOCK_Lpi2cDiv, LPI2C_CLOCK_SOURCE_DIVIDER);
	
  /*给masterConfig赋值为以下默认配置*/
	/*
	 * masterConfig.debugEnable = false;
	 * masterConfig.ignoreAck = false;
	 * masterConfig.pinConfig = kLPI2C_2PinOpenDrain;
	 * masterConfig.baudRate_Hz = 100000U;
	 * masterConfig.busIdleTimeout_ns = 0;
	 * masterConfig.pinLowTimeout_ns = 0;
	 * masterConfig.sdaGlitchFilterWidth_ns = 0;
	 * masterConfig.sclGlitchFilterWidth_ns = 0;
	 */
	LPI2C_MasterGetDefaultConfig(&masterConfig);

	/* 把默认波特率改为I2C_BAUDRATE */
	masterConfig.baudRate_Hz = GTP_I2C_BAUDRATE;

	/*  使用以上配置初始化 LPI2C 外设 */
	LPI2C_MasterInit(GTP_I2C_MASTER, &masterConfig, LPI2C_MASTER_CLOCK_FREQUENCY);

	/* 创建 LPI2C 非阻塞传输的句柄 */
	LPI2C_MasterTransferCreateHandle(GTP_I2C_MASTER, &g_m_handle, I2C_Master_Callback, NULL);

}


/**
  * @brief   使用IIC读取数据
  * @param   
  * 	@arg ClientAddr:从设备地址
  *		@arg pBuffer:存放由从机读取的数据的缓冲区指针
  *		@arg NumByteToRead:读取的数据长度
  * @note NumByteToRead <= 256
  * @retval  无
  */
uint32_t I2C_ReadBytes(uint8_t ClientAddr,uint8_t* pBuffer, uint16_t NumByteToRead)
{
	lpi2c_master_transfer_t masterXfer = {0};
	status_t reVal = kStatus_Fail;
  /* 400Kbps,传输一个字节(9bits)至少23us，这里按每字节1024us来算*/
  uint32_t i2c_timeout = NumByteToRead<<10;

	/* subAddress = 0x00, data = pBuffer 自从机处接收
		起始信号start + 设备地址slaveaddress(w 写方向) + 子地址subAddress + 
    重复起始信号repeated start + 设备地址slaveaddress(r 读方向) + 
    接收缓冲数据rx data buffer + 停止信号stop */
	masterXfer.slaveAddress = (ClientAddr>>1);
	masterXfer.direction = kLPI2C_Read;
	masterXfer.subaddress = (uint32_t)0;
	masterXfer.subaddressSize = 0;
	masterXfer.data = pBuffer;
	masterXfer.dataSize = NumByteToRead;
	masterXfer.flags = kLPI2C_TransferDefaultFlag;

	reVal = LPI2C_MasterTransferNonBlocking(GTP_I2C_MASTER, &g_m_handle, &masterXfer);
	if (reVal != kStatus_Success)
	{
			return 1;
	}
	/* 复位传输完成标志 */
	g_MasterCompletionFlag = false;

	/* 等待传输完成 */
	while (!g_MasterCompletionFlag)
	{
    CPU_TS_Tmr_Delay_US(1);
    if((i2c_timeout--) == 0) return I2C_Timeout_Callback(0);
	}
	g_MasterCompletionFlag = false;
	
	return 0;
}

/**
  * @brief   使用IIC写入数据
  * @param   
  * 	@arg ClientAddr:从设备地址
  *		@arg pBuffer:缓冲区指针
  *     @arg NumByteToWrite:写的字节数
  * @retval  无
  */
uint32_t I2C_WriteBytes(uint8_t ClientAddr,uint8_t* pBuffer,  uint8_t NumByteToWrite)
{
	lpi2c_master_transfer_t masterXfer = {0};
	status_t reVal = kStatus_Fail;
  /* 400Kbps,传输一个字节(9bits)至少23us，这里按每字节1024us来算*/
  uint32_t i2c_timeout = NumByteToWrite<<10;


	/* subAddress = 0x00, data = pBuffer 发送至从机
		起始信号start + 设备地址slaveaddress(w 写方向) + 
    发送缓冲数据tx data buffer + 停止信号stop */
  
	masterXfer.slaveAddress = (ClientAddr>>1);
	masterXfer.direction = kLPI2C_Write;
	masterXfer.subaddress = (uint32_t)0;
	masterXfer.subaddressSize = 0;
	masterXfer.data = pBuffer;
	masterXfer.dataSize = NumByteToWrite;
	masterXfer.flags = kLPI2C_TransferDefaultFlag;

	reVal = LPI2C_MasterTransferNonBlocking(GTP_I2C_MASTER, &g_m_handle, &masterXfer);
	if (reVal != kStatus_Success)
	{
			return 1;
	}
	/* 复位传输完成标志 */
	g_MasterCompletionFlag = false;

	/* 等待传输完成 */
	while (!g_MasterCompletionFlag)
	{
    CPU_TS_Tmr_Delay_US(1);
    if((i2c_timeout--) == 0) return I2C_Timeout_Callback(1);
	}
	g_MasterCompletionFlag = false;
	
	return 0;

}

/**
  * @brief  IIC等待超时调用本函数输出调试信息
  * @param  None.
  * @retval 返回0xff，表示IIC读取数据失败
  */
static  uint32_t I2C_Timeout_Callback(uint8_t errorCode)
{
  /* Block communication and all processes */
  GTP_ERROR("I2C 等待超时!errorCode = %d",errorCode);
  
  return 0xFF;
}

/**
* @brief  I2C外设传输完成的回调函数
* @param  无
* @retval 无
*/
static void I2C_Master_Callback(LPI2C_Type *base, lpi2c_master_handle_t *handle, status_t status, void *userData)
{		
    /* 接收到kStatus_Success标志后，
       设置g_MasterCompletionFlag标志表明传输成功 */
    if (status == kStatus_Success)
    {
        g_MasterCompletionFlag = true;
    }
}



/**
* @brief  触摸引脚及芯片初始化
* @param  无
* @retval 无
*/
void I2C_Touch_Init(void)
{
  /* 初始化各引脚IOMUXC相关 */
  I2C_GTP_IOMUXC_MUX_Config();
  I2C_GTP_IOMUXC_PAD_Config();

  /* 初始化I2C外设工作模式 */
  GTP_I2C_ModeInit(); 
  
  /* 复位触摸芯片，配置地址 */
  GTP_ResetChip();
 
  GTP_IRQDisable();

//  I2C_GTP_IRQEnable();
}


/***************************中断相关******************************/
/**
* @brief  触摸芯片TOUCH_PAD_INT_GPIO_PIN引脚的中断服务函数
* @param  无
* @retval 无
*/
void TOUCH_PAD_IRQHANDLER(void)
{ 
    /* 确认是触摸芯片的中断 */
    if(GPIO_GetPinsInterruptFlags(TOUCH_PAD_INT_GPIO) & 1U << TOUCH_PAD_INT_GPIO_PIN)
    {
       /* 清除中断标志 */
      GPIO_PortClearInterruptFlags(TOUCH_PAD_INT_GPIO, 1U << TOUCH_PAD_INT_GPIO_PIN);
      /* 切换触摸输入状态标志 */
      g_TouchPadInputSignal = true;

     }

    /* 以下部分是为 ARM 的勘误838869添加的, 
       该错误影响 Cortex-M4, Cortex-M4F内核，       
       立即存储覆盖重叠异常，导致返回操作可能会指向错误的中断
        CM7不受影响，此处保留该代码
    */  
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}

/*********************************************END OF FILE**********************/
