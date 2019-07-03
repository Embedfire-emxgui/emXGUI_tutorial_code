
#include "Kernel.h"
#include "BSP.h"

/*=========================================================================================*/
#define	SCL_PIN	GPIOD,GPIO_Pin_7
#define	SDA_PIN	GPIOD,GPIO_Pin_3

//IO操作函数
#define IIC_SCL(x)		GPIO_Pin_Set(SCL_PIN,x)		//SCL
#define IIC_SDA(x)		GPIO_Pin_Set(SDA_PIN,x)		//SDA
#define READ_SDA		GPIO_Pin_Get(SDA_PIN)   	//读取SDA

/*=========================================================================================*/

static void SDA_IN(void)
{	//PD3 输入模式
	volatile int i;

	GPIOD->MODER &= ~(3<<(3*2));
	for(i=0;i<5;i++);
}

static	void SDA_OUT(void)
{	//PD3 输出模式
	volatile int i;

	GPIOD->MODER &= ~(3<<(3*2));
	GPIOD->MODER |=  (1<<(3*2));
	for(i=0;i<5;i++);
}

/*=========================================================================================*/

static void iic_delay(int loop)
{
	volatile int a;

	while(loop-- > 0)
	{
		for(a=0;a<50;a++);
	}
}

static void IIC_Stop(void);

static	mutex_obj *mutex_lock=NULL;

//初始化IIC
static BOOL IIC_Init(void)
{
	GPIO_InitTypeDef gpio_init;

	mutex_lock =SYS_mutex_create(NULL);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); //打开GPIO时钟

	gpio_init.GPIO_Mode  = GPIO_Mode_OUT;
	gpio_init.GPIO_OType = GPIO_OType_PP; 	//PP模式比OD模式有更高的速度,更强的驱动能力和抗干扰能力...
	gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;	//上拉电阻使能
	gpio_init.GPIO_Speed = GPIO_Speed_25MHz;
	gpio_init.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_3;
	GPIO_Init(GPIOD, &gpio_init);
	
	//给一个停止信号, 复位I2C总线上的所有设备到待机模式
	IIC_Stop();
	return TRUE;
}

static BOOL IIC_Open(void)
{
	SYS_mutex_lock(mutex_lock,5000);
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
	iic_delay(2);
 	IIC_SDA(0);
	iic_delay(2);
	IIC_SCL(0);//钳住I2C总线，准备发送或接收数据 
	iic_delay(2);
}	  

//产生IIC停止信号
static void IIC_Stop(void)
{//STOP:when CLK is high DATA change form low to high

	SDA_OUT();//sda线输出
	IIC_SCL(0);
	IIC_SDA(0);
 	iic_delay(2);
	IIC_SCL(1); 
	iic_delay(2);
	IIC_SDA(1);//发送I2C总线结束信号
	iic_delay(2);
}


//等待应答信号到来
static BOOL IIC_Wait_Ack(void)
{
	u16 timeout=0;

	SDA_IN();      //SDA设置为输入  
	IIC_SDA(1);
	iic_delay(1);
	IIC_SCL(1);    //CPU驱动SCL = 1, 此时器件会返回ACK应答
	iic_delay(1);
	while(READ_SDA)
	{
		if(timeout++ > 1000)
		{
			return FALSE;
		}
	}
	IIC_SCL(0);//时钟输出0
	iic_delay(1);
	return TRUE;
} 

//产生ACK应答
static void IIC_Ack(void)
{
	SDA_OUT();
	IIC_SDA(0);   //CPU驱动SDA = 0
	iic_delay(1);
	IIC_SCL(1);   //CPU产生1个时钟
	iic_delay(1);
	IIC_SCL(0);
	iic_delay(1);

	IIC_SDA(1);   //CPU释放SDA总线
}

//不产生ACK应答		    
static void IIC_NAck(void)
{
	SDA_OUT();
	IIC_SDA(1);   //CPU驱动SDA = 1
	iic_delay(1);
	IIC_SCL(1);   //CPU产生1个时钟
	iic_delay(1);
	IIC_SCL(0);
	iic_delay(1);

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
        iic_delay(1);

    	if(txd&0x80)
    	{
    		IIC_SDA(1);
    	}
    	else
    	{
    		IIC_SDA(0);
    	}

        txd <<= 1;
		iic_delay(1);
		IIC_SCL(1);
		iic_delay(1);

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
		iic_delay(1);
		dat<<=1;
        if(READ_SDA)
        {
        	dat |= 0x01;
        }
        IIC_SCL(0);
        iic_delay(1);
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

