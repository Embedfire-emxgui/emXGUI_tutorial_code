/**
  ******************************************************************
  * @file    bsp_norflash.c
  * @author  fire
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   nor flash驱动
  ******************************************************************
  * @attention
  *
  * 实验平台:野火  i.MXRT1052开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************
  */
#include "fsl_flexspi.h"
#include "fsl_debug_console.h"

#include "fsl_iomuxc.h"
#include "pin_mux.h"
#include "board.h"
#include "clock_config.h"
#include "fsl_common.h"

#include "pad_config.h"
#include "./norflash/bsp_norflash.h"  
#include "./delay/core_delay.h"  

/*******************************************************************************
* Definitions
******************************************************************************/
/* 定义指令在查找表中的编号 */
#define NOR_CMD_LUT_SEQ_IDX_READ_NORMAL                 0
#define NOR_CMD_LUT_SEQ_IDX_READ_FAST                   1
#define NOR_CMD_LUT_SEQ_IDX_READ_FAST_QUAD              2
#define NOR_CMD_LUT_SEQ_IDX_READSTATUS                  3
#define NOR_CMD_LUT_SEQ_IDX_WRITEENABLE                 4
#define NOR_CMD_LUT_SEQ_IDX_ERASESECTOR                 5
#define NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_SINGLE          6
#define NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_QUAD            7
#define NOR_CMD_LUT_SEQ_IDX_READID                      8
#define NOR_CMD_LUT_SEQ_IDX_READJEDECID                 9
#define NOR_CMD_LUT_SEQ_IDX_WRITESTATUSREG              10
#define NOR_CMD_LUT_SEQ_IDX_READSTATUSREG               11
#define NOR_CMD_LUT_SEQ_IDX_ERASECHIP                   12
#define NOR_CMD_LUT_SEQ_IDX_AHB_PAGEPROGRAM_QUAD_1      13
#define NOR_CMD_LUT_SEQ_IDX_AHB_PAGEPROGRAM_QUAD_2      14
#define NOR_CMD_LUT_SEQ_IDX_READ_UUID_ISSI              15
#define NOR_CMD_LUT_SEQ_IDX_READ_UUID_WB                16

/* 查找表的长度 */
#define CUSTOM_LUT_LENGTH           90


/* FLEXSPI的引脚使用同样的PAD配置 */
#define FLEXSPI_PAD_CONFIG_DATA         (SRE_1_FAST_SLEW_RATE| \
                                        DSE_6_R0_6| \
                                        SPEED_3_MAX_200MHz| \
                                        ODE_0_OPEN_DRAIN_DISABLED| \
                                        PKE_1_PULL_KEEPER_ENABLED| \
                                        PUE_0_KEEPER_SELECTED| \
                                        PUS_0_100K_OHM_PULL_DOWN| \
                                        HYS_0_HYSTERESIS_DISABLED)   
    /* 配置说明 : */
    /* 转换速率: 转换速率快
        驱动强度: R0/6 
        带宽配置 : max(200MHz)
        开漏配置: 关闭 
        拉/保持器配置: 使能
        拉/保持器选择: 保持器
        上拉/下拉选择: 100K欧姆下拉(选择了保持器此配置无效)
        滞回器配置: 禁止 */ 

/*******************************************************************************
* Prototypes
******************************************************************************/
static void FlexSPI_NorFlash_IOMUXC_MUX_Config(void);
static void FlexSPI_NorFlash_IOMUXC_PAD_Config(void);
static void NorFlash_FlexSPI_ModeInit(void);
/*******************************************************************************
 * Variables
 ******************************************************************************/

extern flexspi_device_config_t deviceconfig;
extern const uint32_t customLUT[CUSTOM_LUT_LENGTH];

/*******************************************************************************
 * Code
 ******************************************************************************/
/* 设备特性相关的参数 */
flexspi_device_config_t deviceconfig = {
    .flexspiRootClk = 120000000,
    .flashSize = (32*1024),
    .CSIntervalUnit = kFLEXSPI_CsIntervalUnit1SckCycle,
    .CSInterval = 2,
    .CSHoldTime = 1,
    .CSSetupTime = 1,
    .dataValidTime = 2,
    .columnspace = 0,
    .enableWordAddress = false,
    .AWRSeqIndex = NOR_CMD_LUT_SEQ_IDX_AHB_PAGEPROGRAM_QUAD_1,
    .AWRSeqNumber = 2,
    .ARDSeqIndex = NOR_CMD_LUT_SEQ_IDX_READ_FAST_QUAD,
    .ARDSeqNumber = 1,
    /* W25Q256 typical time=0.7ms,max time=3ms 
     *  fAHB = 528MHz,T AHB = 1/528us
     *  unit = 32768/528 = 62.06us
     *  取延时时间为1ms，
     *  AHBWriteWaitInterval = 1*1000/62.06 = 17
     */
    .AHBWriteWaitUnit = kFLEXSPI_AhbWriteWaitUnit32768AhbCycle,
    .AHBWriteWaitInterval = 17,
};

/* 定义查找表LUT
 * 下表以[4 * NOR_CMD_LUT_SEQ_IDX_xxxx]表示1个序列，
 * 1个序列最多包含8条指令，使用宏FLEXSPI_LUT_SEQ可以一次定义2个指令。
 * 一个FLEXSPI_LUT_SEQ占一个LUT寄存器，端口A和端口B各有64个LUT寄存器，
 * 所以CUSTOM_LUT_LENGTH最大值为64。
 *
 * FLEXSPI_LUT_SEQ格式如下（LUT指令0，使用的数据线数目，指令的参数，
                            LUT指令1，使用的数据线数目，指令的参数）
 * 
 * 不满8条指令的序列应以STOP指令结束，即kFLEXSPI_Command_STOP，
 * 不过因为STOP指令中的所有参数均为0，而数组的初始值也都为0，
 * 所以部分序列的末尾忽略了STOP指令也能正常运行。
 */
const uint32_t customLUT[CUSTOM_LUT_LENGTH] = {
        /* 普通读指令，Normal read mode -SDR */
        [4 * NOR_CMD_LUT_SEQ_IDX_READ_NORMAL] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, W25Q_ReadData_4Addr, 
                            kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, FLASH_ADDR_LENGTH),
            
        [4 * NOR_CMD_LUT_SEQ_IDX_READ_NORMAL + 1] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_READ_SDR, kFLEXSPI_1PAD, 0x04, 
                            kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),

        /* 快速读指令，Fast read mode - SDR */
        [4 * NOR_CMD_LUT_SEQ_IDX_READ_FAST] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, W25Q_FastReadData_4Addr, 
                            kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, FLASH_ADDR_LENGTH),
            
        [4 * NOR_CMD_LUT_SEQ_IDX_READ_FAST + 1] = 
          FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DUMMY_SDR, kFLEXSPI_1PAD, 0x08,
                          kFLEXSPI_Command_READ_SDR, kFLEXSPI_1PAD, 0x04),

        /* QUAD模式快速读指令，Fast read quad mode - SDR */
        [4 * NOR_CMD_LUT_SEQ_IDX_READ_FAST_QUAD] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, W25Q_FastReadQuad_4Addr, 
                            kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, FLASH_ADDR_LENGTH),
        [4 * NOR_CMD_LUT_SEQ_IDX_READ_FAST_QUAD + 1] = 
          FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DUMMY_SDR, kFLEXSPI_4PAD, 0x08, 
                          kFLEXSPI_Command_READ_SDR, kFLEXSPI_4PAD, 0x04),

        /* 读取扩展参数，Read extend parameters */
        [4 * NOR_CMD_LUT_SEQ_IDX_READSTATUS] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, W25Q_ReadStatusReg, 
                            kFLEXSPI_Command_READ_SDR, kFLEXSPI_1PAD, 0x04),

        /* 写使能，Write Enable */
        [4 * NOR_CMD_LUT_SEQ_IDX_WRITEENABLE] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, W25Q_WriteEnable, 
                            kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),

        /* 擦除扇区，Erase Sector  */
        [4 * NOR_CMD_LUT_SEQ_IDX_ERASESECTOR] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, W25Q_SectorErase_4Addr, 
                            kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, FLASH_ADDR_LENGTH),

        /* SINGLE模式页写入，Page Program - single mode */
        [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_SINGLE] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, W25Q_PageProgram_4Addr, 
                            kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, FLASH_ADDR_LENGTH),
        [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_SINGLE + 1] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_WRITE_SDR, kFLEXSPI_1PAD, 0x04, 
                            kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),

        /* QUAD模式页写入，Page Program - quad mode */
        [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_QUAD] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, W25Q_PageProgramQuad_4Addr, 
                            kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, FLASH_ADDR_LENGTH),
        [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_QUAD + 1] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_WRITE_SDR, kFLEXSPI_4PAD, 0x04, 
                            kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),  

        /* 读ID，Read ID ，ID7-ID0*/
        [4 * NOR_CMD_LUT_SEQ_IDX_READID] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, W25Q_DeviceID, 
                            kFLEXSPI_Command_DUMMY_SDR, kFLEXSPI_1PAD, FLASH_ADDR_LENGTH),
        [4 * NOR_CMD_LUT_SEQ_IDX_READID + 1] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_READ_SDR, kFLEXSPI_1PAD, 0x04, 
                            kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),
        
        /* 读JedecDeviceID,MF7-MF0+ID15-ID0 */
        [4 * NOR_CMD_LUT_SEQ_IDX_READJEDECID] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, W25Q_JedecDeviceID, 
                            kFLEXSPI_Command_READ_SDR, kFLEXSPI_1PAD, 0x04),

        /* 写状态寄存器，Enable Quad mode */
        [4 * NOR_CMD_LUT_SEQ_IDX_WRITESTATUSREG] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, W25Q_WriteStatusReg, 
                            kFLEXSPI_Command_WRITE_SDR, kFLEXSPI_1PAD, 0x04),

        /* 读状态寄存器，Read status register */
        [4 * NOR_CMD_LUT_SEQ_IDX_READSTATUSREG] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, W25Q_ReadStatusReg, 
                            kFLEXSPI_Command_READ_SDR, kFLEXSPI_1PAD, 0x04),

        /* 擦除整片FLASH，Erase Chip */
        [4 * NOR_CMD_LUT_SEQ_IDX_ERASECHIP] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, W25Q_ChipErase, 
                            kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),
            
        
        /* 给AHB命令访问的 QUAD模式页写入 序列，包含写使能和页写入两条序列 */
        /* 写使能，Write Enable */
        [4 * NOR_CMD_LUT_SEQ_IDX_AHB_PAGEPROGRAM_QUAD_1] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, W25Q_WriteEnable, 
                            kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),
            
        /* QUAD模式页写入，Page Program - quad mode */
        [4 * NOR_CMD_LUT_SEQ_IDX_AHB_PAGEPROGRAM_QUAD_2] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, W25Q_PageProgramQuad_4Addr, 
                            kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, FLASH_ADDR_LENGTH),
        [4 * NOR_CMD_LUT_SEQ_IDX_AHB_PAGEPROGRAM_QUAD_2 + 1] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_WRITE_SDR, kFLEXSPI_4PAD, 0x04, 
                            kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),  	

        // 读唯一ID ISSI芯片，命令0X4B/
        [4 * NOR_CMD_LUT_SEQ_IDX_READ_UUID_ISSI] 	=
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,kFLEXSPI_1PAD,0x4B, 
                              kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, FLASH_ADDR_LENGTH),
                              
         [4 * NOR_CMD_LUT_SEQ_IDX_READ_UUID_ISSI + 1] 	=
             FLEXSPI_LUT_SEQ(kFLEXSPI_Command_READ_SDR,kFLEXSPI_1PAD,0x04,
                              kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),
                              
        // 读唯一ID 华邦芯片，命令0X4B/
        [4 * NOR_CMD_LUT_SEQ_IDX_READ_UUID_WB] 	=
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x4B, 
                              kFLEXSPI_Command_DUMMY_SDR, kFLEXSPI_1PAD, 0x18),
                              
        [4 * NOR_CMD_LUT_SEQ_IDX_READ_UUID_WB + 1] 	=
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_READ_SDR, kFLEXSPI_1PAD, 0x04, 
                              kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),


 

};



/**
* @brief  初始化NORFLASH相关IOMUXC的MUX复用配置
* @param  无
* @retval 无
*/
static void FlexSPI_NorFlash_IOMUXC_MUX_Config(void)
{
  /* FlexSPI通讯引脚 */
  IOMUXC_SetPinMux(NORFLASH_SS_IOMUXC, 1U);                                   
  IOMUXC_SetPinMux(NORFLASH_SCLK_IOMUXC, 1U);  
  IOMUXC_SetPinMux(NORFLASH_DATA00_IOMUXC, 1U);  
  IOMUXC_SetPinMux(NORFLASH_DATA01_IOMUXC, 1U);  
  IOMUXC_SetPinMux(NORFLASH_DATA02_IOMUXC, 1U);  
  IOMUXC_SetPinMux(NORFLASH_DATA03_IOMUXC, 1U);  
}

/**
* @brief  初始化NORFLASH相关IOMUXC的PAD属性配置
* @param  无
* @retval 无
*/
static void FlexSPI_NorFlash_IOMUXC_PAD_Config(void)
{
  /* FlexSPI通讯引脚使用同样的属性配置 */
  IOMUXC_SetPinConfig(NORFLASH_SS_IOMUXC, FLEXSPI_PAD_CONFIG_DATA);   
  IOMUXC_SetPinConfig(NORFLASH_SCLK_IOMUXC, FLEXSPI_PAD_CONFIG_DATA);                               
  IOMUXC_SetPinConfig(NORFLASH_DATA00_IOMUXC, FLEXSPI_PAD_CONFIG_DATA);   
  IOMUXC_SetPinConfig(NORFLASH_DATA01_IOMUXC, FLEXSPI_PAD_CONFIG_DATA);                               
  IOMUXC_SetPinConfig(NORFLASH_DATA02_IOMUXC, FLEXSPI_PAD_CONFIG_DATA);   
  IOMUXC_SetPinConfig(NORFLASH_DATA03_IOMUXC, FLEXSPI_PAD_CONFIG_DATA);                               
}

/**
* @brief  初始化NorFlash使用的FlexSPI外设模式及时钟
* @param  无
* @retval 无
*/  
static void NorFlash_FlexSPI_ModeInit(void)
{
  flexspi_config_t config;

  const clock_usb_pll_config_t g_ccmConfigUsbPll = {.loopDivider = 0U};

  /* 初始化USB1PLL，即PLL3，loopDivider=0，
      所以USB1PLL=PLL3 = 24*20 = 480MHz */
  CLOCK_InitUsb1Pll(&g_ccmConfigUsbPll);
  /* 设置PLL3 PFD0频率为：PLL3*18/24 = 360MHZ. */
  CLOCK_InitUsb1Pfd(kCLOCK_Pfd0, 24);  
  /* 选择PLL3 PFD0作为flexspi时钟源
      00b derive clock from semc_clk_root_pre
      01b derive clock from pll3_sw_clk
      10b derive clock from PLL2 PFD2
      11b derive clock from PLL3 PFD0 */  
  CLOCK_SetMux(kCLOCK_FlexspiMux, 0x3); 
  /* 设置flexspiDiv分频因子，得到FLEXSPI_CLK_ROOT = PLL3 PFD0/(flexspiDiv+1) = 120M. */
  CLOCK_SetDiv(kCLOCK_FlexspiDiv, 2);  
  
  /* 关闭DCache功能 */
  SCB_DisableDCache();

  /*获取 FlexSPI 常用默认设置 */
  FLEXSPI_GetDefaultConfig(&config);

  /* 允许AHB预读取的功能 */
  config.ahbConfig.enableAHBPrefetch = true;
  
  /* 写入配置 */
  FLEXSPI_Init(FLEXSPI, &config);

  /* 根据串行闪存功能配置闪存设置 */
  FLEXSPI_SetFlashConfig(FLEXSPI, &deviceconfig, kFLEXSPI_PortA1);

  /* 更新查找表 */
  FLEXSPI_UpdateLUT(FLEXSPI, 0, customLUT, CUSTOM_LUT_LENGTH);
}

/**
* @brief  FlexSPI初始化
* @param  无
* @retval 无
*/
void FlexSPI_NorFlash_Init(void)
{
	uint32_t JedecDeviceID;
	
  FlexSPI_NorFlash_IOMUXC_MUX_Config();
  FlexSPI_NorFlash_IOMUXC_PAD_Config();
  NorFlash_FlexSPI_ModeInit();
	
	/* 获取JedecDevice ID. */
  FlexSPI_NorFlash_Get_JedecDevice_ID(FLEXSPI, &JedecDeviceID);
	
	/* ISSI厂商的FLASH需要使能Quad模式,厂商ID为高8位 */
	if((JedecDeviceID &0xFF0000) == (FLASH_ISSI_JEDECDEVICE_ID &0xFF0000))
	{
		FlexSPI_NorFlash_Enable_Quad_Mode(FLEXSPI);
	}
}


/**
* @brief  读取FLASH芯片的JedecDevice ID
* @param  base:使用的FlexSPI端口
* @param  vendorID[out]:存储接收到的ID值的缓冲区，大小为1字节，正常时该值为0xEF4019
* @retval FlexSPI传输返回的状态值，正常为0
*/
status_t FlexSPI_NorFlash_Get_JedecDevice_ID(FLEXSPI_Type *base, uint32_t *vendorID)
{
    uint32_t temp;
    flexspi_transfer_t flashXfer;
    
    /* 要读写的FLASH内部存储单元地址，本命令不带地址 */
    flashXfer.deviceAddress = 0;
    /* 要使用的端口 */
    flashXfer.port = kFLEXSPI_PortA1;
    /* 本命令的类型 */
    flashXfer.cmdType = kFLEXSPI_Read;
    /* 要执行的序列个数 */
    flashXfer.SeqNumber = 1;
    /* 要执行的序列号 */
    flashXfer.seqIndex = NOR_CMD_LUT_SEQ_IDX_READJEDECID;
    /* 接收到的数据先缓存到temp */
    flashXfer.data = &temp;
    /* 要接收的数据个数 */
    flashXfer.dataSize = 3;

    /* 开始阻塞传输 */
    status_t status = FLEXSPI_TransferBlocking(base, &flashXfer);

    /* 调整高低字节，结果赋值到vendorId */
    *vendorID = ((temp&0xFF)<<16) | (temp&0xFF00) | ((temp&0xFF0000)>>16);

    return status;
}

/**
* @brief  读取FLASH芯片的Device ID
* @param  base:使用的FlexSPI端口
* @param  vendorID[out]:存储接收到的ID值的缓冲区，大小为1字节，正常时该值为0x18
* @retval FlexSPI传输返回的状态值，正常为0
*/
status_t FlexSPI_NorFlash_Get_Device_ID(FLEXSPI_Type *base, uint8_t *vendorID)
{
    uint32_t temp;
    flexspi_transfer_t flashXfer;
    
    /* 要读写的FLASH内部存储单元地址，本命令不带地址 */
    flashXfer.deviceAddress = 0;
    /* 要使用的端口 */
    flashXfer.port = kFLEXSPI_PortA1;
    /* 本命令的类型 */
    flashXfer.cmdType = kFLEXSPI_Read;
    /* 要执行的序列个数 */
    flashXfer.SeqNumber = 1;
    /* 要执行的序列号 */
    flashXfer.seqIndex = NOR_CMD_LUT_SEQ_IDX_READID;
    /* 接收到的数据先缓存到temp */
    flashXfer.data = &temp;
    /* 要接收的数据个数 */
    flashXfer.dataSize = 1;

    /* 开始阻塞传输 */
    status_t status = FLEXSPI_TransferBlocking(base, &flashXfer);

    /* 把接收到的内容赋值到缓冲区 */
    *vendorID = temp;

    return status;
}

/**
* @brief  读取FLASH芯片的UUID (ISSI芯片)
* @param  buf:读取到的UUID ,IS芯片16个字节，wb芯片8个字节
* @retval 默认返回正常
*/
uint8_t FlexSPI_FlashUUID_Get_ISSI(uint8_t *buf)
{
    volatile uint32_t pid,uid,data;
    flexspi_transfer_t FlashTransfer;

    FlashTransfer.deviceAddress=0;                      //地址
    FlashTransfer.port=kFLEXSPI_PortA1;                 //端口
    FlashTransfer.cmdType=kFLEXSPI_Read;                //操作类型，读数据
    FlashTransfer.SeqNumber=1;                          //序号
    FlashTransfer.seqIndex=NOR_CMD_LUT_SEQ_IDX_READ_UUID_ISSI;  //LUT表中命令索引
    FlashTransfer.data=(uint32_t*)buf;                 //数据缓冲区
    FlashTransfer.dataSize=16;                           //数据长度
    FLEXSPI_TransferBlocking(FLEXSPI,&FlashTransfer);
    return 1;

}

/**
* @brief  读取FLASH芯片的UUID (WB芯片)
* @param  buf:读取到的UUID ,IS芯片16个字节，wb芯片8个字节
* @retval 默认返回正常
*/
uint8_t FlexSPI_FlashUUID_Get(uint8_t *buf)
{
    volatile uint32_t pid,uid,data;
    flexspi_transfer_t FlashTransfer;

    FlashTransfer.deviceAddress=0;                      //地址
    FlashTransfer.port=kFLEXSPI_PortA1;                 //端口
    FlashTransfer.cmdType=kFLEXSPI_Read;                //操作类型，读数据
    FlashTransfer.SeqNumber=1;                          //序号
    FlashTransfer.seqIndex=NOR_CMD_LUT_SEQ_IDX_READ_UUID_WB;  //LUT表中命令索引
    FlashTransfer.data=(uint32_t*)buf;                 //数据缓冲区
    FlashTransfer.dataSize=8;                           //数据长度
    FLEXSPI_TransferBlocking(FLEXSPI,&FlashTransfer);
    return 1;

}
/**
* @brief  写使能
* @param  base:使用的FlexSPI端口
* @retval FlexSPI传输返回的状态值，正常为0
*/
status_t FlexSPI_NorFlash_Write_Enable(FLEXSPI_Type *base)
{
    flexspi_transfer_t flashXfer;
    status_t status;

    /* 写使能 */
    flashXfer.deviceAddress = 0;
    flashXfer.port = kFLEXSPI_PortA1;
    flashXfer.cmdType = kFLEXSPI_Command;
    flashXfer.SeqNumber = 1;
    flashXfer.seqIndex = NOR_CMD_LUT_SEQ_IDX_WRITEENABLE;

    status = FLEXSPI_TransferBlocking(base, &flashXfer);

    return status;
}

/**
* @brief  等待至FLASH空闲状态
* @param  base:使用的FlexSPI端口
* @retval FlexSPI传输返回的状态值，正常为0
*/
status_t FlexSPI_NorFlash_Wait_Bus_Busy(FLEXSPI_Type *base)
{
    /* 等待至空闲状态 */
    bool isBusy;
    uint32_t readValue;
    status_t status;
    flexspi_transfer_t flashXfer;

    /* 读状态寄存器 */
    flashXfer.deviceAddress = 0;
    flashXfer.port = kFLEXSPI_PortA1;
    flashXfer.cmdType = kFLEXSPI_Read;
    flashXfer.SeqNumber = 1;
    flashXfer.seqIndex = NOR_CMD_LUT_SEQ_IDX_READSTATUSREG;
    flashXfer.data = &readValue;
    flashXfer.dataSize = 1;

    do
    {
        status = FLEXSPI_TransferBlocking(base, &flashXfer);

        if (status != kStatus_Success)
        {
            return status;
        }
        /* 若busy位为1表示忙碌 */
        if (FLASH_BUSY_STATUS_POL)
        {
            /* 判断状态寄存器的busy位 */
            if (readValue & (1U << FLASH_BUSY_STATUS_OFFSET))
            {
                isBusy = true;
            }
            else
            {
                isBusy = false;
            }
        }
        else /* 若busy位为0表示忙碌 */
        {
            if (readValue & (1U << FLASH_BUSY_STATUS_OFFSET))
            {
                isBusy = false;
            }
            else
            {
                isBusy = true;
            }
        }

    } while (isBusy);

    return status;
}


/**
* @brief  读状态寄存器
* @param  base:使用的FlexSPI端口
* @retval FlexSPI传输返回的状态值，正常为0
*/
status_t FlexSPI_NorFlash_Read_Status_Register(FLEXSPI_Type *base, uint8_t *SR_value)
{

    uint32_t readValue;
    status_t status;
    flexspi_transfer_t flashXfer;

    /* 读状态寄存器 */
    flashXfer.deviceAddress = 0;
    flashXfer.port = kFLEXSPI_PortA1;
    flashXfer.cmdType = kFLEXSPI_Read;
    flashXfer.SeqNumber = 1;
    flashXfer.seqIndex = NOR_CMD_LUT_SEQ_IDX_READSTATUSREG;
    flashXfer.data = &readValue;
    flashXfer.dataSize = 1;

		status = FLEXSPI_TransferBlocking(base, &flashXfer);
		
		*SR_value = readValue;
   
		return status;
}

/**
* @brief  写状态寄存器
* @param  base:使用的FlexSPI端口
* @param  config:要写入的配置内容
* @retval FlexSPI传输返回的状态值，正常为0
*/
status_t FlexSPI_NorFlash_Write_Status_Register(FLEXSPI_Type *base, uint8_t *config)
{
		flexspi_transfer_t flashXfer;
    status_t status;
		
		 /* 写使能 */
    status = FlexSPI_NorFlash_Write_Enable(base);

    if (status != kStatus_Success)
    {
        return status;
    }

    /* 写入内容 */
    flashXfer.deviceAddress = 0;
    flashXfer.port = kFLEXSPI_PortA1;
    flashXfer.cmdType = kFLEXSPI_Write;
    flashXfer.SeqNumber = 1;
    flashXfer.seqIndex = NOR_CMD_LUT_SEQ_IDX_WRITESTATUSREG;
		flashXfer.data = (uint32_t *)config;
    flashXfer.dataSize = 1;

    status = FLEXSPI_TransferBlocking(base, &flashXfer);
		
		if (status != kStatus_Success)
    {
        return status;
    }
    
    /* 等待FLASH至空闲状态 */
    status = FlexSPI_NorFlash_Wait_Bus_Busy(base);
    
    return status;
}

/**
* @brief  使能Quad模式（ISSI的FLASH上电后必须调用，Winbond不应调用）
* @note   ISSI厂商的FLASH，状态寄存器的bit6-QE用于配置该功能，该位为1时表示使能Quad模式
*				 Winbond厂商的FLASH，状态寄存器的bit6-TB是配置写保护功能的
*         所以在使用Winbond厂商的FLASH时不应调用本函数，
*         而使用ISSI厂商的FLASH时必须调用本函数   		
* @param  base:使用的FlexSPI端口
* @param  config:要写入的配置内容
* @retval FlexSPI传输返回的状态值，正常为0
*/
status_t FlexSPI_NorFlash_Enable_Quad_Mode(FLEXSPI_Type *base)
{
	uint8_t SR_value;
	status_t status;
	
	/* 读取原寄存器的内容 */
	status = FlexSPI_NorFlash_Read_Status_Register(base, &SR_value);
	
	if (status != kStatus_Success)
	{
		return status;
	}
	
	/* 对bit6-QE位置1（ISSI厂商的FLASH） */
	SR_value |= 0x40;

	/* 写入该值 */
	status = FlexSPI_NorFlash_Write_Status_Register(base, &SR_value);
	
	return status;
}


/**
* @brief  擦除扇区
* @param  base:使用的FlexSPI端口
* @param  dstAddr:要擦除扇区的起始地址
* @retval FlexSPI传输返回的状态值，正常为0
*/
status_t FlexSPI_NorFlash_Erase_Sector(FLEXSPI_Type *base, uint32_t dstAddr)
{
    status_t status;
    flexspi_transfer_t flashXfer;

    /* 写使能 */
    status = FlexSPI_NorFlash_Write_Enable(base);

    if (status != kStatus_Success)
    {
        return status;
    }

    /* 擦除扇区指令 */
    flashXfer.deviceAddress = dstAddr;
    flashXfer.port = kFLEXSPI_PortA1;
    flashXfer.cmdType = kFLEXSPI_Command;
    flashXfer.SeqNumber = 1;
    flashXfer.seqIndex = NOR_CMD_LUT_SEQ_IDX_ERASESECTOR;
    
    status = FLEXSPI_TransferBlocking(base, &flashXfer);

    if (status != kStatus_Success)
    {
        return status;
    }
    
    /* 等待FLASH至空闲状态 */
    status = FlexSPI_NorFlash_Wait_Bus_Busy(base);
    
    return status;
}

/**
* @brief  页写入
* @param  base:使用的FlexSPI端口
* @param  dstAddr:要写入的起始地址
* @param  src:要写入的数据的指针
* @param  dataSize:要写入的数据量，不能大于256
* @retval FlexSPI传输返回的状态值，正常为0
*/
status_t FlexSPI_NorFlash_Page_Program(FLEXSPI_Type *base, 
                                       uint32_t dstAddr, 
                                       uint8_t *src,
                                       uint16_t dataSize)
{
    status_t status;
    flexspi_transfer_t flashXfer;

    /* 写使能 */
    status = FlexSPI_NorFlash_Write_Enable(base);

    if (status != kStatus_Success)
    {
        return status;
    }

    /* 设置传输结构体 */
    flashXfer.deviceAddress = dstAddr;
    flashXfer.port = kFLEXSPI_PortA1;
    flashXfer.cmdType = kFLEXSPI_Write;
    flashXfer.SeqNumber = 1;
    flashXfer.seqIndex = NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_QUAD;
    flashXfer.data = (uint32_t *)src;
    flashXfer.dataSize = dataSize;
    
    status = FLEXSPI_TransferBlocking(base, &flashXfer);

    if (status != kStatus_Success)
    {
        return status;
    }

    /* 等待写入完成 */
    status = FlexSPI_NorFlash_Wait_Bus_Busy(base);

    return status;
}


/**
  * @brief 向FLASH写入不限量的数据
  * @note  写入前要确保该空间是被擦除的状态
  * @param  base:使用的FlexSPI端口
  * @param  dstAddr:要写入的起始地址
  * @param  src:要写入的数据的指针
  * @param  dataSize:要写入的数据量，没有限制，确认空间是已被擦除过的即可
  * @retval 写入的返回值，为0是表示正常
  */
status_t FlexSPI_NorFlash_Buffer_Program(FLEXSPI_Type *base, 
                                         uint32_t dstAddr, 
                                         uint8_t *src,
                                         uint16_t dataSize)                              
{
  status_t status = kStatus_Success;
  uint16_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0;
  /* 后续要处理的字节数，初始值为NumByteToWrite*/
  uint16_t NumByteToWriteRest = dataSize;
  /* 根据以下情况进行处理：
    1.写入的首地址是否对齐 
    2.最后一次写入是否刚好写满一页 */
  Addr = dstAddr % FLASH_PAGE_SIZE;
  count = FLASH_PAGE_SIZE - Addr;
  
  /* 若NumByteToWrite > count：
     第一页写入count个字节，对其余字节再进行后续处理，
     所以用 (NumByteToWriteRest = dataSize - count) 求出后续的NumOfPage和NumOfSingle进行处理。
     若NumByteToWrite < count：
     即不足一页数据，直接用NumByteToWriteRest = NumByteToWrite求出NumOfPage和NumOfSingle即可 */
  NumByteToWriteRest = (dataSize > count) ? (dataSize - count) : dataSize;
  
  /* 要完整写入的页数（不包括前count字节）*/
  NumOfPage =  NumByteToWriteRest / FLASH_PAGE_SIZE;
  /* 最后一页要写入的字节数（不包括前count字节）*/
  NumOfSingle = NumByteToWriteRest % FLASH_PAGE_SIZE;
 
  /* dataSize > count时，需要先往第一页写入count个字节
     dataSize < count时无需进行此操作 */
  if(count != 0 && dataSize > count)
  {  
    status = FlexSPI_NorFlash_Page_Program(base, dstAddr, src, count);    
    if(status != kStatus_Success) return status;
    
    dstAddr += count;
    src += count;
  }   
  
  /* 处理后续数据 */
  if(NumOfPage== 0 ) 
  {
    status = FlexSPI_NorFlash_Page_Program(base, dstAddr, src, NumOfSingle);
    if(status != kStatus_Success) return status;
  }
  else
  {   
    /* 后续数据大于一页 */
    while(NumOfPage--)
    {
      status = FlexSPI_NorFlash_Page_Program(base, dstAddr, src, FLASH_PAGE_SIZE);
      if(status != kStatus_Success) return status;
      
      dstAddr +=  FLASH_PAGE_SIZE;
      src += FLASH_PAGE_SIZE;  
    }
    /* 最后一页 */
    if(NumOfSingle != 0)
    {
      status = FlexSPI_NorFlash_Page_Program(base, dstAddr, src, NumOfSingle); 
      if(status != kStatus_Success) return status;

    }
  }

  return status;
}

/**
* @brief  读取数据
* @param  base:使用的FlexSPI端口
* @param  address:要读取的起始地址
* @param  dst[out]:存储接收到的数据的指针
* @param  dataSize:要读取的数据量，不能大于65535
* @retval FlexSPI传输返回的状态值，正常为0
*/
status_t FlexSPI_NorFlash_Buffer_Read(FLEXSPI_Type *base, 
                                      uint32_t address, 
                                      uint8_t *dst,
                                      uint16_t dataSize)
{
    status_t status;
    flexspi_transfer_t flashXfer;

    /* 设置传输结构体 */
    flashXfer.deviceAddress = address;
    flashXfer.port = kFLEXSPI_PortA1;
    flashXfer.cmdType = kFLEXSPI_Read;
    flashXfer.SeqNumber = 1;
    flashXfer.seqIndex = NOR_CMD_LUT_SEQ_IDX_READ_FAST_QUAD;
    flashXfer.data = (uint32_t *)dst;
    flashXfer.dataSize = dataSize;
    
    status = FLEXSPI_TransferBlocking(base, &flashXfer);

    return status;
}

/****************************END OF FILE**********************/
