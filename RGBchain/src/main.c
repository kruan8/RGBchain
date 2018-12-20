/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "stm32f0xx.h"
#include "RGBlibrary.h"
#include "effects.h"
#include <string.h>


/*
 * Shift level 3,3/5
 * https://learn.sparkfun.com/tutorials/bi-directional-logic-level-converter-hookup-guide/all
 *
 *
 *
 *
 */


int main(void)
{
	// kontrola hodin
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq(&RCC_Clocks); // Get system clocks

	RGBlib_Init();

  // test svitivosti vsech barev
  Eff_Test();

	while (1)
	{
	  Eff_EffectLoop();
	}
}

