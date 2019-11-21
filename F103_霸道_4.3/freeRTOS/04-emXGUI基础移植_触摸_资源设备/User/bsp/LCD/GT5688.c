/**
  ******************************************************************************
  * @file    gt5xx.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   i2c电容屏驱动函数gt9157芯片
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火  STM32 F407 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "BSP.h"
#include "gt5xx.h"


#define	IIC_SPEED	IIC_SPEED_400KHZ

static	const struct i2c_ops *pIIC =&I2C_GPD7_GPD3;

#define	GT_CMD_WR 	(0x28)
#define GT_CMD_RD 	(0x29)

#define	GTP_ADDRESS	GT_CMD_WR

#define CTP_RST_GPIO 		GPIOD
#define CTP_RST_GPIO_PIN 	GPIO_Pin_6

#define CTP_INT_GPIO 		GPIOG
#define CTP_INT_GPIO_PIN 	GPIO_Pin_8

#define	LCD_X_LENGTH	LCD_XSIZE
#define	LCD_Y_LENGTH	LCD_YSIZE

static void GTP_PortInit(void)
{
	GPIO_InitTypeDef gpio_init;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); //打开GPIO时钟

	gpio_init.GPIO_Mode  = GPIO_Mode_OUT;
	gpio_init.GPIO_OType = GPIO_OType_PP; 	//PP模式比OD模式有更高的速度,更强的驱动能力和抗干扰能力...
	gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;	//上拉电阻使能
	gpio_init.GPIO_Speed = GPIO_Speed_25MHz;
	gpio_init.GPIO_Pin = CTP_RST_GPIO_PIN ;
	GPIO_Init(CTP_RST_GPIO, &gpio_init);

	//GTP_IRQEnable();
	if(1)
	{
		gpio_init.GPIO_Mode  = GPIO_Mode_OUT;
		gpio_init.GPIO_Pin = CTP_INT_GPIO_PIN ;
		GPIO_Init(CTP_INT_GPIO, &gpio_init);

		////设置GT9xx地址为 0x28/0x29
		GPIO_Pin_Set(CTP_RST_GPIO,CTP_RST_GPIO_PIN,0); //RST=0;
		SYS_msleep(50);
		GPIO_Pin_Set(CTP_INT_GPIO,CTP_INT_GPIO_PIN,0); //INT=0;
		SYS_msleep(50);
		GPIO_Pin_Set(CTP_INT_GPIO,CTP_INT_GPIO_PIN,1); //INT=1;
		SYS_msleep(50);
		GPIO_Pin_Set(CTP_RST_GPIO,CTP_RST_GPIO_PIN,1); //RST=1;

		////
		SYS_msleep(50);
	}

	gpio_init.GPIO_Mode  = GPIO_Mode_IN;
	gpio_init.GPIO_Pin = CTP_INT_GPIO_PIN ;
	GPIO_Init(CTP_INT_GPIO, &gpio_init);

}

// 4.5寸屏GT5688驱动配置
static const u8 CTP_CFG_GT5688[] =  {
			0x96,0xE0,0x01,0x56,0x03,0x05,0x35,0x00,0x01,0x00,
			0x00,0x05,0x50,0x3C,0x53,0x11,0x00,0x00,0x22,0x22,
			0x14,0x18,0x1A,0x1D,0x0A,0x04,0x00,0x00,0x00,0x00,
			0x00,0x00,0x53,0x00,0x14,0x00,0x00,0x84,0x00,0x00,
			0x3C,0x19,0x19,0x64,0x1E,0x28,0x88,0x29,0x0A,0x2D,
			0x2F,0x29,0x0C,0x20,0x33,0x60,0x13,0x02,0x24,0x00,
			0x00,0x20,0x3C,0xC0,0x14,0x02,0x00,0x00,0x54,0xAC,
			0x24,0x9C,0x29,0x8C,0x2D,0x80,0x32,0x77,0x37,0x6E,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x50,0x3C,
			0xFF,0xFF,0x07,0x00,0x00,0x00,0x02,0x14,0x14,0x03,
			0x04,0x00,0x21,0x64,0x0A,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x32,0x20,0x50,0x3C,0x3C,0x00,0x00,0x00,0x00,0x00,
			0x0D,0x06,0x0C,0x05,0x0B,0x04,0x0A,0x03,0x09,0x02,
			0xFF,0xFF,0xFF,0xFF,0x00,0x01,0x02,0x03,0x04,0x05,
			0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
			0x10,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x3C,0x00,0x05,0x1E,0x00,0x02,
			0x2A,0x1E,0x19,0x14,0x02,0x00,0x03,0x0A,0x05,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xFF,0xFF,0x86,
			0x22,0x03,0x00,0x00,0x33,0x00,0x0F,0x00,0x00,0x00,
			0x50,0x3C,0x50,0x00,0x00,0x00,0x1A,0x64,0x01

};


//u8 config[GTP_CONFIG_MAX_LENGTH + GTP_ADDR_LENGTH]
//                = {GTP_REG_CONFIG_DATA >> 8, GTP_REG_CONFIG_DATA & 0xff};

static TOUCH_IC touchIC;

static s8 GTP_I2C_Test(void);

static void Delay(__IO int nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}


/**
  * @brief   从IIC设备中读取数据
  * @param
  *		@arg client_addr:设备地址
  *		@arg  buf[0~1]: 读取数据寄存器的起始地址
  *		@arg buf[2~len-1]: 存储读出来数据的缓冲buffer
  *		@arg len:    GTP_ADDR_LENGTH + read bytes count（寄存器地址长度+读取的数据字节数）
  * @retval  i2c_msgs传输结构体的个数，2为成功，其它为失败
  */
static s32 GTP_I2C_Read(u8 client_addr, u8 *buf, s32 len)
{
	int i;
	pIIC->Open(IIC_SPEED);

	pIIC->Start();
	if(!pIIC->WriteByte(GT_CMD_WR,IIC_ACK))
	{
	    pIIC->Stop();
	    pIIC->Close();
	    return FALSE;
	}
	pIIC->WriteByte(buf[0],IIC_ACK);
	pIIC->WriteByte(buf[1],IIC_ACK);

	pIIC->Start();
	pIIC->WriteByte(GT_CMD_RD,IIC_ACK);
	for (i = 0; i < len - 1; i++)
	{
		   buf[2+i] = pIIC->ReadByte(IIC_ACK);
	}

	// 最后一个数据
	buf[2+i] =pIIC->ReadByte(IIC_NoACK);

	pIIC->Stop();
	pIIC->Close();
	return TRUE;

}



/**
  * @brief   向IIC设备写入数据
  * @param
  *		@arg client_addr:设备地址
  *		@arg  buf[0~1]: 要写入的数据寄存器的起始地址
  *		@arg buf[2~len-1]: 要写入的数据
  *		@arg len:    GTP_ADDR_LENGTH + write bytes count（寄存器地址长度+写入的数据字节数）
  * @retval  i2c_msgs传输结构体的个数，1为成功，其它为失败
  */
static BOOL GTP_I2C_Write(u8 client_addr,u8 *buf,int len)
{
	int i;

	pIIC->Open(IIC_SPEED);

	pIIC->Start();
    if(!pIIC->WriteByte(GT_CMD_WR,IIC_ACK))
    {
    	pIIC->Stop();

    	pIIC->Close();
    	return FALSE;
    }
    pIIC->WriteByte(buf[0],IIC_ACK);
	pIIC->WriteByte(buf[1],IIC_ACK);

	for (i = 0; i < len; i++)
	{
		pIIC->WriteByte(buf[2+i],IIC_ACK);
	}

	pIIC->Stop();

	pIIC->Close();
	return TRUE;
}


/**
  * @brief   使用IIC读取再次数据，检验是否正常
  * @param
  *		@arg client:设备地址
  *		@arg  addr: 寄存器地址
  *		@arg rxbuf: 存储读出的数据
  *		@arg len:    读取的字节数
  * @retval
  * 	@arg FAIL
  * 	@arg SUCCESS
  */
s32 GTP_I2C_Read_dbl_check(u8 client_addr, u16 addr, u8 *rxbuf, int len)
{
    u8 buf[16] = {0};
    u8 confirm_buf[16] = {0};
    u8 retry = 0;
    
    GTP_DEBUG_FUNC();

    while (retry++ < 3)
    {
        memset(buf, 0xAA, 16);
        buf[0] = (u8)(addr >> 8);
        buf[1] = (u8)(addr & 0xFF);
        GTP_I2C_Read(client_addr, buf, len + 2);
        
        memset(confirm_buf, 0xAB, 16);
        confirm_buf[0] = (u8)(addr >> 8);
        confirm_buf[1] = (u8)(addr & 0xFF);
        GTP_I2C_Read(client_addr, confirm_buf, len + 2);

      
        if (!memcmp(buf, confirm_buf, len+2))
        {
            memcpy(rxbuf, confirm_buf+2, len);
            return SUCCESS;
        }
    }    
    GTP_ERROR("I2C read 0x%04X, %d bytes, double check failed!", addr, len);
    return FAIL;
}


/**
  * @brief   关闭GT91xx中断
  * @param 无
  * @retval 无
  */
void GTP_IRQ_Disable(void)
{

    GTP_DEBUG_FUNC();

    I2C_GTP_IRQDisable();
}

/**
  * @brief   使能GT91xx中断
  * @param 无
  * @retval 无
  */
void GTP_IRQ_Enable(void)
{
    GTP_DEBUG_FUNC();
     
	 I2C_GTP_IRQEnable();
}

#if 0

/**
  * @brief   用于处理或报告触屏检测到按下
  * @param
  *    @arg     id: 触摸顺序trackID
  *    @arg     x:  触摸的 x 坐标
  *    @arg     y:  触摸的 y 坐标
  *    @arg     w:  触摸的 大小
  * @retval 无
  */
/*用于记录连续触摸时(长按)的上一次触摸位置，负数值表示上一次无触摸按下*/
static s16 pre_x[GTP_MAX_TOUCH] ={-1,-1,-1,-1,-1};
static s16 pre_y[GTP_MAX_TOUCH] ={-1,-1,-1,-1,-1};

static void GTP_Touch_Down(s32 id,s32 x,s32 y,s32 w)
{
  
	GTP_DEBUG_FUNC();

	/*取x、y初始值大于屏幕像素值*/
    GTP_DEBUG("ID:%d, X:%d, Y:%d, W:%d", id, x, y, w);

		/************************************/
		/*在此处添加自己的触摸点按下时处理过程即可*/
		/* (x,y) 即为最新的触摸点 *************/
		/************************************/
	
		/*prex,prey数组存储上一次触摸的位置，id为轨迹编号(多点触控时有多轨迹)*/
    pre_x[id] = x; pre_y[id] =y;
	
}


/**
  * @brief   用于处理或报告触屏释放
  * @param 释放点的id号
  * @retval 无
  */
static void GTP_Touch_Up( s32 id)
{
		/*****************************************/
		/*在此处添加自己的触摸点释放时的处理过程即可*/
		/* pre_x[id],pre_y[id] 即为最新的释放点 ****/
		/*******************************************/	
		/***id为轨迹编号(多点触控时有多轨迹)********/
	
	
    /*触笔释放，把pre xy 重置为负*/
	  pre_x[id] = -1;
	  pre_y[id] = -1;		
  
    GTP_DEBUG("Touch id[%2d] release!", id);

}


/**
  * @brief   触屏处理函数，轮询或者在触摸中断调用
  * @param 无
  * @retval 无
  */
static void Goodix_TS_Work_Func(void)
{
    u8  end_cmd[3] = {GTP_READ_COOR_ADDR >> 8, GTP_READ_COOR_ADDR & 0xFF, 0};
    u8  point_data[2 + 1 + 8 * GTP_MAX_TOUCH + 1]={GTP_READ_COOR_ADDR >> 8, GTP_READ_COOR_ADDR & 0xFF};
    u8  touch_num = 0;
    u8  finger = 0;
    static u16 pre_touch = 0;
    static u8 pre_id[GTP_MAX_TOUCH] = {0};

    u8 client_addr;//=GTP_ADDRESS;
    u8* coor_data = NULL;
    s32 input_x = 0;
    s32 input_y = 0;
    s32 input_w = 0;
    u8 id = 0;
 
    s32 i  = 0;
    s32 ret = -1;

    GTP_DEBUG_FUNC();

    ret = GTP_I2C_Read(client_addr, point_data, 12);//10字节寄存器加2字节地址
    if (ret < 0)
    {
        GTP_ERROR("I2C transfer error. errno:%d\n ", ret);

        return;
    }
    
    finger = point_data[GTP_ADDR_LENGTH];//状态寄存器数据

    if (finger == 0x00)		//没有数据，退出
    {
        return;
    }

    if((finger & 0x80) == 0)//判断buffer status位
    {
        goto exit_work_func;//坐标未就绪，数据无效
    }

    touch_num = finger & 0x0f;//坐标点数
    if (touch_num > GTP_MAX_TOUCH)
    {
        goto exit_work_func;//大于最大支持点数，错误退出
    }

    if (touch_num > 1)//不止一个点
    {
    	//使用操作系统后，在中断调用本函数，此变量不加static会死机
		static u8 buf[8 * GTP_MAX_TOUCH] = {(GTP_READ_COOR_ADDR + 10) >> 8, (GTP_READ_COOR_ADDR + 10) & 0xff};

        ret = GTP_I2C_Read(client_addr, buf, 2 + 8 * (touch_num - 1));
        memcpy(&point_data[12], &buf[2], 8 * (touch_num - 1));			//复制其余点数的数据到point_data
    }

    
    
    if (pre_touch>touch_num)				//pre_touch>touch_num,表示有的点释放了
    {
        for (i = 0; i < pre_touch; i++)						//一个点一个点处理
         {
            u8 j;
           for(j=0; j<touch_num; j++)
           {
               coor_data = &point_data[j * 8 + 3];
               id = coor_data[0] & 0x0F;									//track id
              if(pre_id[i] == id)
                break;

              if(j >= touch_num-1)											//遍历当前所有id都找不到pre_id[i]，表示已释放
              {
                 GTP_Touch_Up( pre_id[i]);
              }
           }
       }
    }


    if (touch_num)
    {
        for (i = 0; i < touch_num; i++)						//一个点一个点处理
        {
            coor_data = &point_data[i * 8 + 3];

            id = coor_data[0] & 0x0F;									//track id
            pre_id[i] = id;

            input_x  = coor_data[1] | (coor_data[2] << 8);	//x坐标
            input_y  = coor_data[3] | (coor_data[4] << 8);	//y坐标
            input_w  = coor_data[5] | (coor_data[6] << 8);	//size
#if 0
            {
							
									/*根据扫描模式更正X/Y起始方向*/
								switch(LCD_SCAN_MODE)
								{
									case 0:case 7:
										input_y  = LCD_Y_LENGTH - input_y;
										break;
									
									case 2:case 3: 
										input_x  = LCD_X_LENGTH - input_x;
										input_y  = LCD_Y_LENGTH - input_y;
										break;
									
									case 1:case 6:
										input_x  = LCD_X_LENGTH - input_x;
										break;	
									
									default:
									break;
								}
								
                GTP_Touch_Down( id, input_x, input_y, input_w);//数据处理
            }
#endif
        }
    }
    else if (pre_touch)		//touch_ num=0 且pre_touch！=0
    {
      for(i=0;i<pre_touch;i++)
      {
          GTP_Touch_Up(pre_id[i]);
      }
    }


    pre_touch = touch_num;


exit_work_func:
    {
        ret = GTP_I2C_Write(client_addr, end_cmd, 3);
        if (ret < 0)
        {
            GTP_INFO("I2C write end_cmd error!");
        }
    }

}
#endif


/**
  * @brief   给触屏芯片重新复位
  * @param 无
  * @retval 无
  */
 s8 GTP_Reset_Guitar(void)
{
    GTP_DEBUG_FUNC();
#if 1
    I2C_ResetChip();
    return 0;
#else 		//软件复位
    s8 ret = -1;
    s8 retry = 0;
    u8 reset_command[3]={(u8)GTP_REG_COMMAND>>8,(u8)GTP_REG_COMMAND&0xFF,2};

    //写入复位命令
    while(retry++ < 5)
    {
        ret = GTP_I2C_Write(GTP_ADDRESS, reset_command, 3);
        if (ret > 0)
        {
            GTP_INFO("GTP enter sleep!");

            return ret;
        }

    }
    GTP_ERROR("GTP send sleep cmd failed.");
    return ret;
#endif

}



 /**
   * @brief   进入睡眠模式
   * @param 无
   * @retval 1为成功，其它为失败
   */
//s8 GTP_Enter_Sleep(void)
//{
//    s8 ret = -1;
//    s8 retry = 0;
//    u8 reset_comment[3] = {(u8)(GTP_REG_COMMENT >> 8), (u8)GTP_REG_COMMENT&0xFF, 5};//5
//
//    GTP_DEBUG_FUNC();
//
//    while(retry++ < 5)
//    {
//        ret = GTP_I2C_Write(GTP_ADDRESS, reset_comment, 3);
//        if (ret > 0)
//        {
//            GTP_INFO("GTP enter sleep!");
//
//            return ret;
//        }
//
//    }
//    GTP_ERROR("GTP send sleep cmd failed.");
//    return ret;
//}


s8 GTP_Send_Command(u8 command)
{
    s8 ret = -1;
    s8 retry = 0;
    u8 command_buf[3] = {(u8)(GTP_REG_COMMAND >> 8), (u8)GTP_REG_COMMAND&0xFF, GTP_COMMAND_READSTATUS};

    GTP_DEBUG_FUNC();

    while(retry++ < 5)
    {
        ret = GTP_I2C_Write(GTP_ADDRESS, command_buf, 3);
        if (ret > 0)
        {
            GTP_INFO("send command success!");

            return ret;
        }

    }
    GTP_ERROR("send command fail!");
    return ret;
}

/**
  * @brief   唤醒触摸屏
  * @param 无
  * @retval 0为成功，其它为失败
  */
s8 GTP_WakeUp_Sleep(void)
{
    u8 retry = 0;
    s8 ret = -1;

    GTP_DEBUG_FUNC();

    while(retry++ < 10)
    {
        ret = GTP_I2C_Test();
        if (ret > 0)
        {
            GTP_INFO("GTP wakeup sleep.");
            return ret;
        }
        GTP_Reset_Guitar();
    }

    GTP_ERROR("GTP wakeup sleep failed.");
    return ret;
}

static s32 GTP_Get_Info(void)
{
    u8 opr_buf[10] = {0};
    s32 ret = 0;

    u16 abs_x_max = GTP_MAX_WIDTH;
    u16 abs_y_max = GTP_MAX_HEIGHT;
    u8 int_trigger_type = GTP_INT_TRIGGER;
        
    opr_buf[0] = (u8)((GTP_REG_CONFIG_DATA+1) >> 8);
    opr_buf[1] = (u8)((GTP_REG_CONFIG_DATA+1) & 0xFF);
    
    ret = GTP_I2C_Read(GTP_ADDRESS, opr_buf, 10);
    if (ret < 0)
    {
        return FAIL;
    }
    
    abs_x_max = (opr_buf[3] << 8) + opr_buf[2];
    abs_y_max = (opr_buf[5] << 8) + opr_buf[4];
		GTP_DEBUG("RES");   
		GTP_DEBUG_ARRAY(&opr_buf[0],10);

    opr_buf[0] = (u8)((GTP_REG_CONFIG_DATA+6) >> 8);
    opr_buf[1] = (u8)((GTP_REG_CONFIG_DATA+6) & 0xFF);
    ret = GTP_I2C_Read(GTP_ADDRESS, opr_buf, 3);
    if (ret < 0)
    {
        return FAIL;
    }
    int_trigger_type = opr_buf[2] & 0x03;
    
    GTP_INFO("X_MAX = %d, Y_MAX = %d, TRIGGER = 0x%02x",
            abs_x_max,abs_y_max,int_trigger_type);
    
    return SUCCESS;    
}

/*******************************************************
Function:
    Initialize gtp.
Input:
    ts: goodix private data
Output:
    Executive outcomes.
        0: succeed, otherwise: failed
*******************************************************/
static s32 GTP_Init_Panel(void)
{
    s32 ret = -1;

    s32 i = 0;
    u16 check_sum = 0;
    s32 retry = 0;

    const u8* cfg_info;
    u8 cfg_info_len  ;
	u8* config;

    u8 cfg_num =0 ;		//需要配置的寄存器个数

    GTP_DEBUG_FUNC();
	
//u8 config[GTP_CONFIG_MAX_LENGTH + GTP_ADDR_LENGTH]
//                = {GTP_REG_CONFIG_DATA >> 8, GTP_REG_CONFIG_DATA & 0xff};

	config = (u8 *)vmalloc (GTP_ADDR_LENGTH + GTP_CONFIG_MAX_LENGTH);
	config[0] = GTP_REG_CONFIG_DATA >> 8;
	config[1] = GTP_REG_CONFIG_DATA & 0xff;
	
    //I2C_Touch_Init();

    ret = GTP_I2C_Test();
    if (ret < 0)
    {
        GTP_ERROR("I2C communication ERROR!");
		return ret;
    } 
		
		//获取触摸IC的型号
    GTP_Read_Version(); 
		
	//根据IC的型号指向不同的配置
    if(touchIC == GT5688)
	{
		cfg_info =  CTP_CFG_GT5688; //指向寄存器配置
		cfg_info_len = CFG_GROUP_LEN(CTP_CFG_GT5688);//计算配置表的大小
	}
		
    memset(&config[GTP_ADDR_LENGTH], 0, GTP_CONFIG_MAX_LENGTH);
    memcpy(&config[GTP_ADDR_LENGTH], cfg_info, cfg_info_len);
		

	cfg_num = cfg_info_len;
		
	GTP_DEBUG("cfg_info_len = %d ",cfg_info_len);
	GTP_DEBUG("cfg_num = %d ",cfg_num);
	GTP_DEBUG_ARRAY(config,6);
		
	/*根据LCD的扫描方向设置分辨率*/
	config[GTP_ADDR_LENGTH+1] = LCD_X_LENGTH & 0xFF;
	config[GTP_ADDR_LENGTH+2] = LCD_X_LENGTH >> 8;
	config[GTP_ADDR_LENGTH+3] = LCD_Y_LENGTH & 0xFF;
	config[GTP_ADDR_LENGTH+4] = LCD_Y_LENGTH >> 8;

	config[GTP_ADDR_LENGTH+6] &= ~(X2Y_LOC);
#if 0
		/*根据扫描模式设置X2Y交换*/
		switch(LCD_SCAN_MODE)
		{
			case 0:case 2:case 4: case 6:
				config[GTP_ADDR_LENGTH+6] &= ~(X2Y_LOC);
				break;
			
			case 1:case 3:case 5: case 7:
				config[GTP_ADDR_LENGTH+6] |= (X2Y_LOC);
				break;		
		}
#endif

    //计算要写入checksum寄存器的值
    check_sum = 0;
	for (i = GTP_ADDR_LENGTH; i < (cfg_num+GTP_ADDR_LENGTH -3); i += 2)
	{
		check_sum += (config[i] << 8) + config[i + 1];
	}
		
	check_sum = 0 - check_sum;
	GTP_DEBUG("Config checksum: 0x%04X", check_sum);
	//更新checksum
	config[(cfg_num+GTP_ADDR_LENGTH -3)] = (check_sum >> 8) & 0xFF;
	config[(cfg_num+GTP_ADDR_LENGTH -2)] = check_sum & 0xFF;
	config[(cfg_num+GTP_ADDR_LENGTH -1)] = 0x01;
		

    //写入配置信息
    for (retry = 0; retry < 5; retry++)
    {
        ret = GTP_I2C_Write(GTP_ADDRESS, config , cfg_num + GTP_ADDR_LENGTH+2);
        if (ret > 0)
        {
            break;
        }
    }
    SYS_msleep(50);				//延迟等待芯片更新
		
		
#if 0	//读出写入的数据，检查是否正常写入
    //检验读出的数据与写入的是否相同
	{
    	    u16 i;
    	    u8 buf[300];
    	     buf[0] = config[0];
    	     buf[1] =config[1];    //寄存器地址

    	    GTP_DEBUG_FUNC();

    	    ret = GTP_I2C_Read(GTP_ADDRESS, buf, sizeof(buf));
			   
					GTP_DEBUG("read ");

					GTP_DEBUG_ARRAY(buf,cfg_num);
		
			    GTP_DEBUG("write ");

					GTP_DEBUG_ARRAY(config,cfg_num);

					//不对比版本号
    	    for(i=1;i<cfg_num+GTP_ADDR_LENGTH-3;i++)
    	    {

    	    	if(config[i] != buf[i])
    	    	{
    	    		GTP_ERROR("Config fail ! i = %d ",i);
							free(config);
    	    		return -1;
    	    	}
    	    }
    	    if(i==cfg_num+GTP_ADDR_LENGTH-3)
	    		GTP_DEBUG("Config success ! i = %d ",i);
	}
#endif
	

	 /*使能中断，这样才能检测触摸数据*/
	//I2C_GTP_IRQEnable();
    GTP_Get_Info();
		
	vfree(config);
    return 0;
}


/*******************************************************
Function:
    Read chip version.
Input:
    client:  i2c device
    version: buffer to keep ic firmware version
Output:
    read operation return.
        2: succeed, otherwise: failed
*******************************************************/
s32 GTP_Read_Version(void)
{
    s32 ret = -1;
    u8 buf[8] = {GTP_REG_VERSION >> 8, GTP_REG_VERSION & 0xff};    //寄存器地址

    GTP_DEBUG_FUNC();

    ret = GTP_I2C_Read(GTP_ADDRESS, buf, sizeof(buf));
    if (ret < 0)
    {
        GTP_ERROR("GTP read version failed");
        return ret;
    }
    if (buf[2] == '5')
    {
        GTP_INFO("IC1 Version: %c%c%c%c_%02x%02x", buf[2], buf[3], buf[4], buf[5], buf[7], buf[6]);
				
				//GT5688芯片
				if(buf[2] == '5' && buf[3] == '6' && buf[4] == '8'&& buf[5] == '8')
					touchIC = GT5688;
    }        
    else if (buf[5] == 0x00)
    {
        GTP_INFO("IC2 Version: %c%c%c_%02x%02x", buf[2], buf[3], buf[4], buf[7], buf[6]);
				
				//GT911芯片
				if(buf[2] == '9' && buf[3] == '1' && buf[4] == '1')
					touchIC = GT911;
    }
    else
    {
        GTP_INFO("IC3 Version: %c%c%c%c_%02x%02x", buf[2], buf[3], buf[4], buf[5], buf[7], buf[6]);
				
				//GT9157芯片
				if(buf[2] == '9' && buf[3] == '1' && buf[4] == '5' && buf[5] == '7')
					touchIC = GT9157;
		}
    return ret;
}

/*******************************************************
Function:
    I2c test Function.
Input:
    client:i2c client.
Output:
    Executive outcomes.
        2: succeed, otherwise failed.
*******************************************************/
static s8 GTP_I2C_Test( void)
{
    u8 test[3] = {GTP_REG_CONFIG_DATA >> 8, GTP_REG_CONFIG_DATA & 0xff};
    u8 retry = 0;
    s8 ret = -1;

    GTP_DEBUG_FUNC();
  
    while(retry++ < 5)
    {
        ret = GTP_I2C_Read(GTP_ADDRESS, test, 3);
        if (ret > 0)
        {
            return ret;
        }
        GTP_ERROR("GTP i2c test failed time %d.",retry);
    }
    return ret;
}

/*============================================================================*/

void GT5688_Init(void)
{
	GTP_PortInit();
	GTP_Init_Panel();
}

int GT5688_Execu(int *x,int *y)
{
	  u8  end_cmd[3] = {GTP_READ_COOR_ADDR >> 8, GTP_READ_COOR_ADDR & 0xFF, 0};
	  u8  point_data[2 + 1 + 8 * GTP_MAX_TOUCH + 1]={GTP_READ_COOR_ADDR >> 8, GTP_READ_COOR_ADDR & 0xFF};
	  u8  touch_num = 0;
	  u8  finger = 0;
	  static u16 pre_touch = 0;
	  static u8 pre_id[GTP_MAX_TOUCH] = {0};

	  u8 client_addr;//=GTP_ADDRESS;
	  u8* coor_data = NULL;
	  s32 input_x = 0;
	  s32 input_y = 0;
	  s32 input_w = 0;
	  u8 id = 0;

	  s32 i  = 0;
	  s32 ret = 0;

	    GTP_DEBUG_FUNC();

	    ret = GTP_I2C_Read(client_addr, point_data, 12);//10字节寄存器加2字节地址
	    if (ret < 0)
	    {
	        GTP_ERROR("I2C transfer error. errno:%d\n ", ret);
	        return touch_num;
	    }

	    finger = point_data[GTP_ADDR_LENGTH];//状态寄存器数据

	    if (finger == 0x00)		//没有数据，退出
	    {
	    	return touch_num;
	    }

	    if((finger & 0x80) == 0)//判断buffer status位
	    {
	        goto exit;//坐标未就绪，数据无效
	    }

	    touch_num = finger & 0x0f;//坐标点数
	    if (touch_num > GTP_MAX_TOUCH)
	    {
	        goto exit;//大于最大支持点数，错误退出
	    }

	    if (touch_num > 1)//不止一个点
	    {
	    	//使用操作系统后，在中断调用本函数，此变量不加static会死机
			static u8 buf[8 * GTP_MAX_TOUCH] = {(GTP_READ_COOR_ADDR + 10) >> 8, (GTP_READ_COOR_ADDR + 10) & 0xff};

	        ret = GTP_I2C_Read(client_addr, buf, 2 + 8 * (touch_num - 1));
	        memcpy(&point_data[12], &buf[2], 8 * (touch_num - 1));			//复制其余点数的数据到point_data
	    }

	    if (touch_num>0)
	    {
	        for (i = 0; i < touch_num; i++)						//一个点一个点处理
	        {
	            coor_data = &point_data[i * 8 + 3];

	            id = coor_data[0] & 0x0F;									//track id
	            pre_id[i] = id;

	            input_x  = coor_data[1] | (coor_data[2] << 8);	//x坐标
	            input_y  = coor_data[3] | (coor_data[4] << 8);	//y坐标
	            input_w  = coor_data[5] | (coor_data[6] << 8);	//size

	           *x = input_x;
	           *y = input_y;

	        }
	    }
	    pre_touch = touch_num;

exit:
	    ret = GTP_I2C_Write(client_addr, end_cmd, 3);
	    if (ret==FALSE)
	    {
	        GTP_INFO("I2C write end_cmd error!");
	    }
	    return touch_num;
}


void GT5688_Test(void)
{
	GTP_PortInit();
	GTP_Init_Panel();
	SYS_msleep(100);

	while(1)
	{
		volatile int x,y,n;
		n=GT5688_Execu(&x,&y);
		SYS_msleep(50);
	}

}


/*============================================================================*/

#include "GUI_Drv.h"

static BOOL ts_down=FALSE;
static int ts_x,ts_y;


static BOOL GTxx_Init(void)
{
	ts_down=FALSE;
	ts_x=0;
	ts_y=0;

	GT5688_Init();

	return TRUE;
}


static BOOL GetState(void)
{
	int x,y;

	if(GT5688_Execu(&x,&y) > 0)
	{
		x =480-x;

		//if((x<800) && (y<480))
		{
			ts_x =x;
			ts_y =y;
			ts_down =TRUE;

		}
		return TRUE;
	}
	else
	{
		ts_down =FALSE;
		return FALSE;
	}
}


static BOOL GetSample(POINT *pt)
{
	if(ts_down==TRUE)
	{
		pt->x =ts_x;
		pt->y =ts_y;

		return TRUE;
	}
	else
	{
		return FALSE;
	}
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

	return TRUE;
}

static BOOL SaveCfg(TS_CFG_DATA *cfg)
{
	return TRUE;
}

/*============================================================================*/

const GUI_TOUCH_DEV TouchDev_GT5688=
{
	.Init 		=GTxx_Init,
	.GetState 	=GetState,
	.GetSample	=GetSample,
	.GetPoint	=GetPoint,
	.LoadCfg	=LoadCfg,
	.SaveCfg	=SaveCfg,
};

/*============================================================================*/


