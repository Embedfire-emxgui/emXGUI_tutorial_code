#ifndef __GUI_INPUT_PORT_H
#define	__GUI_INPUT_PORT_H

#ifdef __cplusplus
extern "C" {
#endif  
  
#include	"emXGUI.h"
#include "stm32f4xx.h"
#include	"gui_drv_cfg.h"


BOOL GUI_InputInit(void);
void GUI_InputHandler(void);

#ifdef	__cplusplus
}
#endif  
  
#endif /* __GUI_INPUT_PORT_H */
