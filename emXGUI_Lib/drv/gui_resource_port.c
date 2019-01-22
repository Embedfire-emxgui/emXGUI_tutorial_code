/**
  *********************************************************************
  * @file    gui_resource_port.c
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   管理外部资源的接口
  *          例如用来管理外部FLASH中的资源
  *********************************************************************
  * @attention
  * 官网    :www.emXGUI.com
  *
  **********************************************************************
  */ 
  
#include <string.h>
#include "board.h" 
#include	"emXGUI.h"
#include	"emXGUI_Arch.h"
#include "x_libc.h" 
#include "gui_resource_port.h"
#include "gui_mem_port.h"



/*=========================================================================================*/
/*访问资源设备的互斥信号量*/
static GUI_MUTEX *mutex_lock=NULL;

/**
  * @brief  初始化资源设备（外部FLASH）
  * @param  无
  * @retval 是否初始化正常
  */
BOOL RES_DevInit(void)
{  
	mutex_lock=GUI_MutexCreate();

	if(SPI_FLASH_Init() == 0)
    return TRUE;
  else
    return FALSE;

//	RES_DevTest();
}

/**
  * @brief  读取设备ID
  * @param  无
  * @retval 设备ID
  */
U32 RES_DevGetID(void)
{
	U32 id;
	GUI_MutexLock(mutex_lock,5000);

	id =SPI_FLASH_ReadID();
	GUI_MutexUnlock(mutex_lock);
	return id;
}

/**
  * @brief  向设备写入内容
  * @param  buf 要写入的内容
  * @param  addr 写入的目标地址
  * @param  size 写入的数据量（size不应超过BLOCK大小）
  * @retval 是否写入正常
  */
BOOL RES_DevWrite(u8 *buf,u32 addr,u32 size)
{
	GUI_MutexLock(mutex_lock,5000);
	SPI_FLASH_SectorErase(addr&0xFFFFF000);
	SPI_FLASH_BufferWrite(buf,addr,size);
	GUI_MutexUnlock(mutex_lock);
	return TRUE;
}

/**
  * @brief  从设备中读取内容
  * @param  buf 存储读取到的内容
  * @param  addr 读取的目标地址
  * @param  size 读取的数据量
  * @retval 是否读取正常
  */
BOOL RES_DevRead(u8 *buf,u32 addr,u32 size)
{
	GUI_MutexLock(mutex_lock,5000);

	SPI_FLASH_BufferRead(buf,addr,size);
	GUI_MutexUnlock(mutex_lock);
	return TRUE;
}

/**
  * @brief  擦除扇区
  * @param  addr 要擦除的扇区地址
  * @retval 扇区的字节数
  */
int RES_DevEraseSector(u32 addr)
{
	GUI_MutexLock(mutex_lock,5000);
	SPI_FLASH_SectorErase(addr&0xFFFFF000);
	GUI_MutexUnlock(mutex_lock);
	return SPI_FLASH_SectorSize;
}

/*=========================================================================================*/
#if 0
/**
  * @brief  资源设备测试
  * @param  无
  * @retval 无
  */
void RES_DevTest(void)
{
	char *buf;
	volatile u32 id;

	buf =GUI_VMEM_Alloc(4096);
	RES_DevInit();
	id =RES_DevGetID();
  
//  GUI_Printf("0x%x",id);

#if 0  
	while(1)
	{	
    int i = 0;

		RES_DevEraseSector(i);

		memset(buf,i>>12,4096);
		RES_DevWrite(buf,i,4096);

		memset(buf,0,4096);
		RES_DevRead((u8 *)buf,i,4096);

		i += 4096;
		GUI_msleep(100);

	}
#endif  
	GUI_VMEM_Free(buf);
}
#endif



/**
  * @brief  从FLASH中的目录查找相应的资源位置
  * @param  res_base 目录在FLASH中的基地址
  * @param  res_name[in] 要查找的资源名字
  * @retval -1表示找不到，其余值表示资源在FLASH中的基地址
  */
s32 RES_GetOffset(const char *res_name)
{
	int i,len;
	CatalogTypeDef dir;

	len =x_strlen(res_name);
	for(i=0;i<GUI_CATALOG_SIZE;i+=32)
	{
		RES_DevRead((u8*)&dir,GUI_RES_BASE+i,32);

		if(x_strncasecmp(dir.name,res_name,len)==0)
		{
      /* dir.offset是相对基地址的偏移，此处返回绝对地址 */
			return dir.offset + GUI_RES_BASE;
		}
	}

	return -1;
}

/**
  * @brief  从FLASH中的目录查找相应资源的信息
  * @param  res_base 目录在FLASH中的基地址
  * @param  res_name[in] 要查找的资源名字
  * @param  dir[out] 要查找的资源名字
  * @note   此处dir.offset会被赋值为资源的绝对地址！！
  * @retval -1表示找不到，其余值表示资源在FLASH中的基地址
  */
s32 RES_GetInfo_AbsAddr(const char *res_name, CatalogTypeDef *dir)
{
	int i,len;
  
	len =x_strlen(res_name);
  /* 根据名字遍历目录 */
	for(i=0;i<GUI_CATALOG_SIZE;i+=32)
	{
		RES_DevRead((u8*)dir,GUI_RES_BASE+i,32);

		if(x_strncasecmp(dir->name,res_name,len)==0)
		{
      /* dir.offset是相对基地址的偏移，此处返回绝对地址 */
      dir->offset += GUI_RES_BASE;
			return dir->offset ;
		}
	}
	return -1;
}

/********************************END OF FILE****************************/

