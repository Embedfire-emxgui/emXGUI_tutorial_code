#ifndef __FONT_H
#define __FONT_H       

#include "./font/fonts.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>



#define LINE(x) ((x) * (((sFONT *)LCD_GetFont())->Height))
#define LINEY(x) ((x) * (((sFONT *)LCD_GetFont())->Width))

/** @defgroup FONTS_Exported_Types
  * @{
  */ 
typedef struct _tFont
{    
  const uint8_t *table; /*指向字模数据的指针*/
  uint16_t Width;       /*字模的像素宽度*/
  uint16_t Height;      /*字模的像素高度*/  
  
} sFONT;
  
/*这些可选的字体格式定义在fonts.c文件*/
extern sFONT Font24x48;
extern sFONT Font16x32;
extern sFONT Font8x16;

//要支持中文需要实现本函数，可参考“液晶显示中英文（字库在外部FLASH）”例程
#define      GetGBKCode( ucBuffer, usChar ) 


#endif /*end of __FONT_H    */


