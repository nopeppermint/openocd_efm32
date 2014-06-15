/**************************************************************************//**
 * @file
 * @brief Segment LCD Config for the EFM32_G8xx_STK
 * @author Energy Micro AS
 * @version 3.20.0
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2012 Energy Micro AS, http://www.energymicro.com</b>
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 * 4. The source and compiled code may only be used on Energy Micro "EFM32"
 *    microcontrollers and "EFR4" radios.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Energy Micro AS has no
 * obligation to support this Software. Energy Micro AS is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Energy Micro AS will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 * Edit for Olimex EFM32G880F128-STK by S.Weber 28.07.2013
 *****************************************************************************/
#ifndef __SEGMENTLCDCONFIG_H
#define __SEGMENTLCDCONFIG_H

#include "em_lcd.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Range of symbols available on display */
typedef enum
{
	LCD_SYMBOL_OLIMEX,

  LCD_SYMBOL_ARR_UP,
  LCD_SYMBOL_ARR_DN,
  LCD_SYMBOL_ARR_L,
  LCD_SYMBOL_ARR_R,

  LCD_SYMBOL_MINUS,
  LCD_SYMBOL_PLUS,

  LCD_SYMBOL_u,
  LCD_SYMBOL_m,
  LCD_SYMBOL_H,
  LCD_SYMBOL_F,

	LCD_SYMBOL_2COL,
	LCD_SYMBOL_3COL,
	LCD_SYMBOL_4COL,
	LCD_SYMBOL_5COL,
	LCD_SYMBOL_6COL,
  LCD_SYMBOL_10COL,
	
	LCD_SYMBOL_1DP,
	LCD_SYMBOL_2DP,
	LCD_SYMBOL_3DP,
	LCD_SYMBOL_4DP,
	LCD_SYMBOL_5DP,
	LCD_SYMBOL_6DP,
	LCD_SYMBOL_8DP,
	LCD_SYMBOL_10DP,
	LCD_SYMBOL_11DP,
} lcdSymbol;


#define LCD_SYMBOL_OLIMEX_COM  3
#define LCD_SYMBOL_OLIMEX_SEG  15
#define LCD_SYMBOL_ARR_UP_COM  1
#define LCD_SYMBOL_ARR_UP_SEG  3
#define LCD_SYMBOL_ARR_DN_COM  3
#define LCD_SYMBOL_ARR_DN_SEG  3
#define LCD_SYMBOL_ARR_L_COM  0
#define LCD_SYMBOL_ARR_L_SEG  3
#define LCD_SYMBOL_ARR_R_COM	2
#define LCD_SYMBOL_ARR_R_SEG	3
#define LCD_SYMBOL_MINUS_COM  0
#define LCD_SYMBOL_MINUS_SEG  39
#define LCD_SYMBOL_PLUS_COM  3
#define LCD_SYMBOL_PLUS_SEG  39
#define LCD_SYMBOL_u_COM	3
#define LCD_SYMBOL_u_SEG	1
#define LCD_SYMBOL_m_COM  2
#define LCD_SYMBOL_m_SEG  1
#define LCD_SYMBOL_H_COM  1
#define LCD_SYMBOL_H_SEG  1
#define LCD_SYMBOL_F_COM  0
#define LCD_SYMBOL_F_SEG  1
#define LCD_SYMBOL_2COL_COM  3
#define LCD_SYMBOL_2COL_SEG  35
#define LCD_SYMBOL_3COL_COM  3
#define LCD_SYMBOL_3COL_SEG  31
#define LCD_SYMBOL_4COL_COM  3
#define LCD_SYMBOL_4COL_SEG  27
#define LCD_SYMBOL_5COL_COM  3
#define LCD_SYMBOL_5COL_SEG  23
#define LCD_SYMBOL_6COL_COM  3
#define LCD_SYMBOL_6COL_SEG  19
#define LCD_SYMBOL_10COL_COM  3
#define LCD_SYMBOL_10COL_SEG  7
#define LCD_SYMBOL_1DP_COM 0
#define LCD_SYMBOL_1DP_SEG 35
#define LCD_SYMBOL_2DP_COM 0
#define LCD_SYMBOL_2DP_SEG 31
#define LCD_SYMBOL_3DP_COM 0
#define LCD_SYMBOL_3DP_SEG 27
#define LCD_SYMBOL_4DP_COM 0
#define LCD_SYMBOL_4DP_SEG 23
#define LCD_SYMBOL_5DP_COM 0
#define LCD_SYMBOL_5DP_SEG 19
#define LCD_SYMBOL_6DP_COM 0
#define LCD_SYMBOL_6DP_SEG 15
#define LCD_SYMBOL_8DP_COM 3
#define LCD_SYMBOL_8DP_SEG 10
#define LCD_SYMBOL_10DP_COM 3
#define LCD_SYMBOL_10DP_SEG 8
#define LCD_SYMBOL_11DP_COM 3
#define LCD_SYMBOL_11DP_SEG 5

/* LCD Controller Prescaler (divide by 128) */
/* CLKlcd = 256 Hz */
#define LCD_CMU_CLK_PRE         cmuClkDiv_128
#define LCD_CMU_CLK_DIV         0

#define LCD_BOOST_LEVEL         lcdVBoostLevel0

#define LCD_INIT_DEF \
{ true,\
  lcdMuxQuadruplex,\
  lcdBiasOneThird,\
  lcdWaveLowPower,\
  lcdVLCDSelVDD,\
  lcdConConfVLCD }

#define LCD_NUMBER_OFF() \
do { \
	LCD_SegmentSetLow(0, 0x00000FF0, 0x00000000);\
  LCD_SegmentSetLow(1, 0x00000FF0, 0x00000000);\
  LCD_SegmentSetLow(2, 0x00000FF0, 0x00000000);\
  LCD_SegmentSetLow(3, 0x00000A50, 0x00000000);\
} while (0)

#define LCD_ALPHA_NUMBER_OFF() \
do { \
  LCD_SegmentSetLow(0, 0x77777000, 0x00000000);\
  LCD_SegmentSetLow(1, 0xFFFFF000, 0x00000000);\
  LCD_SegmentSetLow(2, 0xFFFFF000, 0x00000000);\
  LCD_SegmentSetLow(3, 0x77777000, 0x00000000);\
	LCD_SegmentSetHigh(0, 0x77, 0x00000000);\
  LCD_SegmentSetHigh(1, 0xFF, 0x00000000);\
  LCD_SegmentSetHigh(2, 0xFF, 0x00000000);\
  LCD_SegmentSetHigh(3, 0x77, 0x00000000);\
} while(0)

#define LCD_ALL_SEGMENTS_OFF() \
do { \
  LCD_SegmentSetLow(0, 0xFFFFFFFF, 0x00000000);\
  LCD_SegmentSetLow(1, 0xFFFFFFFF, 0x00000000);\
  LCD_SegmentSetLow(2, 0xFFFFFFFF, 0x00000000);\
  LCD_SegmentSetLow(3, 0xFFFFFFFF, 0x00000000);\
  LCD_SegmentSetHigh(0, 0xFF, 0x00000000);\
  LCD_SegmentSetHigh(1, 0xFF, 0x00000000);\
  LCD_SegmentSetHigh(2, 0xFF, 0x00000000);\
  LCD_SegmentSetHigh(3, 0xFF, 0x00000000);\
} while(0)

#define LCD_ALL_SEGMENTS_ON() \
do { \
  LCD_SegmentSetLow(0, 0xFFFFFFFF, 0xFFFFFFFF);\
  LCD_SegmentSetLow(1, 0xFFFFFFFF, 0xFFFFFFFF);\
  LCD_SegmentSetLow(2, 0xFFFFFFFF, 0xFFFFFFFF);\
  LCD_SegmentSetLow(3, 0xFFFFFFFF, 0xFFFFFFFF);\
  LCD_SegmentSetHigh(0, 0xFF, 0xFFFFFFFF);\
  LCD_SegmentSetHigh(1, 0xFF, 0xFFFFFFFF);\
  LCD_SegmentSetHigh(2, 0xFF, 0xFFFFFFFF);\
  LCD_SegmentSetHigh(3, 0xFF, 0xFFFFFFFF);\
} while(0)

#define LCD_SEGMENTS_ENABLE() \
do { \
  LCD_SegmentRangeEnable(lcdSegmentAll, true);\
} while(0)

#define LCD_DISPLAY_ENABLE() \
do { \
  ;\
} while(0)

#define EFM_DISPLAY_DEF {\
  .Text        = {\
    { /* 1 */\
      .com[0] = 3, .com[1] = 2, .com[2] = 1, .com[3] = 0,\
      .bit[0] = 37, .bit[1] = 37, .bit[2] = 37, .bit[3] = 37,\
			.com[4] = 1, .com[5] = 2, .com[6] = 2, .com[7] = 3,\
      .bit[4] = 39, .bit[5] = 39, .bit[6] = 38, .bit[7] = 38,\
			.com[8] = 3, .com[9] = 2, .com[10] = 1, .com[11] = 0,\
      .bit[8] = 36, .bit[9] = 36, .bit[10] = 36, .bit[11] = 36,  \
      .com[12] = 0, .com[13] = 1, \
      .bit[12] = 38, .bit[13] = 38,  \
    },\
    { /* 2 */\
      .com[0] = 3, .com[1] = 2, .com[2] = 1, .com[3] = 0,  \
      .bit[0] = 33, .bit[1] = 33, .bit[2] = 33, .bit[3] = 33,\
      .com[4] = 1, .com[5] = 2, .com[6] = 2, .com[7] = 3,    \
      .bit[4] = 35, .bit[5] = 35, .bit[6] = 34, .bit[7] = 34, \
      .com[8] = 3, .com[9] = 2, .com[10] = 1, .com[11] = 0,    \
      .bit[8] = 32, .bit[9] = 32, .bit[10] = 32, .bit[11] = 32,  \
      .com[12] = 0, .com[13] = 1,\
      .bit[12] = 34, .bit[13] = 34,\
    },\
    { /* 3 */\
      .com[0] = 3, .com[1] = 2, .com[2] = 1, .com[3] = 0,   \
      .bit[0] = 29, .bit[1] = 29, .bit[2] = 29, .bit[3] = 29,  \
      .com[4] = 1, .com[5] = 2, .com[6] = 2, .com[7] = 3,      \
      .bit[4] = 31, .bit[5] = 31, .bit[6] = 30, .bit[7] = 30,  \
      .com[8] = 3, .com[9] = 2, .com[10] = 1, .com[11] = 0,   \
      .bit[8] = 28, .bit[9] = 28, .bit[10] = 28, .bit[11] = 28,   \
      .com[12] = 0, .com[13] = 1,\
      .bit[12] = 30, .bit[13] = 30,\
    },\
    { /* 4 */\
      .com[0] = 3, .com[1] = 2, .com[2] = 1, .com[3] = 0,    \
      .bit[0] = 25, .bit[1] = 25, .bit[2] = 25, .bit[3] = 25,\
      .com[4] = 1, .com[5] = 2, .com[6] = 2, .com[7] = 3,\
      .bit[4] = 27, .bit[5] = 27, .bit[6] = 26, .bit[7] = 26,\
      .com[8] = 3, .com[9] = 2, .com[10] = 1, .com[11] = 0,\
      .bit[8] = 24, .bit[9] = 24, .bit[10] = 24, .bit[11] = 24,\
      .com[12] = 0, .com[13] = 1,\
      .bit[12] = 26, .bit[13] = 26,\
    },\
    { /* 5 */\
      .com[0] = 3, .com[1] = 2, .com[2] = 1, .com[3] = 0,\
      .bit[0] = 21, .bit[1] = 21, .bit[2] = 21, .bit[3] = 21,\
      .com[4] = 1, .com[5] = 2, .com[6] = 2, .com[7] = 3,\
      .bit[4] = 23, .bit[5] = 23, .bit[6] = 22, .bit[7] = 22,\
      .com[8] = 3, .com[9] = 2, .com[10] = 1, .com[11] = 0,\
      .bit[8] = 20, .bit[9] = 20, .bit[10] = 20, .bit[11] = 20,\
      .com[12] = 0, .com[13] = 1,\
      .bit[12] = 22, .bit[13] = 22,\
    },\
    { /* 6 */\
      .com[0] = 3, .com[1] = 2, .com[2] = 1, .com[3] = 0,\
      .bit[0] = 17, .bit[1] = 17, .bit[2] = 17, .bit[3] = 17,\
      .com[4] = 1, .com[5] = 2, .com[6] = 2, .com[7] = 3,\
      .bit[4] = 19, .bit[5] = 19, .bit[6] = 18, .bit[7] = 18,\
      .com[8] = 3, .com[9] = 2, .com[10] = 1, .com[11] = 0,\
      .bit[8] = 16, .bit[9] = 16, .bit[10] = 16, .bit[11] = 16,\
      .com[12] = 0, .com[13] = 1,\
      .bit[12] = 18, .bit[13] = 18,\
    },\
    { /* 7 */\
      .com[0] = 3, .com[1] = 2, .com[2] = 1, .com[3] = 0,\
      .bit[0] = 13, .bit[1] = 13, .bit[2] = 13, .bit[3] = 13,\
      .com[4] = 1, .com[5] = 2, .com[6] = 2, .com[7] = 3,\
      .bit[4] = 15, .bit[5] = 15, .bit[6] = 14, .bit[7] = 14,\
      .com[8] = 3, .com[9] = 2, .com[10] = 1, .com[11] = 0,\
      .bit[8] = 12, .bit[9] = 12, .bit[10] = 12, .bit[11] = 12,\
      .com[12] = 0, .com[13] = 1,\
      .bit[12] = 14, .bit[13] = 14,\
    }\
  },\
  .Number      = {\
		{/* 11 */\
      .com[0] = 0, .com[1] = 0, .com[2] = 2, .com[3] = 3,\
      .bit[0] = 5, .bit[1] = 4, .bit[2] = 4, .bit[3] = 4,\
      .com[4] = 2, .com[5] = 1, .com[6] = 1,\
      .bit[4] =5, .bit[5] = 5, .bit[6] = 4,\
    },\
		{/* 10 */\
      .com[0] = 0, .com[1] = 0, .com[2] = 2, .com[3] = 3,\
      .bit[0] = 7, .bit[1] = 6, .bit[2] = 6, .bit[3] = 6,\
      .com[4] = 2, .com[5] = 1, .com[6] = 1,\
      .bit[4] = 7, .bit[5] = 7, .bit[6] = 6,\
    },\
		{/* 9 */\
      .com[0] = 0, .com[1] = 1, .com[2] = 2, .com[3] = 3,\
      .bit[0] = 8, .bit[1] = 8, .bit[2] = 8, .bit[3] = 9,\
      .com[4] = 2, .com[5] = 0, .com[6] = 1,\
      .bit[4] = 9, .bit[5] = 9, .bit[6] = 9,\
    },\
    { /* 8 */\
      .com[0] = 0, .com[1] = 1, .com[2] = 2, .com[3] = 3,\
      .bit[0] = 10, .bit[1] = 10, .bit[2] = 10, .bit[3] = 11,\
      .com[4] = 2, .com[5] = 0, .com[6] = 1,\
      .bit[4] = 11, .bit[5] = 11, .bit[6] = 11,\
    },\
  },\
  .Battery       = {\
    .com[0] = 0, .bit[0] = 2,\
    .com[1] = 3, .bit[1] = 2, \
    .com[2] = 2, .bit[2] = 2,\
    .com[3] = 1, .bit[3] = 2,\
  },\
  .PowerMeter       = {\
    .com[0] = 3, .bit[0] = 0,\
    .com[1] = 2, .bit[1] = 0,\
    .com[2] = 1, .bit[2] = 0,\
    .com[3] = 0, .bit[3] = 0,\
    .com[4] = 0, .bit[4] = 0,\
    .com[5] = 1, .bit[5] = 0,\
    .com[6] = 2, .bit[6] = 0,\
    .com[7] = 3, .bit[7] = 0,\
    .com[8] = 3, .bit[0] = 0,\
    .com[9] = 2, .bit[1] = 0,\
    .com[10] = 1, .bit[2] = 0,\
    .com[11] = 0, .bit[3] = 0 \
  },\
  .Arrows     = {\
    .com[0] = 3, .bit[0] = 3,\
    .com[1] = 2, .bit[1] = 3,\
    .com[2] = 1, .bit[2] = 3,\
    .com[3] = 0, .bit[3] = 3 \
  }\
};

#ifdef __cplusplus
}
#endif

#endif
