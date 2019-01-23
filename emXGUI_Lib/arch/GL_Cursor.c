/**
  *********************************************************************
  * @file    GL_Cursor.c
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   鼠标绘制接口
  * @note    可在此定制自己的鼠标外观
  *********************************************************************
  * @attention
  * 官网    :www.emXGUI.com
  *
  **********************************************************************
  */ 

#include	"gui_drv.h"

#define	CURSOR_W	20
#define	CURSOR_H	20

/*============================================================================*/

static	RECT rc_cursor;
static	RECT rc_cursor_clip;

static	int oldx =-1;
static	int oldy =-1;

static	int curx =-1;
static	int cury =-1;

static	int cur_show=FALSE;

static	u32	CursorShowNest=0;

#pragma pack(4)
static u16 cursor_buf[CURSOR_H][CURSOR_W]; //ARGB4444
#pragma	pack()

static u8  *cursor_bk_buf =NULL;

static const SURFACE *pSurfScreen=NULL;

/*============================================================================*/
/**
  * @brief  隐藏光标
  */
static	void	_gdevHideCursor(int x,int y,int w,int h)
{

	if(pSurfScreen->Format == SURF_RGB565)
	{
		pSurfScreen->GL->DrawBitmap_RGB565(pSurfScreen,x,y,w,h,2*CURSOR_W,cursor_bk_buf);
	}

	if(pSurfScreen->Format == SURF_XRGB8888)
	{
		pSurfScreen->GL->DrawBitmap_XRGB8888(pSurfScreen,x,y,w,h,4*CURSOR_W,cursor_bk_buf);
	}

}

/**
  * @brief  显示光标
  */
static	void	_gdevShowCursor(int x,int y,int w,int h)
{
	if(pSurfScreen->Format == SURF_RGB565)
	{
		pSurfScreen->GL->CopyBits(pSurfScreen,x,y,w,h,2*CURSOR_W,cursor_bk_buf);
	}

	if(pSurfScreen->Format == SURF_XRGB8888)
	{
		pSurfScreen->GL->CopyBits(pSurfScreen,x,y,w,h,4*CURSOR_W,cursor_bk_buf);
	}

	pSurfScreen->GL->DrawBitmap_ARGB4444(pSurfScreen,x,y,w,h,CURSOR_W*2,(u8*)cursor_buf);
}

/**
  * @brief  隐藏光标
  * @param  无
  * @retval 无
  */
static	void _CursorHide(void)
{
	RECT in_rc,rc;

	rc.x = oldx;
	rc.y = oldy;
	rc.w = CURSOR_W;
	rc.h = CURSOR_H;
	
 	if(rc.x<0)
	{		
		rc.w =MAX(0,rc.w+rc.x);
		rc.x =0;	
	}
		
	if(rc.y<0)
	{	
		rc.h =MAX(0,rc.h+rc.y);
		rc.y =0;	
	}
	
	IntersectRect(&in_rc,&rc_cursor_clip,&rc);
	_gdevHideCursor(in_rc.x,in_rc.y,in_rc.w,in_rc.h);
		
}

/**
  * @brief  显示光标
  * @param  无
  * @retval 无
  */
static	void _CursorShow(void)
{

    RECT in_rc,rc; 

    rc.x = curx;
    rc.y = cury;
    rc.w = CURSOR_W;
    rc.h = CURSOR_H;
	 
 	if(rc.x<0)
	{		
		rc.w =MAX(0,rc.w+rc.x);
		rc.x =0;	
	}
		
	if(rc.y<0)
	{	
		rc.h =MAX(0,rc.h+rc.y);
		rc.y =0;	
	}
  
	IntersectRect(&in_rc,&rc_cursor_clip,&rc);
	_gdevShowCursor(in_rc.x,in_rc.y,in_rc.w,in_rc.h);
	

}

/*============================================================================*/
/*============================================================================*/

#if 0
static	const u8 cursor_bitmap_16x16[16][16]=
{

"@               ",
"@@              ",
"@*@             ",
"@**@            ",
"@*-*@           ",
"@*--*@          ",
"@*---*@         ",
"@*----*@        ",
"@*-----*@       ",
"@*---**-*@      ",
"@*--*@@***@     ",
"@*-*@  @@**@    ",
"@**@     @@*@   ",
"@*@        @@@  ",
"@@           @@ ",
"@               ",

};
#endif

/**
  * @brief  光标基础数据，cursor_bitmap_init会转化成对应的像素数据
  */
static	const u8 cursor_bitmap_16x20[20][16]=
{

"@+             ",
"@@+            ",
"@*@+           ",
"@**@+          ",
"@*-*@+         ",
"@*--*@+        ",
"@*---*@+       ",
"@*----*@+      ",
"@*-----*@+     ",
"@*------*@+    ",
"@*-------*@+   ",
"@*-**--****@+  ",
"@**@@*-*@@@@@+ ",
"@*@+@*-*@+++++ ",
"@@+ +@*-*@+    ",
"@+   @*-*@+    ",
"      @*-*@+   ",
"      @***@+   ",
"       @@@@+   ",
"        +++    ",

};

/**
  * @brief  初始化光标的图像数据
  * @param  pSurf 要显示的绘图表面
  * @retval 无
  */
static	void	cursor_bitmap_init(void)
{
	int x,y;

	for(y=0;y<20;y++)
	{
		for(x=0;x<16;x++)
		{
			switch(cursor_bitmap_16x20[y][x])
			{
				case	'@':
						cursor_buf[y][x] =ARGB4444(15,0,0,0);
						break;
				case	'*':
						cursor_buf[y][x] =ARGB4444(15,15,15,15);
						break;
				case	'+':
						cursor_buf[y][x] =ARGB4444(6,6,6,6);
						break;
				case	'-':
						cursor_buf[y][x] =ARGB4444(8,15,15,15);
						break;
				default:
						cursor_buf[y][x] =ARGB4444(0,0,0,0);
			}
		}
	}
}

/**
  * @brief  初始化光标
  * @param  pSurf 要显示的绘图表面
  * @param  x y 初始显示位置
  * @retval 是否正常
  */
BOOL	GL_CursorInit(const SURFACE *pSurf,int x,int y)
{
	int i;

	pSurfScreen =pSurf;

	cur_show = FALSE;
	CursorShowNest = 0;
	rc_cursor.x = x;
    rc_cursor.y = y;
	rc_cursor.w = CURSOR_W;
	rc_cursor.h = CURSOR_H;

	curx = rc_cursor.x;
	cury = rc_cursor.y;
	oldx = curx;
	oldy = cury;

	rc_cursor_clip.x = 0;
	rc_cursor_clip.y = 0;
	rc_cursor_clip.w = pSurfScreen->Width;
	rc_cursor_clip.h = pSurfScreen->Height;

	cursor_bitmap_init();

	i=0;
	if(pSurfScreen->Format == SURF_RGB565)
	{
		i =CURSOR_W*CURSOR_H*2;
	}
	if(pSurfScreen->Format == SURF_XRGB8888)
	{
		i =CURSOR_W*CURSOR_H*4;
	}

	cursor_bk_buf =GUI_GRAM_Alloc(i);

	if(cursor_bk_buf != NULL)
	{
		return TRUE;
	}

	return FALSE;
}

/*============================================================================*/
/**
  * @brief  显示光标
  * @param  bShow 是否显示
  * @retval 显示层级值
  */
int 	GL_ShowCursor(BOOL bShow)
{
#if(GUI_INPUT_DEV_EN)   
	if(bShow != FALSE)
	{
		if(CursorShowNest < 0xFFFF)
		{
			CursorShowNest++;
		}
		_CursorShow(); 
	}
	else
	{
		if(CursorShowNest > 0)
		{
			CursorShowNest--;
			if(CursorShowNest == 0)
			{
				_CursorHide();	
			}
		}
	
	}
	
	return CursorShowNest;
#else
  return 1;
#endif
}

/**
  * @brief  获取光标坐标
  * @param  x[out] y[out] 获取到的坐标
  * @retval 是否获取正常
  */
BOOL	GL_GetCursorPos(int *x,int *y)
{
	*x = curx;
	*y = cury;
	return	TRUE;
}

/**
  * @brief  设置光标坐标
  * @param  x y 要设置到的坐标
  * @retval 是否正常
  */
BOOL	GL_SetCursorPos(int x,int y)
{
	x = MAX(x,0);
	y = MAX(y,0);
	
    x = MIN(x,pSurfScreen->Width-1);
    y = MIN(y,pSurfScreen->Height-1);
   
    rc_cursor.x	=x;
    rc_cursor.y	=y;
    
    curx = x;
    cury = y;
    
   	if ((oldx != curx) || (oldy != cury))
   	{   		
        if(CursorShowNest > 0)
        {	
            _CursorHide();
            _CursorShow();                     
        }
		
		oldx = curx;
		oldy = cury;
    }
    
	return	TRUE;
}


BOOL	GL_SetCursorClipRect(const RECT *lprc)
{
	RECT in_rc,rc;
	
	int	res =FALSE;
	
	if(lprc == NULL)
	{
		return res;
	}
		
	rc.x = 0;
	rc.y = 0;
	rc.w = pSurfScreen->Width;
	rc.h = pSurfScreen->Height;
	if(IntersectRect(&in_rc,&rc,lprc))
	{
		
		CopyRect(&rc_cursor_clip,&in_rc);
			
		if(CursorShowNest > 0)
		{
			_CursorHide();
			_CursorShow();
				
			oldx = curx;
			oldy = cury;
		}
	
		res = TRUE;
	}
	return res;
}

void	GL_CursorCheck(const RECT *lprc) //
{
	if(CursorShowNest > 0)
	{
		if(cur_show == FALSE)
		{	
			if(lprc!=NULL)
			{
				if(IsIntersectRect(&rc_cursor,lprc))
				{
					_CursorHide();
					cur_show =TRUE;
				}
			}
		}
	}
}

void GL_CursorFix(void)
{
	if(CursorShowNest > 0)
	{
		if(cur_show == TRUE)
		{
			_CursorShow();

			oldx = curx;
			oldy = cury;

			cur_show =FALSE;
		}
	}
}

/*============================================================================*/
/*============================================================================*/

