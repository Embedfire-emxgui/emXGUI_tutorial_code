
#include "stm32f10x.h"
#include "board.h"
/*=========================================================================================*/


void FSMC_Init(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;

	  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);

	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOG | RCC_APB2Periph_GPIOE |
	                         RCC_APB2Periph_GPIOF, ENABLE);

	/*-- GPIO Configuration ------------------------------------------------------*/
	  /* SRAM Data lines configuration */
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_9 |
	                                GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOD, &GPIO_InitStructure);

	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
	                                GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 |
	                                GPIO_Pin_15 ;
	  GPIO_Init(GPIOE, &GPIO_InitStructure);

	  /* SRAM Address lines configuration */
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |
	                                GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_12 | GPIO_Pin_13 |
	                                GPIO_Pin_14 | GPIO_Pin_15;
	  GPIO_Init(GPIOF, &GPIO_InitStructure);

	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |
	                                GPIO_Pin_4 | GPIO_Pin_5;
	  GPIO_Init(GPIOG, &GPIO_InitStructure);

	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;
	  GPIO_Init(GPIOD, &GPIO_InitStructure);

	  /* NOE and NWE configuration */
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 |GPIO_Pin_5;
	  GPIO_Init(GPIOD, &GPIO_InitStructure);

	  /* NE3 configuration */
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	  GPIO_Init(GPIOG, &GPIO_InitStructure);

	  /* NE4 configuration */
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	  GPIO_Init(GPIOG, &GPIO_InitStructure);

	  /* NBL0, NBL1 configuration */
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	  GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void FSMC_InitSRAM(void)
{
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef  p;



	 /*-- FSMC Configuration ------------------------------------------------------*/
	  p.FSMC_AddressSetupTime = 2;
	  p.FSMC_AddressHoldTime = 0;
	  p.FSMC_DataSetupTime = 2;
	  p.FSMC_BusTurnAroundDuration = 0;
	  p.FSMC_CLKDivision = 0;
	  p.FSMC_DataLatency = 0;
	  p.FSMC_AccessMode = FSMC_AccessMode_A;


	  FSMC_NORSRAMInitStructure.FSMC_Bank = EXT_SRAM_FSMC_BANK;
	  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
	  FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
	  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
	  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
	  FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;

	  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
	  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
	  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
	  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
	  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
	  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
	  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
	  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct     = &p;

	  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);

	  /* Enable FSMC Bank1_SRAM Bank */
	  FSMC_NORSRAMCmd(EXT_SRAM_FSMC_BANK, ENABLE);
}

void FSMC_InitLCD(void)
{
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef  wr_t,rd_t;

	GPIO_InitTypeDef GPIO_InitStructure;

	//PE2 -> FSMC_A23 - LCD_RS
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);


	wr_t.FSMC_AddressSetupTime      = 0x01;	 //地址建立时间
	wr_t.FSMC_AddressHoldTime       = 0x00;	 //地址保持时间
	wr_t.FSMC_DataSetupTime         = 0x01;	 //数据建立时间
	wr_t.FSMC_BusTurnAroundDuration = 0x00;
	wr_t.FSMC_CLKDivision           = 0x00;
	wr_t.FSMC_DataLatency           = 0x00;
	wr_t.FSMC_AccessMode            = FSMC_AccessMode_B;

	rd_t.FSMC_AddressSetupTime      = 0x01;	 //地址建立时间
	rd_t.FSMC_AddressHoldTime       = 0x00;	 //地址保持时间
	rd_t.FSMC_DataSetupTime         = 0x02;	 //数据建立时间
	rd_t.FSMC_BusTurnAroundDuration = 0x00;
	rd_t.FSMC_CLKDivision           = 0x00;
	rd_t.FSMC_DataLatency           = 0x00;
	rd_t.FSMC_AccessMode            = FSMC_AccessMode_B;

	FSMC_NORSRAMInitStructure.FSMC_Bank                  = EXT_LCD_FSMC_BANK;
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux        = FSMC_DataAddressMux_Disable;
	//FSMC_NORSRAMInitStructure.FSMC_MemoryType          = FSMC_MemoryType_SRAM;
	FSMC_NORSRAMInitStructure.FSMC_MemoryType            = FSMC_MemoryType_NOR;
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth       = FSMC_MemoryDataWidth_16b;
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode       = FSMC_BurstAccessMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait 	 = FSMC_AsynchronousWait_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity    = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_WrapMode              = FSMC_WrapMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive      = FSMC_WaitSignalActive_BeforeWaitState;
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation        = FSMC_WriteOperation_Enable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal            = FSMC_WaitSignal_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode          = FSMC_ExtendedMode_Enable; // 读写使用不同的时序
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst            = FSMC_WriteBurst_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &rd_t;
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct     = &wr_t;

	FSMC_NORSRAMInit ( & FSMC_NORSRAMInitStructure );


	/* 使能 FSMC_Bank1_NORSRAM4 */
	FSMC_NORSRAMCmd ( EXT_LCD_FSMC_BANK, ENABLE );
}

/*=========================================================================================*/
/*=========================================================================================*/









