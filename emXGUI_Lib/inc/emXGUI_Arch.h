#ifndef	__EMXGUI_ARCH_H__
#define	__EMXGUI_ARCH_H__

#ifdef	__cplusplus
extern	"C"{
#endif

#include <emXGUI.h>

/*===================================================================================*/

typedef	struct tagGUI_MUTEX		GUI_MUTEX;
typedef	struct tagGUI_SEM		GUI_SEM;

/*===================================================================================*/

typedef	struct	tagRECT_LL
{
	RECT   rc;
	struct	tagRECT_LL *next;

}RECT_LL;

typedef struct tagCOLOR_CONVERT
{
  COLORREF	(*MapRGB332)(U32 rgb332);
	COLORREF	(*MapRGB565)(U32 rgb565);
	COLORREF	(*MapXRGB1555)(U32 xrgb1555);
	COLORREF	(*MapARGB1555)(U32 argb1555);
	COLORREF	(*MapXRGB4444)(U32 xrgb4444);
	COLORREF	(*MapARGB4444)(U32 argb4444);
	COLORREF	(*MapXRGB8888)(U32 xrgb8888);
	COLORREF	(*MapARGB8888)(U32 argb8888);

	U32			(*ToARGB)(COLORREF c);
	COLORREF	(*MapRGB)(U8 r,U8 g,U8 b);
	COLORREF	(*MapARGB)(U8 a,U8 r,U8 g,U8 b);
	void		(*GetRGB)(COLORREF c,U8 *r,U8 *g,U8 *b);
	void		(*GetARGB)(COLORREF c,U8 *a,U8 *r,U8 *g,U8 *b);

}COLOR_CONVERT;



typedef	void* 	FN_GL_SetPos(const SURFACE *pSurf,int x,int y);
typedef	void		FN_GL_SetPixel(const SURFACE *pSurf,int x,int y,COLORREF color);
typedef	COLORREF	FN_GL_GetPixel(const SURFACE *pSurf,int x,int y);
typedef	void    FN_GL_XorPixel(const SURFACE *pSurf,int x,int y);
typedef	void		FN_GL_HLine(const SURFACE *pSurf,int x0,int y0,int x1,COLORREF color);
typedef	void		FN_GL_VLine(const SURFACE *pSurf,int x0,int y0,int y1,COLORREF color);
typedef	void		FN_GL_Line(const SURFACE *pSurf,int x0,int y0,int x1,int y1,COLORREF color);
typedef	void		FN_GL_FillArea(const SURFACE *pSurf,int x,int y,int w,int h,COLORREF color);
typedef	int 		FN_GL_CopyBits(const SURFACE *pSurf,int x,int y,int w,int h,int width_bytes,U8 *buf);

typedef	void		FN_GL_DrawBitmap_LUT1(const SURFACE *pSurf,int x,int y,int w,int h,int width_bytes,const U8 *bits,int bit_offset,const COLORREF *color_tbl);
typedef	void		FN_GL_DrawBitmap_LUT2(const SURFACE *pSurf,int x,int y,int w,int h,int width_bytes,const U8 *bits,int bit_offset,const COLORREF *color_tbl);
typedef	void		FN_GL_DrawBitmap_LUT4(const SURFACE *pSurf,int x,int y,int w,int h,int width_bytes,const U8 *bits,int bit_offset,const COLORREF *color_tbl);
typedef	void		FN_GL_DrawBitmap_LUT8(const SURFACE *pSurf,int x,int y,int w,int h,int width_bytes,const U8 *bits,const COLORREF *color_tbl);
typedef	void		FN_GL_DrawBitmap_RGB(const	SURFACE *pSurf,int x,int y,int w,int h,int width_bytes,const U8 *bits);
typedef	void		FN_GL_DrawBitmap_AL1(const SURFACE *pSurf,int x,int y,int w,int h,int width_bytes,const U8 *bits,int bit_offset,COLORREF color);
typedef	void		FN_GL_DrawBitmap_AL2(const SURFACE *pSurf,int x,int y,int w,int h,int width_bytes,const U8 *bits,int bit_offset,COLORREF color);
typedef	void		FN_GL_DrawBitmap_AL4(const SURFACE *pSurf,int x,int y,int w,int h,int width_bytes,const U8 *bits,int bit_offset,COLORREF color);
typedef	void		FN_GL_DrawBitmap_AL8(const SURFACE *pSurf,int x,int y,int w,int h,int width_bytes,const U8 *bits,COLORREF color);

typedef	BOOL	FN_GL_BitBlt(const SURFACE *dstSurf,int dst_x,int dst_y,int dst_w,int dst_h,const SURFACE *srcSurf,int src_x,int src_y,U32 dwRop);
typedef	BOOL	FN_GL_StretchBlt(const SURFACE *dstSurf,int dst_x,int dst_y,int dst_w,int dst_h,const SURFACE *srcSurf,int src_x,int src_y,int src_dx,int src_dy,U32 dwRop);
typedef	BOOL	FN_GL_TransparentBlt(const SURFACE *dstSurf,int dst_x,int dst_y,int dst_w,int dst_h,const SURFACE *srcSurf,int src_x,int src_y,int src_w,int src_h,COLORREF key_color);
typedef	BOOL	FN_GL_AlphaBlend(const SURFACE *dstSurf,int dst_x,int dst_y,int dst_w,int dst_h,const SURFACE *srcSurf,int src_x,int src_y,int src_w,int src_h,BLENDFUNCTION *op);

typedef	BOOL	FN_GL_ScaleBitmap(const SURFACE *pSurf,int x,int y,int w,int h,const BITMAP *bm);
typedef	BOOL	FN_GL_RotateBitmap(const SURFACE *pSurf,int cx,int cy,const BITMAP *bm,int angle);

/*============================================================================*/
/**
  * @brief  绘图对象，包含相应的绘图操作函数指针
  */
typedef	struct	tagGL_OP{

	FN_GL_SetPos		*SetPos;
	FN_GL_SetPixel		*SetPixel;
	FN_GL_GetPixel		*GetPixel;
	FN_GL_XorPixel		*XorPixel;
	FN_GL_HLine			*HLine;
	FN_GL_VLine			*VLine;
	FN_GL_Line			*Line;
	FN_GL_FillArea		*FillArea;
	FN_GL_CopyBits		*CopyBits;
	
	FN_GL_DrawBitmap_LUT1	*DrawBitmap_LUT1;
	FN_GL_DrawBitmap_LUT2	*DrawBitmap_LUT2;
	FN_GL_DrawBitmap_LUT4	*DrawBitmap_LUT4;
	FN_GL_DrawBitmap_LUT8	*DrawBitmap_LUT8;
	
	FN_GL_DrawBitmap_RGB	*DrawBitmap_RGB332;
	FN_GL_DrawBitmap_RGB	*DrawBitmap_RGB565;
	FN_GL_DrawBitmap_RGB	*DrawBitmap_XRGB1555;
	FN_GL_DrawBitmap_RGB	*DrawBitmap_ARGB1555;
	FN_GL_DrawBitmap_RGB	*DrawBitmap_ARGB4444;
	FN_GL_DrawBitmap_RGB	*DrawBitmap_RGB888;
	FN_GL_DrawBitmap_RGB	*DrawBitmap_XRGB8888;
	FN_GL_DrawBitmap_RGB	*DrawBitmap_ARGB8888;
	
	FN_GL_DrawBitmap_AL1	*DrawBitmap_AL1;
	FN_GL_DrawBitmap_AL2	*DrawBitmap_AL2;
	FN_GL_DrawBitmap_AL4	*DrawBitmap_AL4;
	FN_GL_DrawBitmap_AL8	*DrawBitmap_AL8;
	
	FN_GL_ScaleBitmap  *ScaleBitmap;
	FN_GL_RotateBitmap *RotateBitmap;

}GL_OP;


#define	SURF_FLAG_GRAM	(1<<0)
/**
  * @brief  绘图表面，包含格式、宽高、显存地址等内容
  */
struct tagSURFACE
{
    U32      Format;            //绘图表面的格式
    U32      Width;             //绘图表面的宽
    U32      Height;            //绘图表面的高
    U32      WidthBytes;        //一行像素点占多少字节
    LPVOID   Bits;              //所在的显存地址
    const COLOR_CONVERT *CC;    //颜色转换函数指针
    const GL_OP *GL;            //绘图引擎指针
    const void  *pdata;         //附加数据
    u32 Flags;                  //标志
};

#define	SURF_MapRGB332(pSurf,rgb332) 		pSurf->CC->MapRGB332(rgb332)
#define	SURF_MapRGB565(pSurf,rgb565) 		pSurf->CC->MapRGB565(rgb565)
#define	SURF_MapXRGB1555(pSurf,xrgb1555) 	pSurf->CC->MapXRGB1555(xrgb1555)
#define	SURF_MapARGB1555(pSurf,argb1555) 	pSurf->CC->MapARGB1555(argb1555)
#define	SURF_MapXRGB4444(pSurf,xrgb4444) 	pSurf->CC->MapXRGB4444(xrgb4444)
#define	SURF_MapARGB4444(pSurf,argb4444) 	pSurf->CC->MapARGB4444(argb4444)
#define	SURF_MapXRGB8888(pSurf,xrgb8888) 	pSurf->CC->MapXRGB8888(xrgb8888)
#define	SURF_MapARGB8888(pSurf,argb8888) 	pSurf->CC->MapARGB8888(argb8888)
#define	SURF_ToARGB(pSurf,color) 			pSurf->CC->ToARGB(color)
#define	SURF_MapRGB(pSurf,r,g,b) 			pSurf->CC->MapRGB(r,g,b)
#define	SURF_MapARGB(pSurf,a,r,g,b) 		pSurf->CC->MapARGB(a,r,g,b)
#define	SURF_GetRGB(pSurf,color,r,g,b) 		pSurf->CC->GetRGB(color,r,g,b)
#define	SURF_GetARGB(pSurf,color,a,r,g,b) 	pSurf->CC->GetARGB(color,a,r,g,b)

/*===================================================================================*/

BOOL 	X_GUI_Init(void);
HWND GUI_CreateDesktop(U32 dwExStyle, const WNDCLASS* wcex, LPCWSTR lpWindowName,
		U32 dwStyle, int x, int y, int nWidth, int nHeight, HWND hwndParent,
		U32 WinId, HINSTANCE hInstance, LPVOID lpParam);

LRESULT DefDesktopProc(HWND hwnd, UINT msg, WPARAM wParam,LPARAM lParam);

void GUI_SetDefFont(HFONT hFont);
void GUI_SetScreenSurface(const SURFACE *pSurf);

/*===================================================================================*/

/**
  * @brief  系统接口对象
  */
void	GUI_msleep(u32 ms);
GUI_MUTEX*	GUI_MutexCreate(void);
BOOL		GUI_MutexLock(GUI_MUTEX *hMutex,UINT time);
void		GUI_MutexUnlock(GUI_MUTEX *hMutex);
void		GUI_MutexDelete(GUI_MUTEX *hMutex);

GUI_SEM*	GUI_SemCreate(int init,int max);
BOOL		GUI_SemWait(GUI_SEM *hSem,U32 time);
void		GUI_SemPost(GUI_SEM *hSem);
void		GUI_SemDelete(GUI_SEM *hSem);
HANDLE		GUI_GetCurThreadHandle(void);
U32			GUI_GetTickCount(void);
void		GUI_Yield(void);


COLOR_RGB32	GUI_AlphaBlendColor(COLOR_RGB32 bk_c,COLOR_RGB32 fr_c,U8 alpha);

RECT_LL*	GUI_RectLL_Alloc(void);
void		GUI_RectLL_Free(RECT_LL* rgn);

/**
  * @brief  初始化光标
  * @param  pSurf[in] 绘图表面
  * @param  x y 光标的初始坐标x y
  * @retval 是否初始化成功
  */
BOOL	GL_CursorInit(const SURFACE *pSurf,int x,int y);
int 	GL_ShowCursor(BOOL bShow);
BOOL	GL_GetCursorPos(int *x,int *y);
BOOL	GL_SetCursorPos(int x,int y);
BOOL	GL_SetCursorClipRect(const RECT *lprc);
void	GL_CursorCheck(const RECT *lprc);
void 	GL_CursorFix(void);

int		GL_BitBlt(const SURFACE *dstSurf,int dst_x,int dst_y,int dst_w,int dst_h,const SURFACE *srcSurf,int src_x,int src_y,U32 rop);
int		GL_StretchBlt(const SURFACE *dstSurf,int dst_x,int dst_y,int dst_w,int dst_h,const SURFACE *srcSurf,int src_x,int src_y,int src_w,int src_h,U32 rop);
int		GL_TransparentBlt(const SURFACE *dstSurf,int dst_x,int dst_y,int dst_w,int dst_h,const SURFACE *srcSurf,int src_x,int src_y,int src_w,int src_h,COLORREF trans_color);
int		GL_AlphaBlend(const SURFACE *dstSurf,int dst_x,int dst_y,int dst_w,int dst_h,const SURFACE *srcSurf,int src_x,int src_y,int src_w,int src_h,BLENDFUNCTION *bf);
U8		GUI_AlphaBlendValue(U8 dst,U8 src,U8 src_a);


/*===================================================================================*/

extern const COLOR_CONVERT RGB332_ColorConvert;
extern const COLOR_CONVERT RGB565_ColorConvert;
extern const COLOR_CONVERT ARGB4444_ColorConvert;
extern const COLOR_CONVERT XRGB8888_ColorConvert;
extern const COLOR_CONVERT ARGB8888_ColorConvert;

void	GUI_memset8(U8 *dst,U8 dat,int count);
void	GUI_memset8_step(U8 *dst,U8 dat,int count,int step);
void	GUI_memset16(U16 *dst,U16 dat,int count);
void	GUI_memset16_step(U16 *dst,U16 dat,int count,int step);
void	GUI_memset32(U32 *dst,U32 dat,int count);
void	GUI_memset32_step(U32 *dst,U32 dat,int count,int step);

void GL_MEM_8BPP_Init(GL_OP *gd);
void GL_MEM_16BPP_Init(GL_OP *gd);
void GL_MEM_32BPP_Init(GL_OP *gd);
void GL_MPU_16BPP_Init(GL_OP *gd);

extern	GL_OP GL_MEM_8PP;
extern	GL_OP GL_MEM_16PP;
extern	GL_OP GL_MEM_32PP;

/**
  * @brief  初始化绘图表面
  * @param  pSurf[out] 根据其它参数对pSurf进行初始化
  * @param  gdraw[in] 绘图对象，如GL_MEM_8PP、GL_MEM_16PP、GL_MEM_32PP
  * @param  w h 绘图表面的宽和高
  * @param  line_bytes 一行像素占多少个字节
  * @param  bits[in] 显存指针
  */
void	SurfaceInit_RGB332(SURFACE *pSurf,const GL_OP *gdraw,int w,int h,int line_bytes,void *bits);
void	SurfaceInit_RGB565(SURFACE *pSurf,const GL_OP *gdraw,int w,int h,int line_bytes,void *bits);
void	SurfaceInit_ARGB4444(SURFACE *pSurf,const GL_OP *gdraw,int w,int h,int line_bytes,void *bits);
void	SurfaceInit_XRGB8888(SURFACE *pSurf,const GL_OP *gdraw,int w,int h,int line_bytes,void *bits);
void	SurfaceInit_ARGB8888(SURFACE *pSurf,const GL_OP *gdraw,int w,int h,int line_bytes,void *bits);


/*===================================================================================*/

#ifdef	__cplusplus
}
#endif
#endif
