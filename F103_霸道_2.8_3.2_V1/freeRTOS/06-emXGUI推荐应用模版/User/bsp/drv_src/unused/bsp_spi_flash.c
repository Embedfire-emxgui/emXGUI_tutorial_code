
#include <string.h>
#include "Include.h"


/*
	STM32F4XX 时钟计算.
		HCLK = 168M
		PCLK1 = HCLK / 4 = 42M
		PCLK2 = HCLK / 2 = 84M

		SPI2、SPI3 在 PCLK1, 时钟42M
		SPI1       在 PCLK2, 时钟84M

		STM32F4 支持的最大SPI时钟为 37.5 Mbits/S, 因此需要分频。
		STM32硬件SPI接口 = SPI3 或者 SPI1
		由于SPI1的时钟源是84M, SPI3的时钟源是42M。为了获得更快的速度，软件上选择SPI1。

*/

//#define SPI_FLASH			SPI3
#define SPI_FLASH			SPI1

//#define ENABLE_SPI_RCC() 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE)
#define ENABLE_SPI_RCC() 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE)

/*
	【SPI时钟最快是2分频，不支持不分频】
	如果是SPI1，2分频时SCK时钟 = 42M，4分频时SCK时钟 = 21M
	如果是SPI3, 2分频时SCK时钟 = 21M
*/
#define SPI_BAUD			SPI_BaudRatePrescaler_2

/* 片选GPIO端口  */
#define SF_CS_GPIO			GPIOG
#define SF_CS_PIN			GPIO_Pin_6

#define SF_CS_L()      SF_CS_GPIO->BSRRH = SF_CS_PIN
#define SF_CS_H()      SF_CS_GPIO->BSRRL = SF_CS_PIN

/*=========================================================================================*/


//#define CMD_AAI       0xAD  	/* AAI 连续编程指令(FOR SST25VF016B) */
#define CMD_DISWR	  0x04		/* 禁止写, 退出AAI状态 */
#define CMD_EWRSR	  0x50		/* 允许写状态寄存器的命令 */
#define CMD_WRSR      0x01  	/* 写状态寄存器命令 */
#define CMD_WREN      0x06		/* 写使能命令 */
#define CMD_READ      0x03  	/* 读数据区命令 */
#define CMD_RDSR      0x05		/* 读状态寄存器命令 */
#define CMD_RDID      0x9F		/* 读器件ID命令 */
#define CMD_SE        0x20		/* 擦除扇区命令 */
#define CMD_BE        0xC7		/* 批量擦除命令 */
#define DUMMY_BYTE    0xA5		/* 哑命令，可以为任意值，用于读操作 */

#define WIP_FLAG      0x01		/* 状态寄存器中的正在编程标志（WIP) */

/*=========================================================================================*/



static const SFLASH_T *pSF=NULL;

static const SFLASH_T flash_tbl[]={

	{ "MX25L1606E",		0xC22015,	4*KB,   2*MB },
	{ "W25Q16",			0xEF4015,	4*KB,   2*MB },
	{ "W25Q32",			0xEF4016,	4*KB,   4*MB },
	{ "W25Q64",			0xEF4017,	4*KB,   8*MB },
	{ "W25Q128",		0xEF4018,	4*KB,  16*MB },

	{ "Unknow",			0xFFFFFF,	4*KB,  1*MB },

};

#define	FLASH_TBL_COUNT	(sizeof(flash_tbl)/sizeof(flash_tbl[0]))
static mutex_obj *mutex_lock=NULL;

/*=========================================================================================*/


static u8 sf_SendByte(u8 _ucValue);
static void sf_WriteEnable(void);
static void sf_WriteStatus(u8 _ucValue);
static void sf_WaitForWriteEnd(void);
static u8 sf_NeedErase(u8 * _ucpOldBuf, u8 *_ucpNewBuf, u16 _uiLen);
static u8 sf_CmpData(u32 _uiSrcAddr, u8 *_ucpTar, u32 _uiSize);
static u8 sf_AutoWritePage(u8 *_ucpSrc, u32 _uiWrAddr, u16 _usWrLen);

static void bsp_CfgSPIForSFlash(void);

static u8 s_spiBuf[4096];	/* 用于写函数，先读出整个page，修改缓冲区后，再整个page回写 */



/*
*********************************************************************************************************
*	函 数 名: bsp_InitSpiFlash
*	功能说明: 初始化串行Flash硬件接口（配置STM32的SPI时钟、GPIO)
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_InitSFlash(void)
{
	int i,id;

	mutex_lock =SYS_mutex_create(NULL);

	/*
	 * STM32硬件SPI接口 = SPI1
		串行Flash型号为 W25Q128 (80MHz)
		SPI_SCK  - PB3
		SPI_MISO - PB4
		SPI_MOSI - PB5
		SF_CS    - PG6


	*/
	if(1)
	{
		GPIO_InitTypeDef GPIO_InitStructure;

		/* 使能GPIO 时钟 */
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOG, ENABLE);

		/* 配置 SCK, MISO 、 MOSI 为复用功能 */
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI1);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_SPI1);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI1);

		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
		GPIO_Init(GPIOB, &GPIO_InitStructure);

		/* 配置片选口线为推挽输出模式 */
		SF_CS_H();		/* 片选置高，不选中 */
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Pin = SF_CS_PIN;
		GPIO_Init(SF_CS_GPIO, &GPIO_InitStructure);
	}


	/* 配置SPI硬件参数用于访问串行Flash */
	bsp_CfgSPIForSFlash();

	id=sf_ReadID();
	for(i=0;i<FLASH_TBL_COUNT;i++)
	{
		if(id ==flash_tbl[i].ChipID)
		{
			break;
		}
	}
	pSF =&flash_tbl[i];

#if 1
	//sf_ReadInfo();			/* 自动识别芯片型号 */

	SF_CS_L();					/* 软件方式，使能串行Flash片选 */
	sf_SendByte(CMD_DISWR);		/* 发送禁止写入的命令,即使能软件写保护 */
	SF_CS_H();					/* 软件方式，禁能串行Flash片选 */

	sf_WaitForWriteEnd();		/* 等待串行Flash内部操作完成 */
	sf_WriteStatus(0);			/* 解除所有BLOCK的写保护 */
#endif
}

/*
*********************************************************************************************************
*	函 数 名: bsp_CfgSPIForSFlash
*	功能说明: 配置STM32内部SPI硬件的工作模式、速度等参数，用于访问SPI接口的串行Flash。
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
static void bsp_CfgSPIForSFlash(void)
{
	SPI_InitTypeDef  SPI_InitStructure;

	/* 打开SPI时钟 */
	ENABLE_SPI_RCC();

	/* 配置SPI硬件参数 */
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	/* 数据方向：2线全双工 */
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		/* STM32的SPI工作模式 ：主机模式 */
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;	/* 数据位长度 ： 8位 */
	/* SPI_CPOL和SPI_CPHA结合使用决定时钟和数据采样点的相位关系、
	   本例配置: 总线空闲是高电平,第2个边沿（上升沿采样数据)
	*/
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;			/* 时钟上升沿采样数据 */
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;		/* 时钟的第2个边沿采样数据 */
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;			/* 片选控制方式：软件控制 */

	/* 设置波特率预分频系数 */
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BAUD;

	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	/* 数据位传输次序：高位先传 */
	SPI_InitStructure.SPI_CRCPolynomial = 7;			/* CRC多项式寄存器，复位后为7。本例程不用 */
	SPI_Init(SPI_FLASH, &SPI_InitStructure);

	SPI_Cmd(SPI_FLASH, DISABLE);			/* 先禁止SPI  */
	SPI_Cmd(SPI_FLASH, ENABLE);				/* 使能SPI  */
}

/*
*********************************************************************************************************
*	函 数 名: sf_EraseSector
*	功能说明: 擦除指定的扇区
*	形    参:  _uiSectorAddr : 扇区地址
*	返 回 值: 无
*********************************************************************************************************
*/
void sf_EraseSector(u32 _uiSectorAddr)
{
	sf_WriteEnable();								/* 发送写使能命令 */

	/* 擦除扇区操作 */
	SF_CS_L();									/* 使能片选 */
	sf_SendByte(CMD_SE);								/* 发送擦除命令 */
	sf_SendByte((_uiSectorAddr & 0xFF0000) >> 16);	/* 发送扇区地址的高8bit */
	sf_SendByte((_uiSectorAddr & 0xFF00) >> 8);		/* 发送扇区地址中间8bit */
	sf_SendByte(_uiSectorAddr & 0xFF);				/* 发送扇区地址低8bit */
	SF_CS_H();									/* 禁能片选 */

	sf_WaitForWriteEnd();							/* 等待串行Flash内部写操作完成 */
}

/*
*********************************************************************************************************
*	函 数 名: sf_EraseChip
*	功能说明: 擦除整个芯片
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
void sf_EraseChip(void)
{
	sf_WriteEnable();								/* 发送写使能命令 */

	/* 擦除扇区操作 */
	SF_CS_L();									/* 使能片选 */
	sf_SendByte(CMD_BE);							/* 发送整片擦除命令 */
	SF_CS_H();									/* 禁能片选 */

	sf_WaitForWriteEnd();							/* 等待串行Flash内部写操作完成 */
}

/*
*********************************************************************************************************
*	函 数 名: sf_PageWrite
*	功能说明: 向一个page内写入若干字节。字节个数不能超出页面大小（4K)
*	形    参:  	_pBuf : 数据源缓冲区；
*				_uiWriteAddr ：目标区域首地址
*				_usSize ：数据个数，不能超过页面大小
*	返 回 值: 无
*********************************************************************************************************
*/
void sf_PageWrite(u8 * _pBuf, u32 _uiWriteAddr, u16 _usSize)
{
	u32 i, j;


	for (j = 0; j < _usSize / 256; j++)
	{
		sf_WriteEnable();								/* 发送写使能命令 */

		SF_CS_L();									/* 使能片选 */
		sf_SendByte(0x02);								/* 发送AAI命令(地址自动增加编程) */
		sf_SendByte((_uiWriteAddr & 0xFF0000) >> 16);	/* 发送扇区地址的高8bit */
		sf_SendByte((_uiWriteAddr & 0xFF00) >> 8);		/* 发送扇区地址中间8bit */
		sf_SendByte(_uiWriteAddr & 0xFF);				/* 发送扇区地址低8bit */

		for (i = 0; i < 256; i++)
		{
			sf_SendByte(*_pBuf++);					/* 发送数据 */
		}

		SF_CS_H();								/* 禁止片选 */

		sf_WaitForWriteEnd();						/* 等待串行Flash内部写操作完成 */

		_uiWriteAddr += 256;
	}

	/* 进入写保护状态 */
	SF_CS_L();
	sf_SendByte(CMD_DISWR);
	SF_CS_H();

	sf_WaitForWriteEnd();							/* 等待串行Flash内部写操作完成 */

}

/*
*********************************************************************************************************
*	函 数 名: sf_ReadBuffer
*	功能说明: 连续读取若干字节。字节个数不能超出芯片容量。
*	形    参:  	_pBuf : 数据源缓冲区；
*				_uiReadAddr ：首地址
*				_usSize ：数据个数, 可以大于PAGE_SIZE,但是不能超出芯片总容量
*	返 回 值: 无
*********************************************************************************************************
*/
void sf_ReadBuffer(u8 * _pBuf, u32 _uiReadAddr, u32 _uiSize)
{
	/* 如果读取的数据长度为0或者超出串行Flash地址空间，则直接返回 */
	if ((_uiSize == 0) ||(_uiReadAddr + _uiSize) > pSF->TotalSize)
	{
		return;
	}

	/* 擦除扇区操作 */
	SF_CS_L();									/* 使能片选 */
	sf_SendByte(CMD_READ);							/* 发送读命令 */
	sf_SendByte((_uiReadAddr & 0xFF0000) >> 16);	/* 发送扇区地址的高8bit */
	sf_SendByte((_uiReadAddr & 0xFF00) >> 8);		/* 发送扇区地址中间8bit */
	sf_SendByte(_uiReadAddr & 0xFF);				/* 发送扇区地址低8bit */
	while (_uiSize--)
	{
		*_pBuf++ = sf_SendByte(DUMMY_BYTE);			/* 读一个字节并存储到pBuf，读完后指针自加1 */
	}
	SF_CS_H();									/* 禁能片选 */
}

/*
*********************************************************************************************************
*	函 数 名: sf_CmpData
*	功能说明: 比较Flash的数据.
*	形    参:  	_ucpTar : 数据缓冲区
*				_uiSrcAddr ：Flash地址
*				_uiSize ：数据个数, 可以大于PAGE_SIZE,但是不能超出芯片总容量
*	返 回 值: 0 = 相等, 1 = 不等
*********************************************************************************************************
*/
static u8 sf_CmpData(u32 _uiSrcAddr, u8 *_ucpTar, u32 _uiSize)
{
	u8 ucValue;

	/* 如果读取的数据长度为0或者超出串行Flash地址空间，则直接返回 */
	if ((_uiSrcAddr + _uiSize) > pSF->TotalSize)
	{
		return 1;
	}

	if (_uiSize == 0)
	{
		return 0;
	}

	SF_CS_L();									/* 使能片选 */
	sf_SendByte(CMD_READ);							/* 发送读命令 */
	sf_SendByte((_uiSrcAddr & 0xFF0000) >> 16);		/* 发送扇区地址的高8bit */
	sf_SendByte((_uiSrcAddr & 0xFF00) >> 8);		/* 发送扇区地址中间8bit */
	sf_SendByte(_uiSrcAddr & 0xFF);					/* 发送扇区地址低8bit */
	while (_uiSize--)
	{
		/* 读一个字节 */
		ucValue = sf_SendByte(DUMMY_BYTE);
		if (*_ucpTar++ != ucValue)
		{
			SF_CS_H();
			return 1;
		}
	}
	SF_CS_H();
	return 0;
}

/*
*********************************************************************************************************
*	函 数 名: sf_NeedErase
*	功能说明: 判断写PAGE前是否需要先擦除。
*	形    参:   _ucpOldBuf ： 旧数据
*			   _ucpNewBuf ： 新数据
*			   _uiLen ：数据个数，不能超过页面大小
*	返 回 值: 0 : 不需要擦除， 1 ：需要擦除
*********************************************************************************************************
*/
static u8 sf_NeedErase(u8 * _ucpOldBuf, u8 *_ucpNewBuf, u16 _usLen)
{
	u16 i;
	u8 ucOld;

	/*
	算法第1步：old 求反, new 不变
	      old    new
		  1101   0101
	~     1111
		= 0010   0101

	算法第2步: old 求反的结果与 new 位与
		  0010   old
	&	  0101   new
		 =0000

	算法第3步: 结果为0,则表示无需擦除. 否则表示需要擦除
	*/

	for (i = 0; i < _usLen; i++)
	{
		ucOld = *_ucpOldBuf++;
		ucOld = ~ucOld;

		/* 注意错误的写法: if (ucOld & (*_ucpNewBuf++) != 0) */
		if ((ucOld & (*_ucpNewBuf++)) != 0)
		{
			return 1;
		}
	}
	return 0;
}

/*
*********************************************************************************************************
*	函 数 名: sf_AutoWritePage
*	功能说明: 写1个PAGE并校验,如果不正确则再重写两次。本函数自动完成擦除操作。
*	形    参:  	_pBuf : 数据源缓冲区；
*				_uiWriteAddr ：目标区域首地址
*				_usSize ：数据个数，不能超过页面大小
*	返 回 值: 0 : 错误， 1 ： 成功
*********************************************************************************************************
*/
static u8 sf_AutoWritePage(u8 *_ucpSrc, u32 _uiWrAddr, u16 _usWrLen)
{
	u16 i;
	volatile	u16 j;					/* 用于延时 */
	u32 uiFirstAddr;		/* 扇区首址 */
	u8 ucNeedErase;		/* 1表示需要擦除 */
	u8 cRet;

	/* 长度为0时不继续操作,直接认为成功 */
	if (_usWrLen == 0)
	{
		return 1;
	}

	/* 如果偏移地址超过芯片容量则退出 */
	if (_uiWrAddr >= pSF->TotalSize)
	{
		return 0;
	}

	/* 如果数据长度大于扇区容量，则退出 */
	if (_usWrLen > pSF->PageSize)
	{
		return 0;
	}

	/* 如果FLASH中的数据没有变化,则不写FLASH */
	sf_ReadBuffer(s_spiBuf, _uiWrAddr, _usWrLen);
	if (memcmp(s_spiBuf, _ucpSrc, _usWrLen) == 0)
	{
		return 1;
	}

	/* 判断是否需要先擦除扇区 */
	/* 如果旧数据修改为新数据，所有位均是 1->0 或者 0->0, 则无需擦除,提高Flash寿命 */
	ucNeedErase = 0;
	if (sf_NeedErase(s_spiBuf, _ucpSrc, _usWrLen))
	{
		ucNeedErase = 1;
	}

	uiFirstAddr = _uiWrAddr & (~(pSF->PageSize - 1));

	if (_usWrLen == pSF->PageSize)		/* 整个扇区都改写 */
	{
		for	(i = 0; i < pSF->PageSize; i++)
		{
			s_spiBuf[i] = _ucpSrc[i];
		}
	}
	else						/* 改写部分数据 */
	{
		/* 先将整个扇区的数据读出 */
		sf_ReadBuffer(s_spiBuf, uiFirstAddr, pSF->PageSize);

		/* 再用新数据覆盖 */
		i = _uiWrAddr & (pSF->PageSize - 1);
		memcpy(&s_spiBuf[i], _ucpSrc, _usWrLen);
	}

	/* 写完之后进行校验，如果不正确则重写，最多3次 */
	cRet = 0;
	for (i = 0; i < 3; i++)
	{

		/* 如果旧数据修改为新数据，所有位均是 1->0 或者 0->0, 则无需擦除,提高Flash寿命 */
		if (ucNeedErase == 1)
		{
			sf_EraseSector(uiFirstAddr);		/* 擦除1个扇区 */
		}

		/* 编程一个PAGE */
		sf_PageWrite(s_spiBuf, uiFirstAddr, pSF->PageSize);

		if (sf_CmpData(_uiWrAddr, _ucpSrc, _usWrLen) == 0)
		{
			cRet = 1;
			break;
		}
		else
		{
			if (sf_CmpData(_uiWrAddr, _ucpSrc, _usWrLen) == 0)
			{
				cRet = 1;
				break;
			}

			/* 失败后延迟一段时间再重试 */
			for (j = 0; j < 10000; j++);
		}
	}

	return cRet;
}

/*
*********************************************************************************************************
*	函 数 名: sf_WriteBuffer
*	功能说明: 写1个扇区并校验,如果不正确则再重写两次。本函数自动完成擦除操作。
*	形    参:  	_pBuf : 数据源缓冲区；
*				_uiWrAddr ：目标区域首地址
*				_usSize ：数据个数，不能超过页面大小
*	返 回 值: 1 : 成功， 0 ： 失败
*********************************************************************************************************
*/
u8 sf_WriteBuffer(u8* _pBuf, u32 _uiWriteAddr, u16 _usWriteSize)
{
	u16 NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

	Addr = _uiWriteAddr % pSF->PageSize;
	count = pSF->PageSize - Addr;
	NumOfPage =  _usWriteSize / pSF->PageSize;
	NumOfSingle = _usWriteSize % pSF->PageSize;

	if (Addr == 0) /* 起始地址是页面首地址  */
	{
		if (NumOfPage == 0) /* 数据长度小于页面大小 */
		{
			if (sf_AutoWritePage(_pBuf, _uiWriteAddr, _usWriteSize) == 0)
			{
				return 0;
			}
		}
		else 	/* 数据长度大于等于页面大小 */
		{
			while (NumOfPage--)
			{
				if (sf_AutoWritePage(_pBuf, _uiWriteAddr, pSF->PageSize) == 0)
				{
					return 0;
				}
				_uiWriteAddr +=  pSF->PageSize;
				_pBuf += pSF->PageSize;
			}
			if (sf_AutoWritePage(_pBuf, _uiWriteAddr, NumOfSingle) == 0)
			{
				return 0;
			}
		}
	}
	else  /* 起始地址不是页面首地址  */
	{
		if (NumOfPage == 0) /* 数据长度小于页面大小 */
		{
			if (NumOfSingle > count) /* (_usWriteSize + _uiWriteAddr) > SPI_FLASH_PAGESIZE */
			{
				temp = NumOfSingle - count;

				if (sf_AutoWritePage(_pBuf, _uiWriteAddr, count) == 0)
				{
					return 0;
				}

				_uiWriteAddr +=  count;
				_pBuf += count;

				if (sf_AutoWritePage(_pBuf, _uiWriteAddr, temp) == 0)
				{
					return 0;
				}
			}
			else
			{
				if (sf_AutoWritePage(_pBuf, _uiWriteAddr, _usWriteSize) == 0)
				{
					return 0;
				}
			}
		}
		else	/* 数据长度大于等于页面大小 */
		{
			_usWriteSize -= count;
			NumOfPage =  _usWriteSize / pSF->PageSize;
			NumOfSingle = _usWriteSize % pSF->PageSize;

			if (sf_AutoWritePage(_pBuf, _uiWriteAddr, count) == 0)
			{
				return 0;
			}

			_uiWriteAddr +=  count;
			_pBuf += count;

			while (NumOfPage--)
			{
				if (sf_AutoWritePage(_pBuf, _uiWriteAddr, pSF->PageSize) == 0)
				{
					return 0;
				}
				_uiWriteAddr +=  pSF->PageSize;
				_pBuf += pSF->PageSize;
			}

			if (NumOfSingle != 0)
			{
				if (sf_AutoWritePage(_pBuf, _uiWriteAddr, NumOfSingle) == 0)
				{
					return 0;
				}
			}
		}
	}
	return 1;	/* 成功 */
}

/*
*********************************************************************************************************
*	函 数 名: sf_ReadID
*	功能说明: 读取器件ID
*	形    参:  无
*	返 回 值: 32bit的器件ID (最高8bit填0，有效ID位数为24bit）
*********************************************************************************************************
*/
u32 sf_ReadID(void)
{
	u32 uiID;
	u8 id1, id2, id3;

	SF_CS_L();									/* 使能片选 */
	sf_SendByte(CMD_RDID);						/* 发送读ID命令 */
	id1 = sf_SendByte(DUMMY_BYTE);				/* 读ID的第1个字节 */
	id2 = sf_SendByte(DUMMY_BYTE);				/* 读ID的第2个字节 */
	id3 = sf_SendByte(DUMMY_BYTE);				/* 读ID的第3个字节 */
	SF_CS_H();									/* 禁能片选 */

	uiID = ((u32)id1 << 16) | ((u32)id2 << 8) | id3;

	return uiID;
}


/*
*********************************************************************************************************
*	函 数 名: sf_SendByte
*	功能说明: 向器件发送一个字节，同时从MISO口线采样器件返回的数据
*	形    参:  _ucByte : 发送的字节值
*	返 回 值: 从MISO口线采样器件返回的数据
*********************************************************************************************************
*/
static u8 sf_SendByte(u8 _ucValue)
{
	/* 等待上个数据未发送完毕 */
	while (SPI_I2S_GetFlagStatus(SPI_FLASH, SPI_I2S_FLAG_TXE) == RESET);

	/* 通过SPI硬件发送1个字节 */
	SPI_I2S_SendData(SPI_FLASH, _ucValue);

	/* 等待接收一个字节任务完成 */
	while (SPI_I2S_GetFlagStatus(SPI_FLASH, SPI_I2S_FLAG_RXNE) == RESET);

	/* 返回从SPI总线读到的数据 */
	return SPI_I2S_ReceiveData(SPI_FLASH);
}

/*
*********************************************************************************************************
*	函 数 名: sf_WriteEnable
*	功能说明: 向器件发送写使能命令
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
static void sf_WriteEnable(void)
{
	SF_CS_L();									/* 使能片选 */
	sf_SendByte(CMD_WREN);								/* 发送命令 */
	SF_CS_H();									/* 禁能片选 */
}

/*
*********************************************************************************************************
*	函 数 名: sf_WriteStatus
*	功能说明: 写状态寄存器
*	形    参:  _ucValue : 状态寄存器的值
*	返 回 值: 无
*********************************************************************************************************
*/
static void sf_WriteStatus(u8 _ucValue)
{
	SF_CS_L();									/* 使能片选 */
	sf_SendByte(CMD_WRSR);						/* 发送命令， 写状态寄存器 */
	sf_SendByte(_ucValue);						/* 发送数据：状态寄存器的值 */
	SF_CS_H();									/* 禁能片选 */
}

/*
*********************************************************************************************************
*	函 数 名: sf_WaitForWriteEnd
*	功能说明: 采用循环查询的方式等待器件内部写操作完成
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
static void sf_WaitForWriteEnd(void)
{
	SF_CS_L();									/* 使能片选 */
	sf_SendByte(CMD_RDSR);							/* 发送命令， 读状态寄存器 */
	while((sf_SendByte(DUMMY_BYTE) & WIP_FLAG) == SET);	/* 判断状态寄存器的忙标志位 */
	SF_CS_H();									/* 禁能片选 */
}

/*=========================================================================================*/
/*=========================================================================================*/

BOOL SF_Write(u8 *buf,u32 addr,u32 size)
{
	SYS_mutex_lock(mutex_lock,5000);

	sf_WriteBuffer(buf,addr,size);

	SYS_mutex_unlock(mutex_lock);
	return TRUE;
}

BOOL SF_Read(u8 *buf,u32 addr,u32 size)
{
	SYS_mutex_lock(mutex_lock,5000);

	sf_ReadBuffer(buf,addr,size);

	SYS_mutex_unlock(mutex_lock);
	return TRUE;
}

/*=========================================================================================*/

