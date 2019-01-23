/**
  *********************************************************************
  * @file    X_GUI_FreeRTOS.c
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   emXGUI的FreeRTOS操作系统接口
  *********************************************************************
  * @attention
  * 官网    :www.emXGUI.com
  *
  **********************************************************************
  */ 
/* 在工程选项中定义这个宏，以设置使用的操作系统 */  
#ifdef	X_GUI_USE_FREERTOS

#include	<stddef.h>
#include	"emXGUI_Arch.h"

#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

/*===================================================================================*/
/*
函数功能: 创建一个互斥(该互斥锁必须支持嵌套使用)
返回: 互斥对象句柄(唯一标识)
说明: 互斥对象句柄按实际OS所定,可以是指针,ID号等...
*/
GUI_MUTEX*	GUI_MutexCreate(void)
{
	return (GUI_MUTEX*)xSemaphoreCreateRecursiveMutex();	
}

/*===================================================================================*/
/*
函数功能: 互斥锁定
参数: hMutex(由GUI_MutexCreate返回的句柄); 
      time 最长等待毫秒数,0立既返回,0xFFFFFFFF,一直等待
返回: TRUE:成功;FALSE:失败或超时
说明: .
*/
BOOL	GUI_MutexLock(GUI_MUTEX *hMutex,U32 time)
{
	if(xSemaphoreTakeRecursive((SemaphoreHandle_t)hMutex,pdMS_TO_TICKS(time))==pdTRUE)
	{
		return TRUE;
	}
	return	FALSE;
}

/*===================================================================================*/
/*
函数功能: 互斥解锁
参数: hMutex(由GUI_MutexCreate返回的句柄);    
返回: 无
说明: .
*/
void	GUI_MutexUnlock(GUI_MUTEX *hMutex)
{
	 xSemaphoreGiveRecursive((SemaphoreHandle_t)hMutex);
}

/*===================================================================================*/
/*
函数功能: 互斥删除
参数: hMutex(由GUI_MutexCreate返回的句柄);    
返回: 无
说明: .
*/
void	GUI_MutexDelete(GUI_MUTEX *hMutex)
{
	vSemaphoreDelete((SemaphoreHandle_t)hMutex);
}

/*===================================================================================*/
/*
函数功能: 创建一个信号量
参数: init: 信号量初始值; max: 信号量最大值
返回: 信号量对象句柄(唯一标识)
说明: 信号量对象句柄按实际OS所定,可以是指针,ID号等...
*/
GUI_SEM*	GUI_SemCreate(int init,int max)
{
	return (GUI_SEM*)xSemaphoreCreateCounting(max,init);
}

/*===================================================================================*/
/*
函数功能: 信号量等待
参数: hsem(由GUI_SemCreate返回的句柄); 
      time 最长等待毫秒数,0立既返回,0xFFFFFFFF,一直等待
返回: TRUE:成功;FALSE:失败或超时
说明: .
*/
BOOL	GUI_SemWait(GUI_SEM *hsem,U32 time)
{

	if(xSemaphoreTake((SemaphoreHandle_t)hsem,pdMS_TO_TICKS(time))== pdTRUE)
	{
		return TRUE;
	}
	return FALSE;
}

/*===================================================================================*/
/*
函数功能: 信号量发送
参数: hsem(由GUI_SemCreate返回的句柄);  
返回: 无
说明: .
*/
void	GUI_SemPost(GUI_SEM *hsem)
{
	xSemaphoreGive((SemaphoreHandle_t)hsem);
}

/*===================================================================================*/
/*
函数功能: 信号量删除
参数: hsem(由GUI_SemCreate返回的句柄);    
返回: 无
说明: .
*/
void	GUI_SemDelete(GUI_SEM *hsem)
{
	vSemaphoreDelete((SemaphoreHandle_t)hsem);
}

/*===================================================================================*/
/*
函数功能: 获得当前线程句柄(唯一标识)
参数: 无  
返回: 当前线程唯一标识,按实际OS所定,可以是指针,ID号等...
说明: .
*/
HANDLE	GUI_GetCurThreadHandle(void)
{
	return	(HANDLE)xTaskGetCurrentTaskHandle();
}


/*===================================================================================*/
/*
函数功能: 获得当前系统时间(单位:毫秒)
参数: 无  
返回: 当前系统时间
说明: .
*/
U32	GUI_GetTickCount(void)
{
	U32 i;
	
	i=xTaskGetTickCount();
	
	return (i*1000)/configTICK_RATE_HZ;

}

/*===================================================================================*/
/*
函数功能: 最短时间内让出CPU
参数: 无  
返回: 无
说明: 按具体OS情况而定,最简单的方法是:OS Delay 一个 tick 周期.
*/
void	GUI_Yield(void)
{
	vTaskDelay(2);
}

/*===================================================================================*/
/*
函数功能: 延时函数
参数: ms: 延时时间(单位:毫秒) 
返回: 无
说明: 
*/
void	GUI_msleep(u32 ms)
{
	vTaskDelay(pdMS_TO_TICKS(ms));
}



#endif

/********************************END OF FILE****************************/

