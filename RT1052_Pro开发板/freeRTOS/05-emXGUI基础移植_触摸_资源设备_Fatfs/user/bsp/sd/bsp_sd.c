/**
******************************************************************
* @file    main.c
* @author  fire
* @version V1.0
* @date    2018-xx-xx
* @brief   SD卡驱动
******************************************************************
* @attention
*
* 实验平台:野火  i.MXRT1052开发板 
* 论坛    :http://www.firebbs.cn
* 淘宝    :http://firestm32.taobao.com
*
******************************************************************
*/
#include "fsl_debug_console.h"

#include "board.h"                      
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_sd.h"
#include "./bsp/sd/bsp_sd.h"
#include "fsl_sdmmc_host.h"



/*Card结构描述符*/
extern sd_card_t g_sd;


/*定义发送缓冲区和接收发送缓冲区，并进行数据对齐
 *说明：
  1.宏SDK_SIZEALIGN(N(数据大小), x)该宏定义的作用是增加N的值直到能被x整除，
 例如 N=6,x=4.则宏定义的结果是8。N=7,x=2宏定义的结果为8.
  2.宏SDK_ALIGN用于实现数据对齐
*/
SDK_ALIGN(uint8_t g_dataWrite[SDK_SIZEALIGN(DATA_BUFFER_SIZE, SDMMC_DATA_BUFFER_ALIGN_CACHE)],
          MAX(SDMMC_DATA_BUFFER_ALIGN_CACHE, SDMMCHOST_DMA_BUFFER_ADDR_ALIGN));
/* 读取数据缓存 */
SDK_ALIGN(uint8_t g_dataRead[SDK_SIZEALIGN(DATA_BUFFER_SIZE, SDMMC_DATA_BUFFER_ALIGN_CACHE)],
          MAX(SDMMC_DATA_BUFFER_ALIGN_CACHE, SDMMCHOST_DMA_BUFFER_ADDR_ALIGN));	



/*
*函数功能：初始化SD卡外部引脚、设置SD卡供电电压
*/
void USDHC1_gpio_init(void)
{
  /*定义GPIO引脚配置结构体*/
  gpio_pin_config_t gpt_config;
  
    /*配置初始化结构体*/
  gpt_config.direction = kGPIO_DigitalOutput; //输出模式
  gpt_config.outputLogic =  1;                //默认高电平
  gpt_config.interruptMode = kGPIO_NoIntmode; //不使用中断
  
  /*SD1_D0*/
  IOMUXC_SetPinMux(USDHC1_DATA0_IOMUXC, 0U);
  IOMUXC_SetPinConfig(USDHC1_DATA0_IOMUXC, USDHC1_DATA_PAD_CONFIG_DATA);
  GPIO_PinInit(USDHC1_DATA0_GPIO, USDHC1_DATA0_GPIO_PIN, &gpt_config);
  
  /*SD1_D1*/
  IOMUXC_SetPinMux(USDHC1_DATA1_IOMUXC, 0U);
  IOMUXC_SetPinConfig(USDHC1_DATA1_IOMUXC, USDHC1_DATA_PAD_CONFIG_DATA);
  GPIO_PinInit(USDHC1_DATA1_GPIO, USDHC1_DATA1_GPIO_PIN, &gpt_config);

  /*SD1_D2*/
  IOMUXC_SetPinMux(USDHC1_DATA2_IOMUXC, 0U);
  IOMUXC_SetPinConfig(USDHC1_DATA2_IOMUXC, USDHC1_DATA_PAD_CONFIG_DATA);
  GPIO_PinInit(USDHC1_DATA2_GPIO, USDHC1_DATA2_GPIO_PIN, &gpt_config);
  
  /*SD1_D3*/
  IOMUXC_SetPinMux(USDHC1_DATA3_IOMUXC, 0U);
  IOMUXC_SetPinConfig(USDHC1_DATA3_IOMUXC, USDHC1_DATA_PAD_CONFIG_DATA);
  GPIO_PinInit(USDHC1_DATA3_GPIO, USDHC1_DATA3_GPIO_PIN, &gpt_config);  
  
  /*SD1_CMD*/
  IOMUXC_SetPinMux(USDHC1_CMD_IOMUXC, 0U);
  IOMUXC_SetPinConfig(USDHC1_CMD_IOMUXC, USDHC1_DATA_PAD_CONFIG_DATA);
  GPIO_PinInit(USDHC1_CMD_GPIO, USDHC1_CMD_GPIO_PIN, &gpt_config);
  
  /*SD1_CLK*/
  IOMUXC_SetPinMux(USDHC1_CLK_IOMUXC, 0U);
  IOMUXC_SetPinConfig(USDHC1_CLK_IOMUXC, USDHC1_CLK_PAD_CONFIG_DATA);
  GPIO_PinInit(USDHC1_CLK_GPIO, USDHC1_CLK_GPIO_PIN, &gpt_config);
  
  /*SD1_POWER*/
  gpt_config.outputLogic =  0;                //默认低电平
  IOMUXC_SetPinMux(SD_POWER_IOMUXC, 0U);
  IOMUXC_SetPinConfig(SD_POWER_IOMUXC, SD_POWER_PAD_CONFIG_DATA);
  GPIO_PinInit(SD_POWER_GPIO, SD_POWER_GPIO_PIN, &gpt_config);
 /*选择 usdhc 输出电压
 *当使用UHS-I协议通讯时，需要把SD总线信号电压降为1.8V，默认为3.0V。本实验不使用UHS-I协议通讯，电压保持默认
 */
  //UDSHC_SelectVoltage(SD_HOST_BASEADDR, SelectVoltage_for_UHS_I_1V8);
}

/**
* 函数功能:初始化USDHC_Host
* 函数参数: sd_struct,SD卡结构体指针；
* 返回值 ：0，成功；-1：失败；
*/
int USDHC_Host_Init(sd_card_t* sd_struct)
{
  sd_card_t *card = sd_struct;
  
  /* 初始化SD外设时钟 */
  BOARD_USDHCClockConfiguration();

  card->host.base = SD_HOST_BASEADDR;
  card->host.sourceClock_Hz = SD_HOST_CLK_FREQ;
  
  /* SD主机初始化函数 */
  if (SD_HostInit(card) != kStatus_Success)
  {
    PRINTF("\r\nSD主机初始化失败\r\n");
    return -1;
  } 
  NVIC_SetPriority(BOARD_SD_HOST_IRQ, 6U); 
  return 0;		
}


/**
* 函数功能:初始化SD卡
* 函数参数: sd_struct,SD卡结构体指针；
* 返回值 ：0，成功；-1：失败；
*/
int SD_Card_Init(sd_card_t* sd_struct)
{
  sd_card_t *card = sd_struct;

  /* Init card. */
  if (SD_CardInit(card))//重新初始化SD卡
  {
    PRINTF("\r\nSD card init failed.\r\n");
    return -1;
  }
  
  return 0;
}

/**
* 函数功能:初始化USDHC时钟
*/
static void BOARD_USDHCClockConfiguration(void)
{
  /*设置系统PLL PFD0 系数为 0x12*/
  CLOCK_InitSysPfd(kCLOCK_Pfd0, 0x12U);
  /* 配置USDHC时钟源和分频系数 */
  CLOCK_SetDiv(kCLOCK_Usdhc1Div, 0U);
  CLOCK_SetMux(kCLOCK_Usdhc1Mux, 1U);
}



/**
* 函数功能:测试SD卡读、写工功能
* 函数参数: sd_struct,SD卡结构体指针；
*/
void SD_Card_Test(sd_card_t* sd_struct)
{
  sd_card_t *card = sd_struct;
    /* 打印卡片工作信息 */
  CardInformationLog(card);
  /* 读写测试 */
  if(AccessCard(card)==kStatus_Success)
    PRINTF("\r\nSDCARD 测试完成.\r\n");
  else
    PRINTF("\r\nSDCARD 测试失败.\r\n");
}

/**
* 函数功能:通过串口输出SD卡信息
* 函数参数: sd_struct,SD卡结构体指针
*/
static void CardInformationLog(sd_card_t *card)
{
  assert(card);
  
  PRINTF("\r\n卡大小 %d * %d bytes\r\n", card->blockCount, card->blockSize);
  PRINTF("\r\n工作条件:\r\n");
  if (card->operationVoltage == kCARD_OperationVoltage330V)
  {
    PRINTF("\r\n  SD卡操作电压 : 3.3V\r\n");
  }
  else if (card->operationVoltage == kCARD_OperationVoltage180V)
  {
    PRINTF("\r\n  SD卡操作电压 : 1.8V\r\n");
  }
  
  if (card->currentTiming == kSD_TimingSDR12DefaultMode)
  {
    if (card->operationVoltage == kCARD_OperationVoltage330V)
    {
      PRINTF("\r\n  时序模式: 常规模式\r\n");
    }
    else if (card->operationVoltage == kCARD_OperationVoltage180V)
    {
      PRINTF("\r\n  时序模式: SDR12 模式\r\n");
    }
  }
  else if (card->currentTiming == kSD_TimingSDR25HighSpeedMode)
  {
    if (card->operationVoltage == kCARD_OperationVoltage180V)
    {
      PRINTF("\r\n  时序模式: SDR25\r\n");
    }
    else
    {
      PRINTF("\r\n  时序模式: High Speed\r\n");
    }
  }
  else if (card->currentTiming == kSD_TimingSDR50Mode)
  {
    PRINTF("\r\n  时序模式: SDR50\r\n");
  }
  else if (card->currentTiming == kSD_TimingSDR104Mode)
  {
    PRINTF("\r\n  时序模式: SDR104\r\n");
  }
  else if (card->currentTiming == kSD_TimingDDR50Mode)
  {
    PRINTF("\r\n  时序模式: DDR50\r\n");
  }
  
  PRINTF("\r\n  Freq : %d HZ\r\n", card->busClock_Hz);
}

/**
* 函数功能:测试SD卡读写功能，并校验写入和读出数据是否一致
* 函数参数: sd_struct,SD卡结构体指针；
*/
static status_t AccessCard(sd_card_t *card)
{

  memset(g_dataWrite, 0x5aU, sizeof(g_dataWrite));
  
  PRINTF("\r\n写入/读取一个数据块......\r\n");
  if (kStatus_Success != SD_WriteBlocks(card, g_dataWrite, DATA_BLOCK_START, 1U))
  {
    PRINTF("写入一个数据块失败.\r\n");
    return kStatus_Fail;
  }
  
  memset(g_dataRead, 0U, sizeof(g_dataRead));
  if (kStatus_Success != SD_ReadBlocks(card, g_dataRead, DATA_BLOCK_START, 1U))
  {
    PRINTF("读取一个数据块.\r\n");
    return kStatus_Fail;
  }
  
  PRINTF("比较读取/写入内容......\r\n");
  if (memcmp(g_dataRead, g_dataWrite, FSL_SDMMC_DEFAULT_BLOCK_SIZE))
  {
    PRINTF("读取/写入内容不一致.\r\n");
    return kStatus_Fail;
  }
  PRINTF("读取/写入内容一致\r\n");
  
  PRINTF("写入/读取多个数据块......\r\n");
  if (kStatus_Success != SD_WriteBlocks(card, g_dataWrite, DATA_BLOCK_START, DATA_BLOCK_COUNT))
  {
    PRINTF("写入多个数据块失败.\r\n");
    return kStatus_Fail;
  }
  
  memset(g_dataRead, 0U, sizeof(g_dataRead));
  
  if (kStatus_Success != SD_ReadBlocks(card, g_dataRead, DATA_BLOCK_START, DATA_BLOCK_COUNT))
  {
    PRINTF("读取多个数据块失败.\r\n");
    return kStatus_Fail;
  }
  
  PRINTF("比较读取/写入内容......\r\n");
  if (memcmp(g_dataRead, g_dataWrite, FSL_SDMMC_DEFAULT_BLOCK_SIZE))
  {
    PRINTF("读取/写入内容不一致.\r\n");
    return kStatus_Fail;
  }
  PRINTF("读取/写入内容一致.\r\n");
  
  PRINTF("擦除多个数据块......\r\n");
  if (kStatus_Success != SD_EraseBlocks(card, DATA_BLOCK_START, DATA_BLOCK_COUNT))
  {
    PRINTF("擦除多个数据块失败.\r\n");
    return kStatus_Fail;
  }
  return kStatus_Success;
}

/****************************END OF FILE**********************/
