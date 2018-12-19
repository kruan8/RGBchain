/*
 * RGBlibrary.h
 *
 *  Created on: 11. 11. 2015
 *      Author: priesolv
 */

#ifndef RGBLIBRARY_H_
#define RGBLIBRARY_H_

#include "stm32f0xx.h"
#include <stdbool.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define RGB_COLOR_MASK   0xFFFFFF

typedef enum
{
  c_black      = 0x000000,
  c_red        = 0xFF0000,
  c_green      = 0x00FF00,
  c_blue       = 0x0000FF,
  c_yellow     = 0x707000,
  c_white      = 0xFFFFFF,
  c_white_dark = 0x505050,
  c_violet     = 0x6400FF,
  c_x          = 0x007070,
  c_tyrkis     = 0x0064FF,  // svetele modra
  c_orange     = 0xE26505,  // { 226, 101, 5}
}RGB_colors_e;

typedef enum
{
  light = 0,
  dark,
}light_mode_e;

void RGBlib_Init();

void RGBlib_ColorWipe(RGB_colors_e color, uint16_t wait_ms, bool bClear);
void RGBlib_ColorWipeCenter(RGB_colors_e color, uint16_t wait_ms);
void RGBlib_Scanner(RGB_colors_e color, uint16_t wait_ms, bool bReturn);
void RGBlib_FillWithSpace(RGB_colors_e color, uint16_t nSpace, uint16_t nWait_ms);
uint32_t RGBlib_Wheel(uint8_t nWheelPos);
uint32_t RGBlib_Rand(uint32_t nMin, uint32_t nMax);
RGB_colors_e RGBlib_GetRandomColor();
RGB_colors_e RGBlib_GetNextColor();

void RGBlib_RotateRight(uint32_t nDelay_ms);
void RGBlib_RotateLeft(uint32_t nDelay_ms);

void RGBlib_WaitAndClear(uint16_t wait_ms);
void RGBlib_Clear(void);

void RGBlib_SetLED(uint8_t position, RGB_colors_e color);
void RGBlib_SetLEDWithBrightnessGamma(uint8_t position, RGB_colors_e eColor, uint8_t nBrightness);
void RGBlib_SetLEDWithBrightness(uint8_t position, RGB_colors_e eColor, uint8_t nBrightness);
void RGBlib_SetColorAll(RGB_colors_e color, uint16_t wait_ms);

uint32_t RGBlib_GetColor(uint8_t position);
uint32_t RGBlib_GetColorFromRGB(uint8_t r, uint8_t g, uint8_t b);
uint8_t RGBlib_GetR(uint32_t nColor);
uint8_t RGBlib_GetG(uint32_t nColor);
uint8_t RGBlib_GetB(uint32_t nColor);

void RGBlib_SetBrightness(uint8_t nBrightness);
uint8_t RGBlib_GetBrightness();
uint8_t RGBlib_GetBrightnessMax();
uint8_t RGBlib_GetBrightnessValue(uint8_t nBrightness);

void RGBlib_FadeOut(uint32_t nDuration_ms);
uint16_t RGBlib_GetLedsCount();

void RGBlib_Show();
void RGBlib_Delay_ms(uint32_t delay_ms);
uint32_t RGBlib_GetTicks(void);

bool RGBlib_IsDark(void);

#endif /* RGBLIBRARY_H_ */
