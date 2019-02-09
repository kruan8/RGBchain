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
 * Spot�eba  12LED:
 *
 * LED on -  5V / 80mA
 * LED off (sn�en� frekvence) - 5V / 20mA
 *
 * Shift level 3,3/5
 * https://learn.sparkfun.com/tutorials/bi-directional-logic-level-converter-hookup-guide/all
 *
 *
 * v0.1: odladeno pro brasku
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

