
#include	"Include.h"
#include	"BSP.h"


/*=========================================================================================*/
extern void FSMC_Init(void);
extern void FSMC_InitSRAM(void);
extern void FSMC_InitLCD(void);

static int a=0x1234;
static int b=0x4567;

void Board_HardInit(void)
{
	volatile u32 clk;
	RCC_ClocksTypeDef RCC_ClocksStatus;
	char buf[64];

	SystemCoreClockUpdate();
	clk=SystemCoreClock;

	RCC_GetClocksFreq(&RCC_ClocksStatus);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	//中断分组配置

	FSMC_Init();
	FSMC_InitSRAM();
	FSMC_InitLCD();

//	SysDrv_RTC_Init();

//	DebugUart_Init();
//	DebugPuts("\r\n");


//	x_sprintf(buf,"SystemClock:%dHz\r\n",SystemCoreClock);
//	DebugPuts(buf);

//	x_sprintf(buf,"&a:%08XH; &b:%08XH.\r\n",&a,&b);
//	DebugPuts(buf);

//	x_sprintf(buf," a:%08XH;  b:%08XH.\r\n",a,b);
//	DebugPuts(buf);

}

/*=========================================================================================*/
void	vfs_fatfs_init(void);
void	vfs_fatfs_register(u8 drv,const char *fs_name,const char *blk_dev_name);
void	vfs_fatfs_check(void);

static  void	__FileSystemInit(void)
{

#if 0
	////BlockDevice
	//RAMDisk_Register("RAMDisk");
	//NandDisk_Register("NandFlash");
	SDMMC0_Register("SDMMC0");
	//SDMMC1_Register("SDMMC1");


	////FileSystem
	vfs_fatfs_init();

	//vfs_fatfs_register(0,"A:","RAMDisk");

	vfs_fatfs_register(1,"B:","SDMMC0");
	//vfs_fatfs_register(1,"B:","SDMMC1");
	//vfs_fatfs_register(2,"C:","NandFlash");
//	vfs_fatfs_check();
	////////
#endif

}

static  void	__DriversInit(void)
{
//	ADC_DrvInit();
	//RTC_DrvInit();
//	I2C_GPD7_GPD3.Init();
//	I2C_GPB8_GPB9.Init();

	RES_DevInit(); //初始化资源储存设备

//	WM8978_Init(&I2C_GPB8_GPB9);


//	OEM_Net_Init();

//	COM1_Register("COM1");
//	COM2_Register("COM2");
//	COM3_Register("COM3");

//	ALCO_Register();
//	VS1053_Register();
//	SPI_Flash_Register();
//	spi_test();
//    Audio_DrvInit();

}

/*=========================================================================================*/

void Board_ModuleInit(void)
{
	////系统模块初始化
//	Board_MemInit();
//	KernelDebugInit();
//	VFS_ModuleInit();			//虚拟文件系统
//	VFS_DEVFS_ModuleInit();		//设备文件系统
//	BLKDEV_MouduleInit();		//块设备

	////用户设备初始化
	__FileSystemInit();
	__DriversInit();

}

/*=========================================================================================*/


