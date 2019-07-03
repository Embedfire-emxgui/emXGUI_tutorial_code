/*
 * retarget.c
 *
 *  Created on: 2017Äê6ÔÂ12ÈÕ
 *      Author: liuwei
 */

#include <stdio.h>
#include <string.h>
#include "Include.h"

/*=========================================================================================*/

int _write(FILE *fp)
{
	return 1;
}

int _read(FILE *fp)
{
	return 1;
}

int _fstat(FILE *fp)
{
	return 0;
}

int _lseek(FILE *fp)
{
	return 0;
}

void _close(FILE *fp)
{

}

int _isatty(FILE *fp)
{
	return 1;
}

/*=========================================================================================*/

//int printf(const char *fmt,...)
//{
//#if 0
//	char buf[200];
//	x_va_list va;

//	x_va_start(va,fmt);
//	x_vsprintf(buf,fmt,va);
//	x_va_end(va);

//	//DebugPuts(buf);
//	return x_strlen(buf);
//#endif

//}


/*=========================================================================================*/

void* malloc(size_t size)
{
	void *p;
	p= vmalloc(size);

	return p;
}

void free(void *ptr)
{
	vfree(ptr);
}

/*=========================================================================================*/

void* calloc(size_t count,size_t eltsize)
{
	void *p;
	int size;

	size =count*eltsize;
	p =vmalloc(size);
	if(p!=NULL)
	{
		memset(p,0,size);
	}
	return p;
}

/*=========================================================================================*/

void* realloc(void *ptr,size_t newsize)
{
	void *p;

	p =vmalloc(newsize);
	if(p!=NULL)
	{
		memcpy(p,ptr,newsize);
		vfree(ptr);
	}
	return p;
}

/*=========================================================================================*/


/*=========================================================================================*/
static u8 sbrk_buf[256];

void* _sbrk(u32 size)
{
	volatile int i=0;
	while(1)
	{
		i++;
	}
	return (void*)sbrk_buf;
}

void _exit(void)
{

}

void _kill(void)
{

}

int _getpid(void)
{
	return 0;
}

/*=========================================================================================*/
