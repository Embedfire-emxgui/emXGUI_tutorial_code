/*
 * audio_drv.h
 *
 *  Created on: 2017Äê1ÔÂ3ÈÕ
 *      Author: liuwei
 */

#ifndef SRC_BSP_BOARD_APOLLO_STM32F7_DRV_INC_AUDIO_DRV_H_
#define SRC_BSP_BOARD_APOLLO_STM32F7_DRV_INC_AUDIO_DRV_H_

#ifdef	__cplusplus
extern "C"{
#endif

void audio_hard_init(void);
void audio_format_init(u32 bps,u32 sample_rate,u32 size);
void audio_format_deinit(void);
void* audio_sync(int wait_ms);
void audio_set_volume(u8 l,u8 r);
void audio_start(void);
void audio_stop(void);


#ifdef __cplusplus
}
#endif

#endif /* SRC_BSP_BOARD_APOLLO_STM32F7_DRV_INC_AUDIO_DRV_H_ */
