
#include "BSP.h"

//#include "./RES_MGR/RES_MGR.h"
#include "x_libc.h"
/*=========================================================================================*/

#define RES_BASE_OFFSET 0x00200000

/* 目录信息类型 */
typedef struct 
{
	char 	name[40];  /* 资源的名字 */
	u32  	size;      /* 资源的大小 */ 
	u32 	offset;    /* 资源相对于基地址的偏移 */
}CatalogTypeDef;

s32 GetResOffset(u32 res_base,const char *res_name);

/*=========================================================================================*/


/*=========================================================================================*/
void RES_DevTest(void);
static GUI_MUTEX *mutex_lock=NULL;

#define SYS_mutex_create GUI_MutexCreate
#define SYS_mutex_lock GUI_MutexLock
#define SYS_mutex_unlock GUI_MutexUnlock

void RES_DevInit(void)
{
	mutex_lock=SYS_mutex_create();

  
	SPI_FLASH_Init();

	//RES_DevTest();
}

U32 RES_DevGetID(void)
{
	U32 id;
	SYS_mutex_lock(mutex_lock,5000);

	id =SPI_FLASH_ReadID();
	SYS_mutex_unlock(mutex_lock);
	return id;
}

BOOL RES_DevWrite(u8 *buf,u32 addr,u32 size)
{
	addr += RES_BASE_OFFSET;
	SYS_mutex_lock(mutex_lock,5000);
	SPI_FLASH_SectorErase(addr&0xFFFFF000);
	SPI_FLASH_BufferWrite(buf,addr,size);
	SYS_mutex_unlock(mutex_lock);
	return TRUE;
}

BOOL RES_DevRead(u8 *buf,u32 addr,u32 size)
{
	addr += RES_BASE_OFFSET;
	SYS_mutex_lock(mutex_lock,5000);

	SPI_FLASH_BufferRead(buf,addr,size);
	SYS_mutex_unlock(mutex_lock);
	return TRUE;
}

int RES_DevEraseSector(u32 addr)
{
	u32 sector;
/*
	sector =addr;
	SYS_mutex_lock(mutex_lock,5000);

	SPI_FLASH_SectorErase(sector);
	SYS_mutex_unlock(mutex_lock);*/
	return 4096;
}

/*=========================================================================================*/

#if 1
s32 RES_Read(u8 *buf,u32 addr,int size)
{

	RES_DevRead(buf,addr,size);
	return size;
}
#endif

#if 1
s32 RES_GetOffset(const char *res_name)
{
	int i,len;
	CatalogTypeDef dir;

	len =x_strlen(res_name);
	for(i=0;i<4096;i+=32)
	{
		RES_Read((u8*)&dir,i,32);

		if(x_strncasecmp(dir.name,res_name,len)==0)
		{
			return dir.offset;
		}
	}

	return -1;

}
#endif

/*=========================================================================================*/

void RES_DevTest(void)
{
	int i;
	char *buf;
	volatile u32 id;

	buf =vmalloc(4096);
	i=0;
	SPI_FLASH_Init();;
	id =SPI_FLASH_ReadID();
	while(1)
	{

#if 0
		RES_DevEraseSector(i);

		memset(buf,i>>12,4096);
		RES_DevWrite(buf,i,4096);
#endif
		memset(buf,0,4096);
		RES_DevRead(buf,i,4096);

		i += 4096;
		GUI_msleep(100);

	}
	vfree(buf);
}

/*=========================================================================================*/









