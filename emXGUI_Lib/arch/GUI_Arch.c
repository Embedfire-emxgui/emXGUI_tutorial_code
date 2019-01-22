
#include <string.h>
#include "gui_drv.h"

/*===================================================================================*/


/*===================================================================================*/

GL_OP GL_MEM_8PP;
GL_OP GL_MEM_16PP;
GL_OP GL_MEM_32PP;

/*===================================================================================*/

void* GUI_memset(void * s, int c, int n)
{
	return memset(s,c,n);
}

void* GUI_memcpy(void *s1, const void *s2, int n)
{
	return	memcpy(s1,s2,n);
}


/*=========================================================================================*/

void	GUI_memset8(U8 *dst,U8 dat,int count)
{
	memset(dst,dat,count);
}

void	GUI_memset8_step(U8 *dst,U8 dat,int count,int step)
{
	switch(count&0x7)
	{
		case 7: count &= ~0x07; goto out7;
		case 6: count &= ~0x07; goto out6;
		case 5: count &= ~0x07; goto out5;
		case 4: count &= ~0x07; goto out4;
		case 3: count &= ~0x07; goto out3;
		case 2: count &= ~0x07; goto out2;
		case 1: count &= ~0x07; goto out1;
		default: break ;
	}

	while(count > 0)
	{
		count -= 8;

//		out8: 
      *dst =dat; dst+= step;
		out7: *dst =dat; dst+= step;
		out6: *dst =dat; dst+= step;
		out5: *dst =dat; dst+= step;
		
		out4: *dst =dat; dst+= step;
		out3: *dst =dat; dst+= step;
		out2: *dst =dat; dst+= step;
		out1: *dst =dat; dst+= step;
	}

}

void	GUI_memset16(U16 *dst,U16 dat,int count)
{
	
	switch(count & 0x7)
	{
		case 7: count &= ~0x07; goto out7;
		case 6: count &= ~0x07; goto out6;
		case 5: count &= ~0x07; goto out5;
		case 4: count &= ~0x07; goto out4;
		case 3: count &= ~0x07; goto out3;
		case 2: count &= ~0x07; goto out2;
		case 1: count &= ~0x07; goto out1;
		default: break;
	}
	
	while(count > 0)
	{
		count -= 8;

//		out8:
      *dst++ =dat;
		out7: *dst++ =dat;
		out6: *dst++ =dat;
		out5: *dst++ =dat;
		
		out4: *dst++ =dat;
		out3: *dst++ =dat;
		out2: *dst++ =dat;
		out1: *dst++ =dat;
	}
}


void	GUI_memset16_step(U16 *dst,U16 dat,int count,int step)
{
	switch(count&0x7)
	{
		case 7: count &= ~0x07; goto out7;
		case 6: count &= ~0x07; goto out6;
		case 5: count &= ~0x07; goto out5;
		case 4: count &= ~0x07; goto out4;
		case 3: count &= ~0x07; goto out3;
		case 2: count &= ~0x07; goto out2;
		case 1: count &= ~0x07; goto out1;
		default: break;
	}
	
	while(count > 0)
	{
		count -= 8;

//		out8: 
      *dst =dat; dst+= step;
		out7: *dst =dat; dst+= step;
		out6: *dst =dat; dst+= step;
		out5: *dst =dat; dst+= step;
		
		out4: *dst =dat; dst+= step;
		out3: *dst =dat; dst+= step;
		out2: *dst =dat; dst+= step;
		out1: *dst =dat; dst+= step;
	}

}

void	GUI_memset32(U32 *dst,U32 dat,int count)
{
	switch(count&0x7)
	{
		case 7: count &= ~0x07; goto out7;
		case 6: count &= ~0x07; goto out6;
		case 5: count &= ~0x07; goto out5;
		case 4: count &= ~0x07; goto out4;
		case 3: count &= ~0x07; goto out3;
		case 2: count &= ~0x07; goto out2;
		case 1: count &= ~0x07; goto out1;
		default: break;
	}
	
	while(count > 0)
	{
		count -= 8;

//		out8: 
      *dst++ =dat;
		out7: *dst++ =dat;
		out6: *dst++ =dat;
		out5: *dst++ =dat;
		
		out4: *dst++ =dat;
		out3: *dst++ =dat;
		out2: *dst++ =dat;
		out1: *dst++ =dat;
	}
}

void	GUI_memset32_step(U32 *dst,U32 dat,int count,int step)
{
	switch(count&0x7)
	{
		case 7: count &= ~0x07; goto out7;
		case 6: count &= ~0x07; goto out6;
		case 5: count &= ~0x07; goto out5;
		case 4: count &= ~0x07; goto out4;
		case 3: count &= ~0x07; goto out3;
		case 2: count &= ~0x07; goto out2;
		case 1: count &= ~0x07; goto out1;
		default: break;
	}
	
	while(count > 0)
	{
		count -= 8;

//		out8: 
      *dst =dat; dst+= step;
		out7: *dst =dat; dst+= step;
		out6: *dst =dat; dst+= step;
		out5: *dst =dat; dst+= step;
		
		out4: *dst =dat; dst+= step;
		out3: *dst =dat; dst+= step;
		out2: *dst =dat; dst+= step;
		out1: *dst =dat; dst+= step;
	}
}

/*===================================================================================*/
#if 0
U8	alpha_blend_value(U8 dst,U8 src,U8 src_a)
{
//	return	( src * src_a + dst * (255-src_a))>>8;
	return	(((src-dst)*src_a)>>8) + dst; 
}
#endif

U8 GUI_AlphaBlendValue(U8 dst,U8 src,U8 src_a)
{
	return	(((src-dst)*src_a)>>8) + dst;
}

/*============================================================================*/

COLOR_RGB32 GUI_AlphaBlendColor(COLOR_RGB32 bk_c,COLOR_RGB32 fr_c,U8 alpha)
{
	U8 bk_r,bk_g,bk_b;
	U8 fr_r,fr_g,fr_b;
	
	bk_r =bk_c>>16;
	bk_g =bk_c>>8;
	bk_b =bk_c;
	
	fr_r =fr_c>>16;
	fr_g =fr_c>>8;
	fr_b =fr_c;

	
	fr_r = (((fr_r-bk_r)*alpha)>>8) + bk_r; 
	fr_g = (((fr_g-bk_g)*alpha)>>8) + bk_g; 
	fr_b = (((fr_b-bk_b)*alpha)>>8) + bk_b; 

/*
	fr_r = ( fr_r * alpha + bk_r * (255-alpha))>>8;
	fr_g = ( fr_g * alpha + bk_g * (255-alpha))>>8;	
	fr_b = ( fr_b * alpha + bk_b * (255-alpha))>>8;	
*/

	return	RGB888(fr_r,fr_g,fr_b);
	
}



/*============================================================================*/



/*===================================================================================*/

/*===================================================================================*/


/**
  * @brief  GUI内核矩形链表，主要用于窗口Z序
  */

/* 是否打印当前使用的矩形链表数 */
//#define	RGN_DEBUG

/** 
 在静态内存中最大的RECT_LL 链表数，
 使用静态内存链表可以极快速的分配，以提升系统性能
 如果这个静态 RECT_LL 链表用完，就会调用 GUI_MEM_Alloc，
 以动态内存方式分配 RECT_LL 
 这部分在GUI_RectLL_Alloc函数实现

 如果用户窗口不多，并且系统静态 RAM又比较少时，
 就可以把这个表定义小一点
 
 一个RECT_LL元素20字节，总的静态空间占用为 20*RECT_LL_SLOT_NUM 个字节
*/
#ifndef	RECT_LL_SLOT_NUM
#define	RECT_LL_SLOT_NUM	512
#endif

static	RECT_LL *rgn_free=NULL;
static	RECT_LL  rgn_slot[RECT_LL_SLOT_NUM];
static	GUI_MUTEX *rgn_lock=NULL;

#ifdef	RGN_DEBUG
static	int	rgn_use=0;
static	int rgn_use_max=0;
#endif

/**
  * @brief  初始化GUI内核矩形链表
  */
static void	_RectLL_Init(void)
{
	int i;

#ifdef	RGN_DEBUG
	rgn_use 	=0;
	rgn_use_max =0;
#endif

	rgn_lock =GUI_MutexCreate();


	for(i=0;i<RECT_LL_SLOT_NUM-1;i++)
	{
		rgn_slot[i].next   = &rgn_slot[i+1];
		rgn_slot[i+1].next = NULL;
	}
	rgn_slot[RECT_LL_SLOT_NUM-1].next =NULL;

	rgn_free =rgn_slot;

}

/**
  * @brief  申请GUI内核矩形链表
  * @note   若当前使用的小于RECT_LL_SLOT_NUM，直接从静态内存rgn_slot中分配，
  *         否则通过GUI_MEM_Alloc从动态空间分配
  */
RECT_LL*	GUI_RectLL_Alloc(void)
{
	RECT_LL *rgn;

	GUI_MutexLock(rgn_lock,0xFFFFFFFF);
	rgn	=rgn_free;
	if(rgn!=NULL)
	{
		rgn_free =rgn->next;
#ifdef	RGN_DEBUG
		rgn_use++;
		if(rgn_use > rgn_use_max)
		{
			rgn_use_max =rgn_use;
			GUI_DEBUG("rgn_use_max: %d\r\n",rgn_use_max);
		}
#endif
	}
	GUI_MutexUnlock(rgn_lock);

	if(rgn==NULL)
	{
		rgn =GUI_MEM_Alloc(sizeof(RECT_LL));
		rgn->next=NULL;
	}
	return	rgn;
}

/**
  * @brief  释放GUI内核矩形链表
  */
void	GUI_RectLL_Free(RECT_LL* rgn)
{
	RECT_LL *next;

	GUI_MutexLock(rgn_lock,0xFFFFFFFF);
	while(rgn != NULL)
	{
		next = rgn->next;

		if(rgn >= &rgn_slot[0])
		if(rgn <= &rgn_slot[RECT_LL_SLOT_NUM-1])
		{
			rgn->next = rgn_free;
			rgn_free  = rgn;
		}
		else
		{
			GUI_MEM_Free(rgn);
		}
		rgn = next;

#ifdef	RGN_DEBUG
		if(rgn_use>0)
		{
			rgn_use--;
		}
#endif
	}
	GUI_MutexUnlock(rgn_lock);


}


/*============================================================================*/
/**
  * @brief  GUI架构适配层初始化.
  */
BOOL	GUI_Arch_Init(void)
{
	_RectLL_Init();                    //初始化GUI内核矩形链表，用于窗口叠加时的Z序管理

	GL_MEM_8BPP_Init(&GL_MEM_8PP);   //初始化8位内存型绘图对象.
	GL_MEM_16BPP_Init(&GL_MEM_16PP); //初始化16位内存型绘图对象.
	GL_MEM_32BPP_Init(&GL_MEM_32PP); //初始化32位内存型绘图对象.

	return TRUE;

}


/*============================================================================*/

