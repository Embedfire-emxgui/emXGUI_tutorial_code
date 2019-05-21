#ifndef __BSP_SD_H
#define __BSP_SD_H


#include "pad_config.h"
#include "fsl_iomuxc.h"
#include "fsl_common.h"
#include "fsl_sd.h"



/*SD1_CMD*/
#define USDHC1_CMD_GPIO             GPIO3
#define USDHC1_CMD_GPIO_PIN         (12U)
#define USDHC1_CMD_IOMUXC           IOMUXC_GPIO_SD_B0_00_USDHC1_CMD

/*SD1_CLK*/
#define USDHC1_CLK_GPIO             GPIO2
#define USDHC1_CLK_GPIO_PIN         (30U)
#define USDHC1_CLK_IOMUXC           IOMUXC_GPIO_SD_B0_01_USDHC1_CLK

/*SD1_D0*/
#define USDHC1_DATA0_GPIO             GPIO3
#define USDHC1_DATA0_GPIO_PIN         (14U)
#define USDHC1_DATA0_IOMUXC           IOMUXC_GPIO_SD_B0_02_USDHC1_DATA0

/*SD1_D1*/
#define USDHC1_DATA1_GPIO             GPIO3
#define USDHC1_DATA1_GPIO_PIN         (15U)
#define USDHC1_DATA1_IOMUXC           IOMUXC_GPIO_SD_B0_03_USDHC1_DATA1

/*SD1_D2*/
#define USDHC1_DATA2_GPIO             GPIO3
#define USDHC1_DATA2_GPIO_PIN         (16U)
#define USDHC1_DATA2_IOMUXC           IOMUXC_GPIO_SD_B0_04_USDHC1_DATA2

/*SD1_D3*/
#define USDHC1_DATA3_GPIO             GPIO3
#define USDHC1_DATA3_GPIO_PIN         (17U)
#define USDHC1_DATA3_IOMUXC           IOMUXC_GPIO_SD_B0_05_USDHC1_DATA3

/*电源控制*/
#define SD_POWER_GPIO             GPIO2
#define SD_POWER_GPIO_PIN         (30U)
#define SD_POWER_IOMUXC           IOMUXC_GPIO_B1_14_USDHC1_VSELECT

/* USDHC1 DATA引脚 CMD引脚 PAD属性配置 IO28,*/
#define USDHC1_DATA_PAD_CONFIG_DATA     (SRE_1_FAST_SLEW_RATE| \
                                        DSE_1_R0_1| \
                                        SPEED_2_MEDIUM_100MHz| \
                                        ODE_0_OPEN_DRAIN_DISABLED| \
                                        PKE_1_PULL_KEEPER_ENABLED| \
                                        PUE_1_PULL_SELECTED| \
                                        PUS_1_47K_OHM_PULL_UP| \
                                        HYS_1_HYSTERESIS_ENABLED)

    /* 配置说明 : */
    /* 转换速率: 转换速率快
        驱动强度: R0 
        带宽配置 : medium(100MHz)
        开漏配置: 关闭 
        拉/保持器配置: 使能
        拉/保持器选择: 上下拉
        上拉/下拉选择: 4.7K欧姆上拉(选择了保持器此配置无效)
        滞回器配置: 禁止 */ 

/* USDHC1 CLK引脚PAD属性配置 */
#define USDHC1_CLK_PAD_CONFIG_DATA       (SRE_1_FAST_SLEW_RATE| \
                                        DSE_1_R0_1| \
                                        SPEED_2_MEDIUM_100MHz| \
                                        ODE_0_OPEN_DRAIN_DISABLED| \
                                        PKE_1_PULL_KEEPER_ENABLED| \
                                        PUE_0_KEEPER_SELECTED| \
                                        PUS_1_47K_OHM_PULL_UP| \
                                        HYS_1_HYSTERESIS_ENABLED)
    /* 配置说明 : */
    /* 转换速率: 转换速率快
        驱动强度: R0 
        带宽配置 : medium(100MHz)
        开漏配置: 关闭 
        拉/保持器配置: 使能
        拉/保持器选择: 保持器
        上拉/下拉选择: 4.7K欧姆上拉(选择了保持器此配置无效)
        滞回器配置: 禁止 */

/* SD卡供电电源控制引脚PAD属性配置 */
#define SD_POWER_PAD_CONFIG_DATA            (SRE_0_SLOW_SLEW_RATE| \
                                        DSE_1_R0_1| \
                                        SPEED_2_MEDIUM_100MHz| \
                                        ODE_0_OPEN_DRAIN_DISABLED| \
                                        PKE_0_PULL_KEEPER_DISABLED| \
                                        PUE_0_KEEPER_SELECTED| \
                                        PUS_0_100K_OHM_PULL_DOWN| \
                                        HYS_0_HYSTERESIS_DISABLED)   
    /* 配置说明 : */
    /* 转换速率: 转换速率慢
      驱动强度: R0 
      带宽配置 : medium(100MHz)
      开漏配置: 关闭 
      拉/保持器配置: 关闭
      拉/保持器选择: 保持器（上面已关闭，配置无效）
      上拉/下拉选择: 100K欧姆下拉（上面已关闭，配置无效）
      滞回器配置: 关闭 */     



/*定义SD进行多个数据块读写测试时，读写数据块的数量 */
#define DATA_BLOCK_COUNT (5U)
/*定义SD卡读写测试的起始块编号 */
#define DATA_BLOCK_START (2U)
/*数据缓冲区大小（单位：字节）*/
#define DATA_BUFFER_SIZE (FSL_SDMMC_DEFAULT_BLOCK_SIZE * DATA_BLOCK_COUNT)


///*电压选择,如果不使用UHS-I，不用设置电压选择，保持默认即可*/
//#define SelectVoltage_3V  0
//#define SelectVoltage_for_UHS_I_1V8 1



  

static status_t AccessCard(sd_card_t *card);
static void CardInformationLog(sd_card_t *card);


void USDHC1_gpio_init(void);
static void BOARD_USDHCClockConfiguration(void);
int USDHC_Host_Init(sd_card_t* sd_struct);
int SD_Card_Init(sd_card_t* sd_struct);
void SD_Card_Test(sd_card_t* sd_struct);

#endif /* __BSP_SD_H */          


