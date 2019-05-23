#ifndef __BSP_NORFLASH_H
#define __BSP_NORFLASH_H

#include "fsl_common.h"

/*******************************************************************************
 * 宏
 ******************************************************************************/


/* FLASH相关特性 */
//#define FLASH_SIZE          (32*1024)  /* 单位为KByte,256Mb = 32768KByte */
#define FLASH_PAGE_SIZE     256     /* 页大小 */
#define SECTOR_SIZE         (4*1024)  /* 扇区大小4K */

/* 使用的FLASH地址宽度，单位：bit */
#define FLASH_ADDR_LENGTH    32              

/* FLASH常用命令 */
#define W25Q_WriteEnable                0x06
#define W25Q_WriteDisable               0x04
#define W25Q_ReadStatusReg              0x05
#define W25Q_WriteStatusReg             0x01
#define W25Q_ReadData                   0x03
#define W25Q_ReadData_4Addr             0x13
#define W25Q_FastReadData               0x0B
#define W25Q_FastReadData_4Addr         0x0C
#define W25Q_FastReadDual               0x3B
#define W25Q_FastReadDual_4Addr         0x3C
#define W25Q_FastReadQuad               0x6B
#define W25Q_FastReadQuad_4Addr         0x6C
#define W25Q_PageProgram                0x02
#define W25Q_PageProgram_4Addr          0x12
#define W25Q_PageProgramQuad            0x32
#define W25Q_PageProgramQuad_4Addr      0x34
#define W25Q_BlockErase                 0xD8
#define W25Q_BlockErase_4Addr           0xDC
#define W25Q_SectorErase                0x20
#define W25Q_SectorErase_4Addr          0x21
#define W25Q_ChipErase                  0xC7
#define W25Q_PowerDown                  0xB9
#define W25Q_ReleasePowerDown           0xAB
#define W25Q_DeviceID                   0xAB
#define W25Q_ManufactDeviceID           0x90
#define W25Q_JedecDeviceID              0x9F
/*其它*/
#define FLASH_ID                        0X18  
#define FLASH_WINBOND_JEDECDEVICE_ID    0XEF4019   
#define FLASH_ISSI_JEDECDEVICE_ID       0X9D6019  

/* FLASH的状态寄存器BUSY位的极性，为1时表示忙碌 */
#define FLASH_BUSY_STATUS_POL       1
/* FLASH的状态寄存器BUSY位的偏移，第0位 */
#define FLASH_BUSY_STATUS_OFFSET    0


/*! @brief FlexSPI引脚定义 */
#define NORFLASH_SS_IOMUXC            IOMUXC_GPIO_SD_B1_06_FLEXSPIA_SS0_B
#define NORFLASH_SCLK_IOMUXC          IOMUXC_GPIO_SD_B1_07_FLEXSPIA_SCLK
#define NORFLASH_DATA00_IOMUXC        IOMUXC_GPIO_SD_B1_08_FLEXSPIA_DATA00
#define NORFLASH_DATA01_IOMUXC        IOMUXC_GPIO_SD_B1_09_FLEXSPIA_DATA01
#define NORFLASH_DATA02_IOMUXC        IOMUXC_GPIO_SD_B1_10_FLEXSPIA_DATA02
#define NORFLASH_DATA03_IOMUXC        IOMUXC_GPIO_SD_B1_11_FLEXSPIA_DATA03

/* FlexSPI_AMBA_BASE是 AHB命令使用的映射地址，值为0x6000 0000 */
/* 把对FLASH访问的地址封装成指针 */
#define NORFLASH_AHB_POINTER(addr)              (void*)(FlexSPI_AMBA_BASE + addr)
/* 8位访问方式 */
#define NORFLASH_AHB_READ_BYTE(addr)            *(uint8_t *)NORFLASH_AHB_POINTER(addr)
#define NORFLASH_AHB_WRITE_BYTE(addr, data)     *(uint8_t *)NORFLASH_AHB_POINTER(addr) = data
/* 16位访问方式 */
#define NORFLASH_AHB_READ_HALFWORD(addr)        *(uint16_t *)NORFLASH_AHB_POINTER(addr)
#define NORFLASH_AHB_WRITE_HALFWORD(addr, data) *(uint16_t *)NORFLASH_AHB_POINTER(addr) = data
/* 32位访问方式 */
#define NORFLASH_AHB_READ_WORD(addr)            *(uint32_t *)NORFLASH_AHB_POINTER(addr)
#define NORFLASH_AHB_WRITE_WORD(addr, data)     *(uint32_t *)NORFLASH_AHB_POINTER(addr) = data

/* 调试使用的宏 */
#define FLASH_DEBUG_ON             1
#define FLASH_DEBUG_ARRAY_ON       1
#define FLASH_DEBUG_FUNC_ON        1
// Log define
#define FLASH_INFO(fmt,arg...)           PRINTF("<<-FLASH-INFO->> "fmt"\n",##arg)
#define FLASH_ERROR(fmt,arg...)          PRINTF("<<-FLASH-ERROR->> "fmt"\n",##arg)
#define FLASH_DEBUG(fmt,arg...)          do{\
                                         if(FLASH_DEBUG_ON)\
                                         PRINTF("<<-FLASH-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
                                          }while(0)

#define FLASH_DEBUG_ARRAY(array, num)    do{\
                                             int32_t i;\
                                             uint8_t* a = array;\
                                             if(FLASH_DEBUG_ARRAY_ON)\
                                             {\
                                                PRINTF("<<-FLASH-DEBUG-ARRAY->>\n");\
                                                for (i = 0; i < (num); i++)\
                                                {\
                                                    PRINTF("%02x   ", (a)[i]);\
                                                    if ((i + 1 ) %10 == 0)\
                                                    {\
                                                        PRINTF("\n");\
                                                    }\
                                                }\
                                                PRINTF("\n");\
                                            }\
                                          }while(0)

#define FLASH_DEBUG_FUNC()             do{\
                                           if(FLASH_DEBUG_FUNC_ON)\
                                           PRINTF("<<-FLASH-FUNC->> Func:%s@Line:%d\n",__func__,__LINE__);\
                                          }while(0)

/*******************************************************************************
 * 函数声明
 ******************************************************************************/
void FlexSPI_NorFlash_Init(void);
status_t FlexSPI_NorFlash_Get_JedecDevice_ID(FLEXSPI_Type *base, uint32_t *vendorID);
status_t FlexSPI_NorFlash_Get_Device_ID(FLEXSPI_Type *base, uint8_t *vendorID);
status_t FlexSPI_NorFlash_Write_Enable(FLEXSPI_Type *base);
status_t FlexSPI_NorFlash_Erase_Sector(FLEXSPI_Type *base, uint32_t dstAddr);
status_t FlexSPI_NorFlash_Wait_Bus_Busy(FLEXSPI_Type *base);
status_t FlexSPI_NorFlash_Write_Status_Register(FLEXSPI_Type *base, uint8_t *config);
status_t FlexSPI_NorFlash_Read_Status_Register(FLEXSPI_Type *base, uint8_t *SR_value);	 
status_t FlexSPI_NorFlash_Enable_Quad_Mode(FLEXSPI_Type *base);

status_t FlexSPI_NorFlash_Page_Program(FLEXSPI_Type *base, 
                                       uint32_t dstAddr, 
                                       uint8_t *src,
                                       uint16_t dataSize);

status_t FlexSPI_NorFlash_Buffer_Program(FLEXSPI_Type *base, 
                                         uint32_t dstAddr, 
                                         uint8_t *src,
                                         uint16_t dataSize);

status_t FlexSPI_NorFlash_Buffer_Read(FLEXSPI_Type *base, 
                                      uint32_t address, 
                                      uint8_t *dst,
                                      uint16_t dataSize);
                                     

                                      
#endif /* __BSP_NORFLASH_H */
