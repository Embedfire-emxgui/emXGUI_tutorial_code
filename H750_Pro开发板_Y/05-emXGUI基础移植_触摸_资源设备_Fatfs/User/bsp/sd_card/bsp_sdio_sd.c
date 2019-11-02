/**
  ******************************************************************************
  * @file    bsp_sdio_sd.c
  * @author  fire
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   SDIO sd卡测试驱动（不含文件系统）
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火  STM32 H743 开发板  
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
#include "./sd_card/bsp_sdio_sd.h"
#include "./led/bsp_led.h"   

#include "FreeRTOS.h"
#include "task.h"

SD_HandleTypeDef uSdHandle;

uint8_t Buffer_Block_Tx[MULTI_BUFFER_SIZE/4];
uint8_t Buffer_Block_Rx[MULTI_BUFFER_SIZE/4];
//发送标志位
volatile uint8_t TX_Flag=0;
//接受标志位
volatile uint8_t RX_Flag=0; 
/**
  * @brief  SD_Card测试函数
  * @param  无
  * @retval 无
  */
void SD_Test(void)
{
    LED_BLUE;
    /*------------------------------ SD 初始化 ------------------------------ */
    if(BSP_SD_Init() != HAL_OK)
    {    
        LED_RED;
        printf("SD卡初始化失败，请确保SD卡已正确接入开发板，或换一张SD卡测试！\n");
    }
    else
    {
        printf("SD卡初始化成功！\n");	     
        LED_BLUE;
        /*擦除测试*/
        SD_EraseTest();

        LED_BLUE;
        /*single block 读写测试*/
        SD_SingleBlockTest();

        LED_BLUE;
        /*muti block 读写测试*/
        SD_MultiBlockTest(); 
    } 
} 
void BSP_SD_MspDeInit(SD_HandleTypeDef *hsd, void *Params)
{
  /* 禁用SDIC中断*/
  HAL_NVIC_DisableIRQ(SDMMC1_IRQn);

  /* 禁用SDMMC1时钟 */
  __HAL_RCC_SDMMC1_CLK_DISABLE();

}
uint8_t BSP_SD_DeInit(void)
{ 
  uint8_t sd_state = HAL_OK;
 
  uSdHandle.Instance = SDMMC1;
  
  /* 取消初始化SD卡设备 */
  if(HAL_SD_DeInit(&uSdHandle) != HAL_OK)
  {
    sd_state = MSD_ERROR;
  }

  /* 取消初始化SD底层驱动 */
  uSdHandle.Instance = SDMMC1;
  BSP_SD_MspDeInit(&uSdHandle, NULL);
  
  return  sd_state;
}

/**
  * @brief  初始化SDMMC1及SD卡
  * @param  无
  * @retval HAL_OK：初始化成功；HAL_ERROR：初始化失败
  */
HAL_StatusTypeDef BSP_SD_Init(void)
{ 
  uint8_t sd_state = HAL_OK;
  //BSP_SD_DeInit();
  /* 定义SDMMC句柄 */
  uSdHandle.Instance = SDMMC1;
  
	/* SDMMC内核时钟200Mhz, SDCard时钟25Mhz  */
  uSdHandle.Init.ClockEdge           = SDMMC_CLOCK_EDGE_RISING;
  uSdHandle.Init.ClockPowerSave      = SDMMC_CLOCK_POWER_SAVE_DISABLE;
  uSdHandle.Init.BusWide             = SDMMC_BUS_WIDE_4B;
  uSdHandle.Init.HardwareFlowControl = SDMMC_HARDWARE_FLOW_CONTROL_DISABLE;
  uSdHandle.Init.ClockDiv            = 0;
  
  /* 初始化SD底层驱动 */
  BSP_SD_MspInit();

  /* HAL SD 初始化 */
  if(HAL_SD_Init(&uSdHandle) != HAL_OK)
  {
    sd_state = MSD_ERROR;
  }
//    /* 配置SD总线位宽 */
//  if(sd_state == HAL_OK)
//  {
//    /* 配置为4bit模式 */
//    if(HAL_SD_ConfigWideBusOperation(&uSdHandle, uSdHandle.Init.BusWide) != HAL_OK)
//    {
//      sd_state = HAL_ERROR;
//    }
//    else
//    {
//      sd_state = HAL_OK;
//    }
//  }

  return  sd_state;
}
/**
  * @brief  SD卡擦除测试
  * @param  无
  * @retval 无
  */
static void SD_EraseTest(void)
{
    HAL_StatusTypeDef Status = HAL_OK;
    HAL_StatusTypeDef EraseStatus = HAL_OK;
    if (Status == HAL_OK)
    {
        Status = HAL_SD_Erase(&uSdHandle, 0x00, (BLOCK_SIZE * NUMBER_OF_BLOCKS));
        if(Wait_SDCARD_Ready() != HAL_OK)
        {
            EraseStatus = HAL_ERROR;
        }
    }     
    if(EraseStatus == HAL_OK)
    {    
      LED_GREEN;
      printf("SD卡擦除测试成功！\n");
    }
    else
    {
      LED_RED;
      printf("SD卡擦除测试失败！\n");
      printf("温馨提示：部分SD卡不支持擦除测试，若SD卡能通过下面的single读写测试，即表示SD卡能够正常使用。\n");
    }    
}

/**
  * @brief  SD卡单块读写测试
  * @param  无
  * @retval 无
  */
void SD_SingleBlockTest(void)
{
    HAL_StatusTypeDef Status =  HAL_OK;
    HAL_StatusTypeDef TransferStatus1 = HAL_ERROR;
    /* Fill the buffer to send */
    Fill_Buffer(Buffer_Block_Tx, BLOCK_SIZE/4, 0);    
    SCB_CleanDCache_by_Addr((uint32_t*)Buffer_Block_Tx, BLOCK_SIZE/4);
    if(Status == HAL_OK)
    {
        /* Write block of 512 bytes on address 0 */
        Status = HAL_SD_WriteBlocks_DMA(&uSdHandle, Buffer_Block_Tx, 0x00, 1);
        while(TX_Flag == 0);
    } 
    /* Fill the buffer to reception */
    Fill_Buffer(Buffer_Block_Rx, BLOCK_SIZE/4, 0);   
    SCB_CleanDCache_by_Addr((uint32_t*)Buffer_Block_Rx, BLOCK_SIZE/4); 
    if(Status == HAL_OK)
    {
        /* Read block of 512 bytes from address 0 */
        Status = HAL_SD_ReadBlocks_DMA(&uSdHandle, Buffer_Block_Rx,0, 1);
        while(RX_Flag == 0);
    }    
    if (Status == HAL_OK)
    {
        TransferStatus1 = Buffercmp(Buffer_Block_Tx, Buffer_Block_Rx, BLOCK_SIZE/4);
    }
    if(TransferStatus1 == HAL_OK)
    {
        LED_GREEN;
        printf("Single block 测试成功！\n");
    }
    else
    {
        LED_RED;
        printf("Single block 测试失败，请确保SD卡正确接入开发板，或换一张SD卡测试！\n");
    }
}
/**
  * @brief  SD卡多块读写测试
  * @param  无
  * @retval 无
  */
void SD_MultiBlockTest(void)
{ 
    HAL_StatusTypeDef Status =  HAL_OK;
    HAL_StatusTypeDef TransferStatus1 = HAL_ERROR;
    TX_Flag = 0;
    RX_Flag = 0; 
    /* Fill the buffer to send */
    Fill_Buffer(Buffer_Block_Tx, MULTI_BUFFER_SIZE/4, 0);    
    SCB_CleanDCache_by_Addr((uint32_t*)Buffer_Block_Tx, MULTI_BUFFER_SIZE/4);
    if(Status == HAL_OK)
    {
        /* Write block of 512 bytes on address 0 */
        Status = HAL_SD_WriteBlocks_DMA(&uSdHandle, (uint8_t *)Buffer_Block_Tx, 0,  NUMBER_OF_BLOCKS);
        while(TX_Flag == 0);
    } 
    /* Fill the buffer to reception */
    Fill_Buffer(Buffer_Block_Rx, MULTI_BUFFER_SIZE/4, 0);   
    SCB_CleanDCache_by_Addr((uint32_t*)Buffer_Block_Rx, MULTI_BUFFER_SIZE/4); 
    if(Status == HAL_OK)
    {
        /* Read block of 512 bytes from address 0 */
        Status = HAL_SD_ReadBlocks_DMA(&uSdHandle, (uint8_t *)Buffer_Block_Rx,0, NUMBER_OF_BLOCKS);
        while(RX_Flag == 0);
    }    
    if (Status == HAL_OK)
    {
        TransferStatus1 = Buffercmp(Buffer_Block_Tx, Buffer_Block_Rx, MULTI_BUFFER_SIZE/4);
    }
    if(TransferStatus1 == HAL_OK)
    {
        LED_GREEN;
        printf("Multi block 测试成功！\n");
    }
    else
    {
        LED_RED;
        printf("Multi block 测试失败，请确保SD卡正确接入开发板，或换一张SD卡测试！\n");
    }
}

/**
  * @brief  SD卡等待擦除完成函数
  * @param  无
  * @retval HAL_OK：擦除成功；HAL_ERROR：擦除失败
  */
static HAL_StatusTypeDef Wait_SDCARD_Ready(void)
{
    uint32_t loop = SD_TIMEOUT;
    
    /* Wait for the Erasing process is completed */
    /* Verify that SD card is ready to use after the Erase */
    while(loop > 0)
    {
      loop--;
      if(HAL_SD_GetCardState(&uSdHandle) == HAL_SD_CARD_TRANSFER)
      {
          return HAL_OK;
      }
    }
    return HAL_ERROR;
}
/**
  * @brief  数组匹配检测函数
  * @param  pBuffer1：发送数组；pBuffer2：接受数组；BufferLength：数组长度
  * @retval HAL_OK：匹配；HAL_ERROR：不匹配
  */
static HAL_StatusTypeDef Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint32_t BufferLength)
{
    while (BufferLength--)
    {
      if (*pBuffer1 != *pBuffer2)
      {      
        return HAL_ERROR;      
      }
      else{

        pBuffer1++;
        pBuffer2++;
      }
    }
    return HAL_OK;
}


/**
  * @brief  Fills buffer with user predefined data.
  * @param  pBuffer: pointer on the Buffer to fill
  * @param  BufferLength: size of the buffer to fill
  * @param  Offset: first value to fill on the Buffer
  * @retval None
  */
void Fill_Buffer(uint8_t *pBuffer, uint32_t BufferLength, uint32_t Offset)
{
  uint32_t index = 0;
  /* Put in global buffer same values */
  for (index = 0; index < BufferLength; index++)
  {
    pBuffer[index] = index + Offset;
  }
}
/**
  * @brief  禁用WIFI模块
  * @param  无
  * @param  无
  * @retval 无
  */
void WIFI_PDN_INIT(void)
{
    /*定义一个GPIO_InitTypeDef类型的结构体*/
    GPIO_InitTypeDef GPIO_InitStruct;
    /*使能引脚时钟*/	
    __HAL_RCC_GPIOC_CLK_ENABLE();
    /*选择要控制的GPIO引脚*/															   
    GPIO_InitStruct.Pin = GPIO_PIN_2;	
    /*设置引脚的输出类型为推挽输出*/
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;      
    /*设置引脚为上拉模式*/
    GPIO_InitStruct.Pull  = GPIO_PULLUP;
    /*设置引脚速率为高速 */   
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; 
    /*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO*/
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);	
    /*禁用WiFi模块*/
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_RESET);  
}
/**
  * @brief  在轮询模式下从SD卡中的指定地址读取块
  * @param  pData: 指向将包含要传输的数据的缓冲区的指针
  * @param  ReadAddr: 从哪里读取数据的地址  
  * @param  NumOfBlocks: 读取的扇区数 
  * @retval SD 状态
  */
uint8_t BSP_SD_ReadBlocks(uint32_t *pData, uint64_t ReadAddr, uint32_t NumOfBlocks)
{
  
  if(HAL_SD_ReadBlocks(&uSdHandle,(uint8_t *)pData, ReadAddr,NumOfBlocks,SD_TIMEOUT) == HAL_OK)
  {
    return HAL_OK;
  }
  else
  {
    return MSD_ERROR;
  }
}

/**
  * @brief  在轮询模式下从SD卡中的指定地址写入块 
  * @param  pData: 指向将包含要传输的数据的缓冲区的指针
  * @param  WriteAddr: 从哪里读取数据的地址  
  * @param  NumOfBlocks: 读取的扇区数 
  * @retval SD 状态
  */
uint8_t BSP_SD_WriteBlocks(uint32_t *pData, uint64_t WriteAddr,uint32_t NumOfBlocks)
{
  if(HAL_SD_WriteBlocks(&uSdHandle,(uint8_t *)pData, WriteAddr,NumOfBlocks,SD_TIMEOUT) == HAL_OK)
  {
    
    return MSD_OK;
  }
  else
  {
    return MSD_ERROR;
  }
}

/**
  * @brief  以DMA方式从SD卡中的指定地址读取块
  * @param  pData: 指向将包含要传输的数据的缓冲区的指针
  * @param  ReadAddr: 从哪里读取数据的地址  
  * @param  NumOfBlocks: 读取的扇区数 
  * @retval SD 状态
  */
uint8_t BSP_SD_ReadBlocks_DMA(uint32_t *pData, uint64_t ReadAddr, uint32_t NumOfBlocks)
{ 
  taskENTER_CRITICAL();
  /* 以DMA方式从SD卡中的指定地址读取块 */
  if(HAL_SD_ReadBlocks_DMA(&uSdHandle, (uint8_t *)pData, ReadAddr,NumOfBlocks) == HAL_OK)
  {
    taskEXIT_CRITICAL();	
    return MSD_OK;
  }
  else
  {
    taskEXIT_CRITICAL();	
    return MSD_ERROR;
  }
}

/**
  * @brief  以DMA方式从SD卡中的指定地址写入块
  * @param  pData: 指向将包含要传输的数据的缓冲区的指针
  * @param  ReadAddr: 从哪里写入数据的地址  
  * @param  NumOfBlocks: 读取的扇区数 
  * @retval SD 状态
  */
uint8_t BSP_SD_WriteBlocks_DMA(uint32_t *pData, uint64_t WriteAddr, uint32_t NumOfBlocks)
{  

  /* 以DMA方式从SD卡中的指定地址写入块 */
  if(HAL_SD_WriteBlocks_DMA(&uSdHandle, (uint8_t *)pData, WriteAddr, NumOfBlocks) == HAL_OK)
  {

    return MSD_OK;
  }
  else
  {

    return MSD_ERROR;
  }
}
/**
  * @brief  初始化SD外设
  * @param  无
  * @param  无
  * @retval None
  */
void BSP_SD_MspInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    /* 使能 SDMMC 时钟 */
    __HAL_RCC_SDMMC1_CLK_ENABLE();
//    HAL_RCCEx_GetPLL1ClockFreq(&PLL1_Clocks);
    /* 使能 GPIOs 时钟 */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
  
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11 
                          |GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_SDIO1;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_SDIO1;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
    //禁用WIFI模块
    WIFI_PDN_INIT();
        
    HAL_NVIC_SetPriority(SDMMC1_IRQn,0x7,0);  //配置SDMMC1中断
    HAL_NVIC_EnableIRQ(SDMMC1_IRQn);        //使能SDMMC1中断
    
    HAL_NVIC_SetPriority(SysTick_IRQn, 0x0E ,0);
}

void SDMMC1_IRQHandler(void)
{
//  uint32_t ulReturn;
//  /* 进入临界段，临界段可以嵌套 */
//  ulReturn = taskENTER_CRITICAL_FROM_ISR(); 
  HAL_SD_IRQHandler(&uSdHandle);
		
  /* 退出临界段 */
//  taskEXIT_CRITICAL_FROM_ISR( ulReturn );  
}
/************************END OF FILE*******************/
