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

#include <stdint.h>
#include <stdbool.h>
#include "em_device.h"		//Include h-file for defined Chip
#include "em_chip.h" 			//Chip init
#include "segmentlcd.h"
#include "lcdtest.h"

/******************************************************************************
* @brief  Main function 																											*
******************************************************************************/
int main (void)
{
  CHIP_Init();
	
	/* Enable LCD without voltage boost */
  SegmentLCD_Init(false);

  /* Run Energy Mode with LCD demo, see lcdtest.c */
  Test();
	
	/* Never going to reach this statement. Infinte loop in Test(). */
	return 0;

}// end int main (void)
/******************************************************************************/
