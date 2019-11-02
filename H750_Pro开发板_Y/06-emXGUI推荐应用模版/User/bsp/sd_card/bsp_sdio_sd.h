#ifndef __STM32H743_SDIO_SD_H
#define __STM32H743_SDIO_SD_H

#include "stm32h7xx.h"
//等待时间
#define SD_TIMEOUT             ((uint32_t)0xFFf00000U)
//块的大小（以字节为单位）
#define BLOCK_SIZE            512 
//块的数目
#define NUMBER_OF_BLOCKS      50
//块的数据大小
#define MULTI_BUFFER_SIZE    (BLOCK_SIZE * NUMBER_OF_BLOCKS)


#define MSD_OK                        ((uint8_t)0x00)
#define MSD_ERROR                     ((uint8_t)0x01)

void BSP_SD_MspInit(void);
HAL_StatusTypeDef BSP_SD_Init(void);
static void SD_EraseTest(void);
static HAL_StatusTypeDef Wait_SDCARD_Ready(void);
static HAL_StatusTypeDef Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint32_t BufferLength);

uint8_t BSP_SD_ReadBlocks(uint32_t *pData, uint64_t ReadAddr,uint32_t NumOfBlocks);
uint8_t BSP_SD_WriteBlocks(uint32_t *pData, uint64_t WriteAddr, uint32_t NumOfBlocks);
uint8_t BSP_SD_ReadBlocks_DMA(uint32_t *pData, uint64_t ReadAddr, uint32_t NumOfBlocks);
uint8_t BSP_SD_WriteBlocks_DMA(uint32_t *pData, uint64_t WriteAddr, uint32_t NumOfBlocks);


void WIFI_PDN_INIT(void);
void SD_Test(void);
void SD_SingleBlockTest(void);
void SD_MultiBlockTest(void);
void Fill_Buffer(uint8_t *pBuffer, uint32_t BufferLength, uint32_t Offset);
#endif 
/************************END OF FILE*******************/
