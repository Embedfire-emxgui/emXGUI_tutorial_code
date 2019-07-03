
#include	"BSP.h"

/*============================================================================================*/

void DebugUart_Init(void)
{
#if 0
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	//配置GPIO用于USART1

	/* 打开 GPIO 时钟 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	/* 打开 UART 时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);


	/* 将 PA9 映射为 USART1_TX */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);

	/* 将 PA10 映射为 USART1_RX */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

	/* 配置 USART Tx 为复用功能 */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	/* 输出类型为推挽 */
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	/* 内部上拉电阻使能 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	/* 复用模式 */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* 配置 USART Rx 为复用功能 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStructure);



	// 配置USART参数
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);

	USART_ClearFlag(USART1,USART_IT_TXE);

	// USART1接收中断使能,配置NVIC,使能USART1
	//USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	//USART1_NVIC_Config();

	USART_Cmd(USART1, ENABLE);

	/* CPU的小缺陷：串口配置好，如果直接Send，则第1个字节发送不出去,如下语句解决第1个字节无法正确发送出去的问题 */
	USART_ClearFlag(USART1, USART_FLAG_TC);     /* 清发送完成标志，Transmission Complete flag */

	//DebugPuts("\r\n");
	//DebugPuts("UART1 Init OK.\r\n");
#endif
}
/*============================================================================================*/


void	DbgUart_Send(const char *buf,int size)
{
#if 0
	int i;
	for(i=0;i<size;i++)
	{
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET); //等待数据发送完毕
		USART_SendData(USART1,buf[i]);
	}
#endif
}
/*============================================================================================*/

int	SysDrv_stdin(char *buf,int size)
{
 	return	-1;
}

int	SysDrv_stdout(const char *buf,int size)
{
  DbgUart_Send(buf,size);
  return TRUE;
}

int	SysDrv_stderr(const char *buf,int size)
{
  DbgUart_Send(buf,size);
  return TRUE;
}

/*============================================================================================*/


