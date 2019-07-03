/*
 * audio_drv.c
 *
 *  Created on: 2016年3月6日
 *      Author: Administrator
 */


#include "Include.h"
#include "BSP.h"


void audio_hard_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;


	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC, ENABLE);			//使能外设GPIOB,GPIOC时钟

	// 复用功能输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化

	//复用功能输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化

	GPIO_PinAFConfig(GPIOB,GPIO_PinSource12,GPIO_AF_SPI2);  //PB12,  I2S_LRCK
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource13,GPIO_AF_SPI2);	//PB13,  I2S_SCLK
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_SPI2);	//PB15,  I2S_DACDATA
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_SPI2);	//PC6 ,  I2S_MCK
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_SPI2);	//PC2 ,  I2S_ADCDATA  I2S2ext_SD是AF6!!!
 	WM8978_ADDA_Cfg(1,0);
 	WM8978_Input_Cfg(0,0,0);
 	WM8978_Output_Cfg(1,0);

	////
	WM8978_HPvol_Set(0,0);
	WM8978_SPKvol_Set(0);

	////
	WM8978_EQ1_Set(0,10);
	WM8978_EQ1_Set(1,10);
	WM8978_EQ1_Set(2,10);
	WM8978_EQ1_Set(3,12);

	WM8978_EQ4_Set(0,18);
	WM8978_EQ4_Set(1,18);
	WM8978_EQ4_Set(2,18);
	WM8978_EQ4_Set(3,18);

	WM8978_EQ5_Set(0,22);
	WM8978_EQ5_Set(1,22);
	WM8978_EQ5_Set(2,22);
	WM8978_EQ5_Set(3,22);


}

void audio_hard_deinit(void)
{
	I2S2_Play_Stop();
}

static u8 *play_buf1=NULL;
static u8 *play_buf2=NULL;
static u8  buf_idx=0;

static sem_obj *sem_rdy=NULL;

static void wav_dma_tx_callback(void)
{
	u16 i;
	if(DMA1_Stream4->CR&(1<<19))
	{
		buf_idx =0;
		//DebugPuts("0");
	}
	else
	{
		buf_idx =1;
		//DebugPuts("1");
	}

	SYS_sem_post(sem_rdy);
}

static void I2S2_TXMode_Config(const uint16_t _usStandard,const uint16_t _usWordLen,const uint32_t _usAudioFreq)
{
	I2S_InitTypeDef I2S_InitStructure;
	uint32_t n = 0;
	FlagStatus status = RESET;
/**
	*	For I2S mode, make sure that either:
	*		- I2S PLL is configured using the functions RCC_I2SCLKConfig(RCC_I2S2CLKSource_PLLI2S),
	*		RCC_PLLI2SCmd(ENABLE) and RCC_GetFlagStatus(RCC_FLAG_PLLI2SRDY).
	*/
	RCC_I2SCLKConfig(RCC_I2S2CLKSource_PLLI2S);
	RCC_PLLI2SCmd(ENABLE);
	for (n = 0; n < 500; n++)
	{
		status = RCC_GetFlagStatus(RCC_FLAG_PLLI2SRDY);
		if (status == 1) break;
	}
	/* 打开 I2S2 APB1 时钟 */
	RCC_APB1PeriphClockCmd(SPI2, ENABLE);

	/* 复位 SPI2 外设到缺省状态 */
	SPI_I2S_DeInit(SPI2);

	/* I2S2 外设配置 */
	I2S_InitStructure.I2S_Mode = I2S_Mode_MasterTx;			/* 配置I2S工作模式 */
	I2S_InitStructure.I2S_Standard = _usStandard;			/* 接口标准 */
	I2S_InitStructure.I2S_DataFormat = _usWordLen;			/* 数据格式，16bit */
	I2S_InitStructure.I2S_MCLKOutput = I2S_MCLKOutput_Enable;	/* 主时钟模式 */
	I2S_InitStructure.I2S_AudioFreq = _usAudioFreq;			/* 音频采样频率 */
	I2S_InitStructure.I2S_CPOL = I2S_CPOL_Low;
	I2S_Init(SPI2, &I2S_InitStructure);

	/* 使能 SPI2/I2S2 外设 */
	I2S_Cmd(SPI2, ENABLE);
}

void audio_format_init(u32 bps,u32 sample_rate,u32 size)
{

	sem_rdy =SYS_sem_create(1,1,NULL);

	buf_idx =0;
	play_buf1 =vmalloc(size);
	play_buf2 =vmalloc(size);

	memset(play_buf1,0,size);
	memset(play_buf2,0,size);

	if(bps==16)
	{
		DebugPrintf("I2S2_Init 16bit.\r\n");
		WM8978_I2S_Cfg(WM8978_Phlips_I2S,WM8978_16bit);
		I2S2_Init(I2S_Standard_Phillips,I2S_Mode_MasterTx,I2S_CPOL_Low,I2S_DataFormat_16b,sample_rate);		//飞利浦标准,主机发送,时钟低电平有效,16位扩展帧长度
		I2S2_TX_DMA_Init(play_buf1,play_buf2,size/2,wav_dma_tx_callback); //配置TX DMA
	}
	else if(bps==24)
	{
		DebugPrintf("I2S2_Init 24bit.\r\n");
		WM8978_I2S_Cfg(WM8978_Phlips_I2S,WM8978_24bit);
		I2S2_Init(I2S_Standard_Phillips,I2S_Mode_MasterTx,I2S_CPOL_Low,I2S_DataFormat_24b,sample_rate);		//飞利浦标准,主机发送,时钟低电平有效,24位扩展帧长度
		I2S2_TX_DMA_Init(play_buf1,play_buf2,size/4,wav_dma_tx_callback); //配置TX DMA
	}
	I2S2_SampleRate_Set(sample_rate);//设置采样率

}

void audio_format_deinit(void)
{
	I2S2_Play_Stop();

	SYS_sem_destroy(sem_rdy);
	vfree(play_buf1);
	vfree(play_buf2);

}

void* audio_wait_buffer(int wait_ms)
{
	if(SYS_sem_wait(sem_rdy,wait_ms) == SYS_NO_ERR)
	{
		if(buf_idx==0)
		{
			return play_buf1;
		}
		else
		{
			return play_buf2;
		}
	}
	return NULL;
}

void audio_set_volume(u8 l,u8 r)
{
	l >>= 2;
	r >>= 2;

	WM8978_HPvol_Set(l,r);
	WM8978_SPKvol_Set((l+r)>>1);

}

//开始音频播放
void audio_start(void)
{
	I2S2_Play_Start();
}

//停止音频播放
void audio_stop(void)
{
	I2S2_Play_Stop();
}
