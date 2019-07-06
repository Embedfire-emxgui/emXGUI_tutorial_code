
#include "BSP.h"

#define IIC_SPEED_100KHZ     1
#define IIC_SPEED_200KHZ     2
#define IIC_SPEED_400KHZ     3
#define IIC_SPEED_800KHZ     4

/*=========================================================================================*/
//#define	SCL_GPIO_RCC_Init()		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE)
#define	SCL_GPIO				GPIOF
#define	SCL_PIN					GPIO_Pin_10
#define	SCL_BIT					GPIO_PinSource10

//#define	SDA_GPIO_RCC_Init()		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE)
#define	SDA_GPIO				GPIOF
#define	SDA_PIN					GPIO_Pin_6
#define SDA_BIT					GPIO_PinSource6


//IO操作函数
#define IIC_SCL(x)		if(x){GPIO_SetBits(GTP_I2C_SCL_GPIO_PORT, GTP_I2C_SCL_PIN);}else{GPIO_ResetBits(GTP_I2C_SCL_GPIO_PORT, GTP_I2C_SCL_PIN);}
#define IIC_SDA(x)		if(x){GPIO_SetBits(GTP_I2C_SDA_GPIO_PORT, GTP_I2C_SDA_PIN);}else{GPIO_ResetBits(GTP_I2C_SDA_GPIO_PORT, GTP_I2C_SDA_PIN);}
#define READ_SDA		  (GPIO_ReadInputDataBit(GTP_I2C_SDA_GPIO_PORT, GTP_I2C_SDA_PIN))  		//读取SDA

/*I2C引脚*/
#define GTP_I2C_SCL_PIN                  GPIO_Pin_10                 
#define GTP_I2C_SCL_GPIO_PORT            GPIOF                     
#define GTP_I2C_SCL_GPIO_CLK             RCC_APB2Periph_GPIOF
#define GTP_I2C_SCL_SOURCE               GPIO_PinSource10

#define GTP_I2C_SDA_PIN                  GPIO_Pin_6                 
#define GTP_I2C_SDA_GPIO_PORT            GPIOF                    
#define GTP_I2C_SDA_GPIO_CLK             RCC_APB2Periph_GPIOF
#define GTP_I2C_SDA_SOURCE               GPIO_PinSource6

/*复位引脚*/
#define GTP_RST_GPIO_PORT                GPIOF
#define GTP_RST_GPIO_CLK                 RCC_APB2Periph_GPIOF
#define GTP_RST_GPIO_PIN                 GPIO_Pin_11
/*中断引脚*/
#define GTP_INT_GPIO_PORT                GPIOF
#define GTP_INT_GPIO_CLK                 RCC_APB2Periph_GPIOF
#define GTP_INT_GPIO_PIN                 GPIO_Pin_9

/*=========================================================================================*/

static void SDA_IN(void)
{	//SDA 输入模式
//	volatile int i;

//	SDA_GPIO->MODER &= ~(3<<(SDA_BIT*2));
//	for(i=0;i<5;i++);
}

static	void SDA_OUT(void)
{	//SDA 输出模式
//	volatile int i;

//	SDA_GPIO->MODER &= ~(3<<(SDA_BIT*2));
//	SDA_GPIO->MODER |=  (1<<(SDA_BIT*2));
//	for(i=0;i<5;i++);
}


//初始化IIC
static BOOL IIC_PortInit(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;  
  
  /*使能触摸屏使用的引脚的时钟*/
  RCC_APB2PeriphClockCmd(GTP_I2C_SCL_GPIO_CLK|
                       	 GTP_I2C_SDA_GPIO_CLK|
	                       GTP_RST_GPIO_CLK|GTP_INT_GPIO_CLK, 
	                       ENABLE);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    
  /*配置SCL引脚 */   
  GPIO_InitStructure.GPIO_Pin = GTP_I2C_SCL_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GTP_I2C_SCL_GPIO_PORT, &GPIO_InitStructure);

  /*配置SDA引脚 */
  GPIO_InitStructure.GPIO_Pin = GTP_I2C_SDA_PIN;
  GPIO_Init(GTP_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);
 
  /*配置RST引脚，推挽输出 */   
  GPIO_InitStructure.GPIO_Pin = GTP_RST_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GTP_RST_GPIO_PORT, &GPIO_InitStructure);
  
  /*配置 INT引脚，推挽输出，方便初始化 */   
  GPIO_InitStructure.GPIO_Pin = GTP_INT_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//设置为下拉，方便初始化
  GPIO_Init(GTP_INT_GPIO_PORT, &GPIO_InitStructure);
	return TRUE;
}


/*=========================================================================================*/
#define		IIC_DELAY_COUNT	220 //for 100KZ
#define		IIC_MASTER

/*=========================================================================================*/

static volatile int speed=IIC_SPEED_100KHZ;

static void iic_delay(void)
{
	volatile int a,b;

	b =IIC_DELAY_COUNT;
	switch(speed)
	{
		case IIC_SPEED_100KHZ:
			b = b>>0;
			break;
		case IIC_SPEED_200KHZ:
			b = b>>1;
			break;
		case IIC_SPEED_400KHZ:
			b = b>>2;
			break;
		case IIC_SPEED_800KHZ:
			b = b>>3;
			break;
	}

	for(a=0;a<b;a++);

}

static void IIC_Stop(void);

static	mutex_obj *mutex_lock=NULL;

//初始化IIC
static BOOL IIC_Init(void)
{
	
	if(IIC_PortInit())
	{
		mutex_lock =SYS_mutex_create(NULL);


		//给一个停止信号, 复位I2C总线上的所有设备到待机模式
		IIC_Stop();
		return TRUE;
	}
	return FALSE;
}

static BOOL IIC_Open(int iic_speed)
{
	SYS_mutex_lock(mutex_lock,5000);
	speed =iic_speed;
	return TRUE;
}

static void IIC_Close(void)
{
	SYS_mutex_unlock(mutex_lock);
}

/*=========================================================================================*/

//产生IIC起始信号
static void IIC_Start(void)
{//START:when CLK is high,DATA change form high to low

	SDA_OUT();	//sda线输出
	IIC_SDA(1);
	IIC_SCL(1);
	iic_delay();
	iic_delay();
 	IIC_SDA(0);
	iic_delay();
	iic_delay();
	IIC_SCL(0);//钳住I2C总线，准备发送或接收数据 
	iic_delay();
	iic_delay();
	iic_delay();
	iic_delay();
}	  

//产生IIC停止信号
static void IIC_Stop(void)
{//STOP:when CLK is high DATA change form low to high

	SDA_OUT();//sda线输出
	IIC_SCL(0);
	IIC_SDA(0);
 	iic_delay();
 	iic_delay();
	IIC_SCL(1); 
	iic_delay();
	iic_delay();
	IIC_SDA(1);//发送I2C总线结束信号
	iic_delay();
	iic_delay();
}


//等待应答信号到来
static BOOL IIC_Wait_Ack(void)
{
	u16 timeout=0;

	SDA_IN();      //SDA设置为输入  
	IIC_SDA(1);
	iic_delay();
	IIC_SCL(1);    //CPU驱动SCL = 1, 此时器件会返回ACK应答
	iic_delay();
	while(READ_SDA)
	{
		if(timeout++ > 1000)
		{
			return FALSE;
		}
	}
	IIC_SCL(0);//时钟输出0
	iic_delay();
	return TRUE;
} 

//产生ACK应答
static void IIC_Ack(void)
{
	SDA_OUT();
	IIC_SDA(0);   //CPU驱动SDA = 0
	iic_delay();
	IIC_SCL(1);   //CPU产生1个时钟
	iic_delay();
	IIC_SCL(0);
	iic_delay();

	IIC_SDA(1);   //CPU释放SDA总线
}

//不产生ACK应答		    
static void IIC_NAck(void)
{
	SDA_OUT();
	IIC_SDA(1);   //CPU驱动SDA = 1
	iic_delay();
	IIC_SCL(1);   //CPU产生1个时钟
	iic_delay();
	IIC_SCL(0);
	iic_delay();

}

//IIC发送一个字节
//返回从机有无应答
static BOOL IIC_Send_Byte(u8 txd,u8 ack)
{                        
	int i;

	SDA_OUT(); 	    
    for(i=0;i<8;i++)
    {
        IIC_SCL(0);//拉低时钟开始数据传输
        iic_delay();

    	if(txd&0x80)
    	{
    		IIC_SDA(1);
    	}
    	else
    	{
    		IIC_SDA(0);
    	}

        txd <<= 1;
		iic_delay();
		IIC_SCL(1);
		iic_delay();

    }
    IIC_SCL(0);
    IIC_SDA(1); //free SDA
    if(ack == IIC_NoACK)
    {
    	return TRUE;
    }

	if(IIC_Wait_Ack())
	{
		return TRUE;
	}

	return FALSE;
} 	    

//读1个字节.
static u8 IIC_Read_Byte(u8 ack)
{
	u8 i,dat=0;
	SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
		IIC_SCL(1);
		iic_delay();
		dat<<=1;
        if(READ_SDA)
        {
        	dat |= 0x01;
        }
        IIC_SCL(0);
        iic_delay();
    }

    if(ack==IIC_ACK)
    {
    	IIC_Ack(); //发送ACK
    }
    else
    {
    	IIC_NAck();//发送nACK
    }
    return dat;
}

/*=========================================================================================*/

const struct	i2c_ops I2C_GPD7_GPD3={

	IIC_Init,
	IIC_Open,
	IIC_Close,
	IIC_Start,
	IIC_Stop,
	IIC_Send_Byte,
	IIC_Read_Byte,
};

/*=========================================================================================*/

