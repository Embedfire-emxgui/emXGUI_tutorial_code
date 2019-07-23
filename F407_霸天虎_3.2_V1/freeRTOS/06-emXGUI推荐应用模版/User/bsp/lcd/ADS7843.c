
#include	"GUI_Drv.h"
#include	"board.h"

/*=====================================================================*/
// CS   - PF10
// SCLK - PG7
// MOSI - PF11
// MISO - PF6
// IRQ  - PF9

#define	CS_PORT		GPIOD
#define	CS_PIN		GPIO_Pin_7

#define	SCLK_PORT	GPIOG
#define	SCLK_PIN	GPIO_Pin_9

#define	MOSI_PORT	GPIOD
#define	MOSI_PIN	GPIO_Pin_6

#define	MISO_PORT	GPIOD
#define	MISO_PIN	GPIO_Pin_3

#define	IRQ_PORT	GPIOG
#define	IRQ_PIN		GPIO_Pin_8

// CS   - PB0
#define	CS_0()		CS_PORT->BSRRH = CS_PIN
#define	CS_1()		CS_PORT->BSRRL = CS_PIN

// SCLK - PB14
#define	SCLK_0()	SCLK_PORT->BSRRH = SCLK_PIN
#define	SCLK_1()	SCLK_PORT->BSRRL = SCLK_PIN

// MOSI - PB1
#define	MOSI_0()	MOSI_PORT->BSRRH = MOSI_PIN
#define	MOSI_1()	MOSI_PORT->BSRRL = MOSI_PIN

// MISO - PB2
#define	MISO()		((MISO_PORT->IDR & MISO_PIN) != 0)

// IRQ  - PF11
#define TP_IRQ()	((IRQ_PORT->IDR & IRQ_PIN) != 0)

/*=====================================================================*/
//static
 BOOL	ADS7843_HardInit(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOG, ENABLE);//使能PD,,PG时钟
  
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;//输出
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;//上拉

  GPIO_InitStructure.GPIO_Pin = CS_PIN;//PF5:0
  GPIO_Init(CS_PORT, &GPIO_InitStructure);//初始化

  GPIO_InitStructure.GPIO_Pin = SCLK_PIN;//PF5:0
  GPIO_Init(SCLK_PORT, &GPIO_InitStructure);//初始化

  GPIO_InitStructure.GPIO_Pin = MOSI_PIN;//PF5:0
  GPIO_Init(MOSI_PORT, &GPIO_InitStructure);//初始化
  
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;//推挽输出
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;//输出
  
  GPIO_InitStructure.GPIO_Pin = MISO_PIN;//PF5:0
  GPIO_Init(MISO_PORT, &GPIO_InitStructure);//初始化
  
//  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;//上拉
  
  GPIO_InitStructure.GPIO_Pin = IRQ_PIN;//PF5:0
  GPIO_Init(IRQ_PORT, &GPIO_InitStructure);//初始化

	GUI_DEBUG("ADS7843_Init,\r\n");

	return TRUE;
}

/*=====================================================================*/
// A/D 通道选择命令字和工作寄存器
#define	CHX 	0x90 	//通道Y+的选择控制字	//0x94
#define	CHY 	0xD0	//通道X+的选择控制字	//0xD4

/*=====================================================================*/

static void  delay_us(int t)
{
	volatile int i;

	while(t-->0)
	{
		for(i=0;i<2;i++);
	}
}

/*=====================================================================*/

static BOOL	ADS7843_IsPenDown(void)
{
	if(!TP_IRQ())         // ((GPIOG->IDR >> 8) & 1)
	{
		return TRUE;
	}
	else
	{
//    GUI_DEBUG("没有按下");
		return FALSE;
	}
		
}

/*=====================================================================*/

static	void ADS7843_WrByte(U8 dat)
{
	int  i;
	
    SCLK_0();
	for( i = 0; i < 8; i++ )
	{
		
		if(dat&0x80)			 //时钟上升沿锁存DIN
		{
			MOSI_1();	
		}
		else
		{
			MOSI_0();
		}
		 	
		dat <<=1;
		
		delay_us(1);
		SCLK_0();			//开始发送命令字
		delay_us(1);
		SCLK_1();			//时钟脉冲，一共8个
		delay_us(1);
		SCLK_0();			//时钟脉冲，一共8个
		
	}

}




//插入法排序
static	void InsertSort(int *A, int p, int r)
{
    int i,j;
    int key;
    for(i=p+1; i<=r; i++)
    {
        key = A[i];
        j = i-1;
        while (j >= 0 && A[j] > key)
        {
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = key;
    }
}


//从触摸屏IC读取adc值
//CMD:指令
//返回值:读到的数据
static u16 ADS7843_ReadAD(u8 CMD)
{
	u8 count=0;
	u16 dat=0;

	SCLK_0();		//先拉低时钟
	MOSI_0(); 		//拉低数据线
	CS_0(); 		//选中触摸屏IC

	ADS7843_WrByte(CMD);
	delay_us(6);	//ADS7843的转换时间最长为6us

	SCLK_0(); 	 	//给1个时钟，清除BUSY
	delay_us(1);
	SCLK_1();
	delay_us(1);
	SCLK_0();

	for(count=0;count<16;count++)//读出16位数据,只有高12位有效
	{
		dat <<= 1;

		SCLK_0();	//下降沿有效
		delay_us(1);
 		SCLK_1();
 		if(MISO())
 		{
 			dat |= 1;
 		}
	}

	dat >>= 4;  //只有高12位有效.
	CS_1();		//释放片选

	return dat;
}

////////
#define	COUNT	12
static	int ad_dat[COUNT];

static BOOL	ADS7843_GetXY(u16 *X_Addata,u16 *Y_Addata)
{

	U16	i,x_dat,y_dat;


//	while( ADS7843_IsBusy());			//如果BUSY，等待直到转换完毕，这个可以不用

	////X
	for(i=0;i<COUNT;i++)
	{
		ad_dat[i] =ADS7843_ReadAD(CHX);
	}

	InsertSort(ad_dat,0,COUNT-1);
	i=COUNT>>1;
	x_dat  = ad_dat[i++];
	x_dat += ad_dat[i];
	x_dat >>= 1;
	
	////Y
	for(i=0;i<COUNT;i++)
	{
		ad_dat[i] =ADS7843_ReadAD(CHY);
	}

	InsertSort(ad_dat,0,COUNT-1);
	i=COUNT>>1;
	y_dat  = ad_dat[i++];
	y_dat += ad_dat[i];
	y_dat >>= 1;

	////
	if(0)
	{
//		char buf[40];
//		x_sprintf(buf,"ts_ad: %04XH,%04XH.\r\n",x_dat,y_dat);
//		DebugPuts(buf);
	}
	
	*X_Addata = x_dat;
	*Y_Addata = y_dat;
	
	return TRUE;

}

/*============================================================================*/

//static int ts_x=0,ts_y=0;
static int ts_down=0;

static BOOL Init(void)
{
	ts_down=0;
	ADS7843_HardInit();
	return TRUE;
}

static int GetState(void)
{
	if(ADS7843_IsPenDown())
	{
		ts_down =1;
		return 1;
	}
	ts_down=0;
	return 0;
}

static BOOL GetSample(POINT *pt)
{
	if(ts_down==1)
	{
		u16 x,y;

		ADS7843_GetXY(&x,&y);
		pt->x =x;
		pt->y =y;
		return TRUE;
	}
	return FALSE;
}

static BOOL GetPoint(POINT *pt)
{
	if(GetSample(pt))
	{
#if	GUI_TOUCHSCREEN_CALIBRATE
		TouchPanel_TranslatePoint(LCD_XSIZE,LCD_YSIZE,pt);
#endif
		return TRUE;
	}
	return	TRUE;
}



static BOOL LoadCfg(TS_CFG_DATA *cfg)
{
#if 0
	X_FILE *fp=NULL;
	int i;

	////

	fp=x_fopen("B:ts_cfg.bin","rb");
	if(fp!=NULL)
	{

		i=x_fread((char*)cfg,sizeof(TS_CFG_DATA),1,fp);
		DebugPutHex(0,32,(void*)cfg);

		x_fclose(fp);
		////
		return TRUE;
	}
	else
	{
		cfg->LUx =0x10;
		cfg->LUy =0x10;

		cfg->RUx =0x20;
		cfg->RUy =0x10;

		cfg->RDx =0x20;
		cfg->RDy =0x20;

		cfg->LDx =0x10;
		cfg->LDy =0x20;

		printf("ts_load_config Error\r\n");
		return FALSE;
	}
#endif

/* 设置一个默认值 */
  cfg->LUx =0x10;
  cfg->LUy =0x10;

  cfg->RUx =0x20;
  cfg->RUy =0x10;

  cfg->RDx =0x20;
  cfg->RDy =0x20;

  cfg->LDx =0x10;
  cfg->LDy =0x20;

  SPI_FLASH_BufferRead((uint8_t *)cfg, GUI_TOUCH_CALIBRATEParamAddr, sizeof(TS_CFG_DATA));    // 保存数据
  
  return TRUE;
}

static BOOL SaveCfg(TS_CFG_DATA *cfg)
{
#if 0
	X_FILE *fp;

		////
	
	printf("ts_save_cfg\n");

	fp=x_fopen("B:ts_cfg.bin","wb+");
	if(fp!=NULL)
	{

		x_fwrite((u8*)cfg,sizeof(TS_CFG_DATA),1,fp);
		x_fclose(fp);
		return TRUE;
	}
	////
#endif
  
  cfg->rsv = 0;    // 写入校准标志

  SPI_FLASH_SectorErase(GUI_TOUCH_CALIBRATEParamAddr);    // 擦除要保存的地址
  SPI_FLASH_BufferWrite((uint8_t *)cfg, GUI_TOUCH_CALIBRATEParamAddr, sizeof(TS_CFG_DATA));    // 保存数据
  
	return TRUE;
}

/*============================================================================*/

const GUI_TOUCH_DEV TouchDev_ADS7843=
{
	.Init 		=Init,
	.GetState 	=GetState,
	.GetSample	=GetSample,
	.GetPoint	=GetPoint,
	.LoadCfg	=LoadCfg,
	.SaveCfg	=SaveCfg,
};


/*============================================================================*/

/*=====================================================================*/

