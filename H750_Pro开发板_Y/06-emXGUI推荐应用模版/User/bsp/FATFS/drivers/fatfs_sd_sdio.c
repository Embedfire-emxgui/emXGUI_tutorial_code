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
#include "./drivers/fatfs_sd_sdio.h"
#include <stdio.h>
#include <string.h>
#include "./sd_card/bsp_sdio_sd.h"
#include "ff_gen_drv.h"
#include "./led/bsp_led.h" 
#include "emXGUI.h"
/* Disk status */
static volatile DSTATUS Stat = STA_NOINIT;
static GUI_SEM *sem_sd = NULL;
static GUI_MUTEX *mutex_lock=NULL;
extern SD_HandleTypeDef uSdHandle;
//发送标志位
extern volatile uint8_t TX_Flag;
//接受标志位
extern volatile uint8_t RX_Flag; 
const Diskio_drvTypeDef  SD_Driver =
{
  SD_initialize,
  SD_status,
  SD_read, 
#if  _USE_WRITE == 1
  SD_write,
#endif /* _USE_WRITE == 1 */
  
#if  _USE_IOCTL == 1
  SD_ioctl,
#endif /* _USE_IOCTL == 1 */
};
DSTATUS SD_initialize(BYTE lun)
{
    Stat = STA_NOINIT;
  
    if(BSP_SD_Init() == HAL_OK)
    {    
        sem_sd = GUI_SemCreate(0,1);//同步摄像头图像
        mutex_lock = GUI_MutexCreate();
        Stat &= ~STA_NOINIT;
    }
    return Stat;
}

DSTATUS SD_status(BYTE lun){

    Stat = STA_NOINIT;
    if(HAL_SD_GetCardState(&uSdHandle) == HAL_SD_CARD_TRANSFER)
    {
        Stat &= ~STA_NOINIT;
    }
    return Stat;
}


DRESULT SD_ReadBlocks(BYTE *buff,//数据缓存区 
                      DWORD sector, //扇区首地址
                      UINT count)//扇区个数(1..128)
{
  DRESULT res = RES_ERROR;  
  uint32_t timeout;
  uint32_t alignedAddr;
  RX_Flag = 0;
  taskENTER_CRITICAL();
  if(HAL_SD_ReadBlocks_DMA(&uSdHandle, (uint8_t*)buff,
                           (uint32_t) (sector),
                           count) == HAL_OK)
  {
    taskEXIT_CRITICAL();
    /* Wait that the reading process is completed or a timeout occurs */
//    timeout = HAL_GetTick();
//    while((RX_Flag == 0) && ((HAL_GetTick() - timeout) < SD_TIMEOUT))
//    {
//    }
//    /* incase of a timeout return error */
//    if (RX_Flag == 0)
//    {
//      res = RES_ERROR;
//    }
//    else
    GUI_SemWait(sem_sd,2000);
    {
//      RX_Flag = 0;
      //timeout = HAL_GetTick();

      //while((HAL_GetTick() - timeout) < SD_TIMEOUT)
      {
        //if (HAL_SD_GetCardState(&uSdHandle) == HAL_SD_CARD_TRANSFER)
        {
          res = RES_OK;

          /*
             the SCB_InvalidateDCache_by_Addr() requires a 32-Byte aligned address,
             adjust the address and the D-Cache size to invalidate accordingly.
           */
          alignedAddr = (uint32_t)buff & ~0x1F;
          //使相应的DCache无效
          SCB_InvalidateDCache_by_Addr((uint32_t*)alignedAddr, count*BLOCKSIZE + ((uint32_t)buff - alignedAddr));

//           break;
        }
      }
    }
  }

  return res;  
}



DRESULT SD_read(BYTE lun,//物理扇区，多个设备时用到(0...)
                BYTE *buff,//数据缓存区 
                DWORD sector, //扇区首地址
                UINT count)//扇区个数(1..128)
{
  DRESULT res = RES_ERROR;
  uint32_t i;
  DWORD pbuff[512/4];	
  
	if((DWORD)buff&3)
    GUI_DEBUG("不对齐");
	{
    GUI_MutexLock(mutex_lock,0xffffff);
	 	for(i=0;i<count;i++)
		{
      //GUI_DEBUG("1");
		 	res = SD_ReadBlocks((BYTE *)pbuff,sector+i,1);//单个sector的读操作
      taskENTER_CRITICAL();
			memcpy(buff,pbuff,512);
      taskEXIT_CRITICAL();
			buff+=512;
		} 
	}
//  else 
//  {
////    GUI_msleep(2);
//    res = SD_ReadBlock(buff,sector,count);	//单个/多个sector     

//  }
  GUI_MutexUnlock(mutex_lock);
  return RES_OK;
}
  
DRESULT SD_write(BYTE lun,//物理扇区，多个设备时用到(0...)
                 const BYTE *buff,//数据缓存区 
                 DWORD sector, //扇区首地址
                 UINT count)//扇区个数(1..128)
{
    DRESULT res = RES_ERROR;
    uint32_t timeout;

  
    TX_Flag = 0;
//    alignedAddr = (uint32_t)buff & ~0x1F;
//    //更新相应的DCache
//    SCB_CleanDCache_by_Addr((uint32_t*)alignedAddr, count*BLOCKSIZE + ((uint32_t)buff - alignedAddr));
    if(HAL_SD_WriteBlocks_DMA(&uSdHandle, (uint8_t*)buff,
                             (uint32_t) (sector),
                             count) == HAL_OK)
    {
      /* Wait that the reading process is completed or a timeout occurs */
      timeout = HAL_GetTick();
      while((TX_Flag == 0) && ((HAL_GetTick() - timeout) < SD_TIMEOUT))
      {
      }
      /* incase of a timeout return error */
      if (TX_Flag == 0)
      {
        res = RES_ERROR;
      }
      else
      {
        TX_Flag = 0;
        timeout = HAL_GetTick();

        while((HAL_GetTick() - timeout) < SD_TIMEOUT)
        {
          if (HAL_SD_GetCardState(&uSdHandle) == HAL_SD_CARD_TRANSFER)
          {
            res = RES_OK;
            //使相应的DCache无效
//            SCB_InvalidateDCache_by_Addr((uint32_t*)alignedAddr, count*BLOCKSIZE + ((uint32_t)buff - alignedAddr));

             break;
          }
        }
      }
    }
    return res;
}



DRESULT SD_ioctl(BYTE lun,BYTE cmd, void *buff){
    DRESULT res = RES_ERROR;
    HAL_SD_CardInfoTypeDef CardInfo;

    if (Stat & STA_NOINIT) return RES_NOTRDY;

    switch (cmd)
    {
    /* Make sure that no pending write process */
    case CTRL_SYNC :
      res = RES_OK;
      break;

    /* Get number of sectors on the disk (DWORD) */
    case GET_SECTOR_COUNT :
      HAL_SD_GetCardInfo(&uSdHandle, &CardInfo);
      *(DWORD*)buff = CardInfo.LogBlockNbr;
      res = RES_OK;
      break;

    /* Get R/W sector size (WORD) */
    case GET_SECTOR_SIZE :
      HAL_SD_GetCardInfo(&uSdHandle, &CardInfo);
      *(WORD*)buff = CardInfo.LogBlockSize;
      res = RES_OK;
      break;

    /* Get erase block size in unit of sector (DWORD) */
    case GET_BLOCK_SIZE :
      HAL_SD_GetCardInfo(&uSdHandle, &CardInfo);
      *(DWORD*)buff = CardInfo.LogBlockSize / BLOCK_SIZE;
      res = RES_OK;
      break;

    default:
      res = RES_PARERR;
    }
    return RES_OK;
}

//SDMMC1发送完成回调函数
void HAL_SD_TxCpltCallback(SD_HandleTypeDef *hsd)
{
  //GUI_SemPostISR(sem_sd);
  TX_Flag=1; //标记写完成
}

//SDMMC1接受完成回调函数
void HAL_SD_RxCpltCallback(SD_HandleTypeDef *hsd)
{
  GUI_SemPostISR(sem_sd);
  RX_Flag=1;
}
/*****************************END OF FILE****************************/

