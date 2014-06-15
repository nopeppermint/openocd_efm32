/**************************************************************************//**
 * @file
 * @brief LCD Controller test and demo
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
#include <string.h>
#include <stddef.h>
#include "em_device.h"
#include "em_emu.h"
#include "em_lcd.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "segmentlcd.h"
#include "lcdtest.h"
#include "rtcdrv.h"

/** Demo scroll text */
static char *stext = "Energy Micro        ";

#define DEMO_MODE_NONE    0x0
#define DEMO_MODE_EM3     0x1
#define DEMO_MODE_EM4     0x2

static uint16_t emMode = DEMO_MODE_NONE;
static bool     inEM3  = false;

/**************************************************************************//**
 * @brief GPIO Interrupt handler (PE1) BUT2
 *****************************************************************************/
void GPIO_ODD_IRQHandler(void)
{
  GPIO_IntClear(1 << 1);

  if (inEM3)
  {
    emMode = DEMO_MODE_NONE;
  }
  else
  {
    emMode = DEMO_MODE_EM3;
		SegmentLCD_Battery(3);
		SegmentLCD_Arrows(0, 1); //arrow down, go to sleep in EM3
  }
}

/**************************************************************************//**
 * @brief GPIO Interrupt handler (PE0) BUT1
 *****************************************************************************/
void GPIO_EVEN_IRQHandler(void)
{
	GPIO_IntClear(1 << 0);
	SegmentLCD_Arrows(0, 1); //arrow down, go to sleep in EM4
	SegmentLCD_Battery(4);
	emMode = DEMO_MODE_EM4;
}

/**************************************************************************//**
 * @brief Initialize GPIO interrupt on PE0 and PE1
 *****************************************************************************/
void GPIO_IRQInit(void)
{
	// enable clock for GPIO module
  CMU_ClockEnable(cmuClock_GPIO, true);

	// Init the Button BUT1 located on PIN PE0
	GPIO_PinModeSet(gpioPortE,0,gpioModeInputPullFilter,1);

	// Init the Button BUT2 located on PIN PE1
	GPIO_PinModeSet(gpioPortE,1,gpioModeInputPullFilter,1);

  /* Enable GPIO_ODD interrupt vector in NVIC */
  NVIC_EnableIRQ(GPIO_ODD_IRQn);
	/* Enable GPIO_EVEN interrupt vector in NVIC */
  NVIC_EnableIRQ(GPIO_EVEN_IRQn);

  /* Configure PE0 interrupt on falling edge */
  GPIO_IntConfig(gpioPortE, 0, false, true, true);

	  /* Configure PE1 interrupt on falling edge */
  GPIO_IntConfig(gpioPortE, 1, false, true, true);
}

/**************************************************************************//**
 * @brief Callback function lighting the "Antenna symbol"
 *****************************************************************************/
void RtcTrigger(void)
{
  /* Just a few No-OPerations to have a place to put a breakpoint */
  SegmentLCD_Symbol(LCD_SYMBOL_OLIMEX, 1);
}

/**************************************************************************//**
 * @brief Sleeps in EM1 in given time unless some other IRQ sources has been
 *        enabled
 * @param msec Time in milliseconds
 *****************************************************************************/
void EM1Sleep(uint32_t msec)
{
  /* Wake us up after msec (or joystick pressed) */
  NVIC_DisableIRQ(LCD_IRQn);
  /* Tell AEM we're in EM1 */
  RTCDRV_Trigger(msec, RtcTrigger);
  EMU_EnterEM1();
  NVIC_EnableIRQ(LCD_IRQn);
}

/**************************************************************************//**
 * @brief Sleeps in EM2 in given time unless some other IRQ sources has been
 *        enabled
 * @param msec Time in milliseconds
 *****************************************************************************/
void EM2Sleep(uint32_t msec)
{
  /* Wake us up after msec (or joystick pressed) */
  NVIC_DisableIRQ(LCD_IRQn);
  RTCDRV_Trigger(msec, NULL);
  EMU_EnterEM2(true);
  NVIC_EnableIRQ(LCD_IRQn);
}


/**************************************************************************//**
 * @brief Sleeps in EM3 until GPIO interrupt is triggered
 *****************************************************************************/
void EM3Sleep(void)
{
  inEM3 = true;
  EMU_EnterEM3(true);
  inEM3 = false;
}

/**************************************************************************//**
 * @brief Sleeps in EM4 until reset
 *****************************************************************************/
void EM4Sleep(void)
{
  EMU_EnterEM4();
  /* we will never wake up again here - reset required */
}

/**************************************************************************//**
 * @brief LCD scrolls a text over the display, sort of "polled printf"
 *****************************************************************************/
void ScrollText(char *scrolltext)
{
  int  i, len;
  char buffer[8];

  buffer[7] = 0x00;
  len       = strlen(scrolltext);
  if (len < 7) return;
  for (i = 0; i < (len - 7); i++)
  {
    memcpy(buffer, scrolltext + i, 7);
    SegmentLCD_Write(buffer);
    EM2Sleep(125);
  }
}

/**************************************************************************//**
 * @brief LCD Test Routine, shows various text and patterns
 *****************************************************************************/
void Test(void)
{
  int i, numberOfIterations = 0;

  /* Initialize GPIO */
  GPIO_IRQInit();

  /* Loop through funny pattern */
  while (1)
  {
    SegmentLCD_AllOff();

    if (emMode == DEMO_MODE_NONE)
    {
      for (i = 100; i > 0; i--)
      {
        SegmentLCD_Number(i);
        EM2Sleep(10);
      }
      SegmentLCD_NumberOff();

			SegmentLCD_Symbol(LCD_SYMBOL_OLIMEX, 1);
      SegmentLCD_Write(" Gecko ");
      EM2Sleep(1000);

      SegmentLCD_AllOn();
      EM2Sleep(1000);

      SegmentLCD_AllOff();

      SegmentLCD_Write("OPENOCD");
      EM2Sleep(2000);
      SegmentLCD_Write("XXXXXXX");
      EM2Sleep(500);
     // SegmentLCD_Write("-EFM32-");
      EM2Sleep(2000);

      /* Various eye candy */
      SegmentLCD_AllOff();
      for (i = 0; i < 17; i++)
      {
        SegmentLCD_LowerNumber( i);
        SegmentLCD_Battery(i);
				SegmentLCD_UnsignedHex(numberOfIterations +i);
        EM2Sleep(200);
      }
			SegmentLCD_Symbol(LCD_SYMBOL_ARR_UP, 1);
			EM2Sleep(200);
			SegmentLCD_Symbol(LCD_SYMBOL_ARR_DN, 1);
			EM2Sleep(200);
			SegmentLCD_Symbol(LCD_SYMBOL_ARR_L, 1);
			EM2Sleep(200);
			SegmentLCD_Symbol(LCD_SYMBOL_ARR_R, 1);
			EM2Sleep(200);
			SegmentLCD_Symbol(LCD_SYMBOL_MINUS, 1);
			SegmentLCD_Symbol(LCD_SYMBOL_PLUS, 1);
			EM2Sleep(100);
			SegmentLCD_Symbol(LCD_SYMBOL_u, 1);
			SegmentLCD_Symbol(LCD_SYMBOL_m, 1);
			SegmentLCD_Symbol(LCD_SYMBOL_H, 1);
			SegmentLCD_Symbol(LCD_SYMBOL_F, 1);
			EM2Sleep(200);
			SegmentLCD_Symbol(LCD_SYMBOL_2COL, 1);
			SegmentLCD_Symbol(LCD_SYMBOL_3COL, 1);
			SegmentLCD_Symbol(LCD_SYMBOL_4COL, 1);
			SegmentLCD_Symbol(LCD_SYMBOL_5COL, 1);
			SegmentLCD_Symbol(LCD_SYMBOL_6COL, 1);
			SegmentLCD_Symbol(LCD_SYMBOL_10COL, 1);
			SegmentLCD_Symbol(LCD_SYMBOL_1DP, 1);
			SegmentLCD_Symbol(LCD_SYMBOL_2DP, 1);
			SegmentLCD_Symbol(LCD_SYMBOL_3DP, 1);
			SegmentLCD_Symbol(LCD_SYMBOL_4DP, 1);
			SegmentLCD_Symbol(LCD_SYMBOL_5DP, 1);
			SegmentLCD_Symbol(LCD_SYMBOL_6DP, 1);
			SegmentLCD_Symbol(LCD_SYMBOL_8DP, 1);
			SegmentLCD_Symbol(LCD_SYMBOL_10DP, 1);
			SegmentLCD_Symbol(LCD_SYMBOL_11DP, 1);
			EM2Sleep(800);
			SegmentLCD_AllOff();
    /* Energy Modes */

			SegmentLCD_Number(0);
			SegmentLCD_Battery(0);
			SegmentLCD_Write("  EM0  ");
			RTCDRV_Delay(2000, false);
			SegmentLCD_Number(1111);
			SegmentLCD_Battery(1);
			SegmentLCD_Write("  EM1  ");
			EM1Sleep(2000);
			SegmentLCD_Number(2222);
			SegmentLCD_Battery(2);
			SegmentLCD_Write("  EM2  ");
			EM2Sleep(2000);
			ScrollText("Energy Mode demo, Press BUT2 for EM3 or BUT1 for EM4        ");
			EM2Sleep(500);
			SegmentLCD_Write("PRESS x");
			EM2Sleep(2000);
		}
    /* Check if somebody has pressed one of the buttons */
    if (emMode == DEMO_MODE_EM3)
    {
			SegmentLCD_Number(3333);
			SegmentLCD_Battery(3);
			SegmentLCD_Arrows(0, 1); //arrow down, go to sleep in EM3
      ScrollText("Going down to EM3, press BUT2 to wake up    ");
      SegmentLCD_Write("  EM3  ");
      RTCDRV_Delay(1000, false);

      /* Wake up on GPIO interrupt */
      EM3Sleep();
			SegmentLCD_Battery(0);
			SegmentLCD_Arrows(0, 0); 	//arrow down off
			SegmentLCD_Arrows(2, 1);	//arrow up, wakeup from sleep in EM3
			SegmentLCD_Write("wakeup");
			RTCDRV_Delay(1500, false);
			SegmentLCD_Arrows(2, 0);	//arrow up off
      SegmentLCD_Battery(0);
			SegmentLCD_Number(0000);
      SegmentLCD_Write("--EM0--");
      RTCDRV_Delay(500, false);
    }
    /* Check if somebody's joystick down */
    if (emMode == DEMO_MODE_EM4)
    {
			SegmentLCD_Number(4444);
			SegmentLCD_Battery(4);
			SegmentLCD_Arrows(0, 1); //arrow down, go to sleep in EM4
      ScrollText("Going down to EM4, press reset to restart    ");
      SegmentLCD_Write("  EM4  ");
      RTCDRV_Delay(1000, false);

      /* Wake up on reset */
      EM4Sleep();
    }

    /* Scrolltext */
    ScrollText(stext);
    numberOfIterations++;
  }
}

