
//#ifdef	IIC_MASTER
///*=========================================================================================*/

///*=========================================================================================*/
//static volatile int speed=IIC_SPEED_100KHZ;

//static void iic_delay(void)
//{
//	volatile int a,b;

//	b =IIC_DELAY_COUNT;
//	switch(speed)
//	{
//		case IIC_SPEED_100KHZ:
//			b = b>>0;
//			break;
//		case IIC_SPEED_200KHZ:
//			b = b>>1;
//			break;
//		case IIC_SPEED_400KHZ:
//			b = b>>2;
//			break;
//		case IIC_SPEED_800KHZ:
//			b = b>>3;
//			break;
//	}

//	for(a=0;a<b;a++);

//}

//static void IIC_Stop(void);

//static	mutex_obj *mutex_lock=NULL;

////初始化IIC
//static BOOL IIC_Init(void)
//{
//	
//	if(IIC_PortInit())
//	{
//		mutex_lock =SYS_mutex_create(NULL);


//		//给一个停止信号, 复位I2C总线上的所有设备到待机模式
//		IIC_Stop();
//		return TRUE;
//	}
//	return FALSE;
//}

//static BOOL IIC_Open(int iic_speed)
//{
//	SYS_mutex_lock(mutex_lock,5000);
//	speed =iic_speed;
//	return TRUE;
//}

//static void IIC_Close(void)
//{
//	SYS_mutex_unlock(mutex_lock);
//}

///*=========================================================================================*/

////产生IIC起始信号
//static void IIC_Start(void)
//{//START:when CLK is high,DATA change form high to low

//	SDA_OUT();	//sda线输出
//	IIC_SDA(1);
//	IIC_SCL(1);
//	iic_delay();
//	iic_delay();
// 	IIC_SDA(0);
//	iic_delay();
//	iic_delay();
//	IIC_SCL(0);//钳住I2C总线，准备发送或接收数据 
//	iic_delay();
//	iic_delay();
//	iic_delay();
//	iic_delay();
//}	  

////产生IIC停止信号
//static void IIC_Stop(void)
//{//STOP:when CLK is high DATA change form low to high

//	SDA_OUT();//sda线输出
//	IIC_SCL(0);
//	IIC_SDA(0);
// 	iic_delay();
// 	iic_delay();
//	IIC_SCL(1); 
//	iic_delay();
//	iic_delay();
//	IIC_SDA(1);//发送I2C总线结束信号
//	iic_delay();
//	iic_delay();
//}


////等待应答信号到来
//static BOOL IIC_Wait_Ack(void)
//{
//	u16 timeout=0;

//	SDA_IN();      //SDA设置为输入  
//	IIC_SDA(1);
//	iic_delay();
//	IIC_SCL(1);    //CPU驱动SCL = 1, 此时器件会返回ACK应答
//	iic_delay();
//	while(READ_SDA)
//	{
//		if(timeout++ > 1000)
//		{
//			return FALSE;
//		}
//	}
//	IIC_SCL(0);//时钟输出0
//	iic_delay();
//	return TRUE;
//} 

////产生ACK应答
//static void IIC_Ack(void)
//{
//	SDA_OUT();
//	IIC_SDA(0);   //CPU驱动SDA = 0
//	iic_delay();
//	IIC_SCL(1);   //CPU产生1个时钟
//	iic_delay();
//	IIC_SCL(0);
//	iic_delay();

//	IIC_SDA(1);   //CPU释放SDA总线
//}

////不产生ACK应答		    
//static void IIC_NAck(void)
//{
//	SDA_OUT();
//	IIC_SDA(1);   //CPU驱动SDA = 1
//	iic_delay();
//	IIC_SCL(1);   //CPU产生1个时钟
//	iic_delay();
//	IIC_SCL(0);
//	iic_delay();

//}

////IIC发送一个字节
////返回从机有无应答
//static BOOL IIC_Send_Byte(u8 txd,u8 ack)
//{                        
//	int i;

//	SDA_OUT(); 	    
//    for(i=0;i<8;i++)
//    {
//        IIC_SCL(0);//拉低时钟开始数据传输
//        iic_delay();

//    	if(txd&0x80)
//    	{
//    		IIC_SDA(1);
//    	}
//    	else
//    	{
//    		IIC_SDA(0);
//    	}

//        txd <<= 1;
//		iic_delay();
//		IIC_SCL(1);
//		iic_delay();

//    }
//    IIC_SCL(0);
//    IIC_SDA(1); //free SDA
//    if(ack == IIC_NoACK)
//    {
//    	return TRUE;
//    }

//	if(IIC_Wait_Ack())
//	{
//		return TRUE;
//	}

//	return FALSE;
//} 	    

////读1个字节.
//static u8 IIC_Read_Byte(u8 ack)
//{
//	u8 i,dat=0;
//	SDA_IN();//SDA设置为输入
//    for(i=0;i<8;i++ )
//	{
//		IIC_SCL(1);
//		iic_delay();
//		dat<<=1;
//        if(READ_SDA)
//        {
//        	dat |= 0x01;
//        }
//        IIC_SCL(0);
//        iic_delay();
//    }

//    if(ack==IIC_ACK)
//    {
//    	IIC_Ack(); //发送ACK
//    }
//    else
//    {
//    	IIC_NAck();//发送nACK
//    }
//    return dat;
//}

///*=========================================================================================*/

//#endif /* IIC_MASTER */


