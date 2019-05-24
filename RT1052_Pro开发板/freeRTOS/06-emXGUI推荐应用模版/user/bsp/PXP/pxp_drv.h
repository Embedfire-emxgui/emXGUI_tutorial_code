/*
 * pxp_drv.h
 *
 *  Created on: 2018Äê8ÔÂ24ÈÕ
 *      Author: liuwei
 */

#ifndef SRC_BSP_COMMON_PXP_PXP_DRV_H_
#define SRC_BSP_COMMON_PXP_PXP_DRV_H_

#include "fsl_pxp.h"
#include "emXGUI.h"




BOOL	PXP_fill_rect(const SURFACE *pSurf,int x,int y,int w,int h,u32 c);
BOOL	PXP_draw_bitmap_RGB(const SURFACE *pSurf,int x,int y,int w,int h,int width_bytes,const U8 *bits,pxp_ps_pixel_format_t pixelFormat);
BOOL 	PXP_draw_bitmap_ARGB(const SURFACE *pSurf,int x,int y,int w,int h,int width_bytes,const U8 *bits,pxp_as_pixel_format_t pixelFormat);
int		PXP_StretchBlt_SRCCOPY(const SURFACE *dstSurf,int dst_x,int dst_y,int dst_w,int dst_h,const SURFACE *srcSurf,int src_x,int src_y,int src_w,int src_h);
BOOL	PXP_ScaleBitmap(const SURFACE *pSurf,int x,int y,int w,int h,const BITMAP *bm);


void PXP_DrvInit(void);


#endif /* SRC_BSP_COMMON_PXP_PXP_DRV_H_ */
