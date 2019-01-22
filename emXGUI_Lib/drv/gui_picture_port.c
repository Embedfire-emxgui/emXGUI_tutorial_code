/**
  *********************************************************************
  * @file    gui_picture_port.c
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   图片显示接口
  *********************************************************************
  * @attention
  * 官网    :www.emXGUI.com
  *
  **********************************************************************
  */ 

#include	"emXGUI.h"
#include  "GUI_Drv_Cfg.h"
#include  "gui_resource_port.h"
#include  "gui_picture_port.h"

/*===================================================================================*/
/**
  * @brief  从流媒体加载内容的回调函数
  * @param  buf[out] 存储读取到的数据缓冲区
  * @param  offset 要读取的位置
  * @param  size 要读取的数据大小
  * @param  lParam 调用函数时的自定义参数（用户参数）
  * @retval 读取到的数据大小
  */
static int bmp_read_data_exFlash(void *buf,int offset,int size,LPARAM lParam)
{
	offset += lParam;
	RES_DevRead(buf,offset,size);
	return size;
}

 /**
  * @brief  显示文件系统中的BMP图片
  * @param  hdc（输入）：绘图上下文
  * @param  x，y（输入）: 绘制到目标的坐标
  * @param 	lprc（输入）:要绘制的BMP图像矩形区域，如果设置该参数为NULL，则绘制整个BMP图像区域。
  * @retval FALSE:失败; TRUE:成功
  */
BOOL _ShowBMPEx_rawFlash(HDC hdc, int x, int y, const RECT *lprc, char *file_name) 
{	 
    int offset;
    GUI_GET_DATA  get_data;
  
    offset =RES_GetOffset(file_name);
    if(offset > 0)
    {    
      get_data.lParam = offset;
      get_data.pfReadData = bmp_read_data_exFlash;

      return BMP_DrawEx(hdc,x,y,&get_data,lprc);
    }
    
    return FALSE;
}




/********************************END OF FILE****************************/
