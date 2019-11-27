/*
 * DMA_LCD.c
 *
 *  Created on: 2018年6月28日
 *      Author: liuwei
 */

#include "def.h"
#include "DMA_LCD.h"
#include "FreeRTOS.h"
#include "board.h"
#include "semphr.h"
/*=========================================================================================*/

#define	LCD_DMA_CLK_EN()		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE)
#define	LCD_DMA_Stream		DMA2_Stream0
#define	LCD_DMA_Channel		DMA_Channel_0
#define	LCD_DMA_IRQn		DMA2_Stream0_IRQn


static	const int LCD_DMA_MAX_TRANS	= 0xFFF0;

/*=========================================================================================*/

static GUI_SEM* sem_rdy = NULL;

static volatile int dma_busy=FALSE;

//static void dma_isr(void)
//{
//	DMA_ClearFlag(LCD_DMA_Stream,DMA_FLAG_TCIF0);//清除传输完成中断
//	dma_busy=FALSE;
//	SYS_sem_post(sem_rdy);
//}

void DMA2_Stream0_IRQHandler(void)
{
  uint32_t ulReturn;
  BaseType_t pxHigherPriorityTaskWoken;
  
  /* 进入临界段，临界段可以嵌套 */
  ulReturn = taskENTER_CRITICAL_FROM_ISR();
  
  if(DMA_GetITStatus(DMA2_Stream0,DMA_IT_TCIF0)==SET)
  {
    DMA_ClearITPendingBit(DMA2_Stream0,DMA_IT_TCIF0);//清除传输完成中断
    dma_busy=FALSE;
    
    xSemaphoreGiveFromISR(sem_rdy, &pxHigherPriorityTaskWoken);
    //如果需要的话进行一次任务切换，系统会判断是否需要进行切换
    portYIELD_FROM_ISR(pxHigherPriorityTaskWoken);
//    GUI_SemPost(sem_rdy);
  }
  
  /* 退出临界段 */
  taskEXIT_CRITICAL_FROM_ISR( ulReturn );
}

//void DMA2_Stream0_IRQHandler(void)
//{
//	mk_isr_enter();

//	if(DMA_GetITStatus(DMA2_Stream0,DMA_IT_TCIF0)==SET)
//	{
//		DMA_ClearITPendingBit(DMA2_Stream0,DMA_IT_TCIF0);

//		if(pfnDMA2Isr[0]!=NULL)
//			pfnDMA2Isr[0]();
//	}

//	mk_isr_exit();
//}

/*=========================================================================================*/

static u32 LCD_DAT_ADR=0;

void LCD_DMA_Init(u32 lcd_dat_addr)
{
	DMA_InitTypeDef  DMA_InitStructure;

	LCD_DAT_ADR =lcd_dat_addr;

	sem_rdy = GUI_SemCreate(0,1);

	LCD_DMA_CLK_EN(); //DMA2时钟使能

	while (DMA_GetCmdStatus(LCD_DMA_Stream) != DISABLE){}//等待DMA2_Stream1可配置
	DMA_DeInit(LCD_DMA_Stream);

	/* 配置 DMA Stream */
	DMA_InitStructure.DMA_Channel         = LCD_DMA_Channel;  //通道0
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)lcd_dat_addr;//&LCD->LCD_RAM;;//DMA 存储器0地址
	DMA_InitStructure.DMA_PeripheralBaseAddr=0;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToMemory;//存储器到存储器模式
	DMA_InitStructure.DMA_BufferSize = 0;//数据传输量
	DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;//外设增量模式
	DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Disable;//存储器非增量模式
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//外设数据长度:16位
	DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;//存储器数据长度 16位
	DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;// 使用普通模式
	DMA_InitStructure.DMA_Priority           = DMA_Priority_VeryHigh;//高优先级

	DMA_InitStructure.DMA_FIFOMode           = DMA_FIFOMode_Enable; //FIFO模式
	DMA_InitStructure.DMA_FIFOThreshold      = DMA_FIFOThreshold_HalfFull;

	DMA_InitStructure.DMA_MemoryBurst        = DMA_MemoryBurst_INC4;//外设突发单次传输
	DMA_InitStructure.DMA_PeripheralBurst    = DMA_PeripheralBurst_INC8;//存储器突发单次传输
	DMA_Init(LCD_DMA_Stream, &DMA_InitStructure);//初始化DMA Stream

	DMA_ITConfig(LCD_DMA_Stream,DMA_IT_TC,ENABLE);//开启传输完成中断
//	DMA_SetIRQHandler(LCD_DMA_Stream,dma_isr);
	if(1)
	{
		NVIC_InitTypeDef   nvic_init;
		nvic_init.NVIC_IRQChannel = LCD_DMA_IRQn;
		nvic_init.NVIC_IRQChannelPreemptionPriority =0x05;//抢占优先级0
		nvic_init.NVIC_IRQChannelSubPriority = 0x01;//子优先级1
		nvic_init.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
		NVIC_Init(&nvic_init);//配置
	}

}


static u16 dat_v;

void LCD_DMA_WaitBusy(void)
{
	while(dma_busy==TRUE);

//	DMA_Cmd(LCD_DMA_Stream,DISABLE);//关闭DMA2,Stream0
//	while (DMA_GetCmdStatus(LCD_DMA_Stream) != DISABLE){}//等待DMA2_Stream0可配置
//	DMA_ClearFlag(LCD_DMA_Stream,DMA_FLAG_TCIF0);//清除传输完成中断

}

static void LCD_DMA_Execu(u32 dst,u32 src,int count,int src_inc)
{
	LCD_DMA_Stream->M0AR =dst;
	LCD_DMA_Stream->PAR  =src;

	while(count > 0)
	{
		if(count > (int)LCD_DMA_MAX_TRANS)
		{
			LCD_DMA_Stream->NDTR =LCD_DMA_MAX_TRANS; //设置传输长度
			count -= LCD_DMA_MAX_TRANS;

			dma_busy=TRUE;
			LCD_DMA_Stream->CR |= (uint32_t)DMA_SxCR_EN;  //开启DMA
			GUI_SemWait(sem_rdy,1000);

			if(src_inc)
			{
				src += LCD_DMA_MAX_TRANS*2; //halfword.
				LCD_DMA_Stream->PAR  =src;
			}
		}
		else
		{

			LCD_DMA_Stream->NDTR =count; //设置传输长度
			count =0;

			dma_busy=TRUE;
			LCD_DMA_Stream->CR |= (uint32_t)DMA_SxCR_EN;  //开启DMA
			GUI_SemWait(sem_rdy,1000);
			break;

		}

	}

}


BOOL LCD_DMA_WritePixels(u16 val,s32 count)
{

	if(count < (20*20))
	{
		return FALSE;
	}

	LCD_DMA_WaitBusy();

	dat_v =val;
	LCD_DMA_Stream->CR &= ~DMA_MemoryInc_Enable;
	LCD_DMA_Stream->CR &= ~DMA_PeripheralInc_Enable;

	LCD_DMA_Execu(LCD_DAT_ADR,(u32)&dat_v,count,FALSE);

	return TRUE;

}


BOOL LCD_DMA_WriteBitmap(u16 *src,int count)
{

	if(count < (20*20))
	{
		return FALSE;
	}

	LCD_DMA_WaitBusy();

	LCD_DMA_Stream->CR &= ~DMA_MemoryInc_Enable;
	LCD_DMA_Stream->CR |=  DMA_PeripheralInc_Enable;

	LCD_DMA_Execu(LCD_DAT_ADR,(u32)src,count,TRUE);

	return TRUE;
}



/*=========================================================================================*/
/*=========================================================================================*/
