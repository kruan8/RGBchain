#include "effects.h"

#define EFF_DURATION_1MIN    60000
#define EFF_DURATION_3MIN    60000 * 3
#define EFF_DURATION_5MIN    60000 * 5

uint32_t g_nLeds;

void Eff_EffectLoop()
{
  g_nLeds = RGBlib_GetLedsCount();
  RGBlib_Clear();

  if (!RGBlib_IsDark())
  {
    RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
    RGBlib_Delay_ms(1000);
    return;
  }
  else
  {
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  }

//  while (1)
//  {
////    Eff_Candle_1(c_yellow, EFF_DURATION_5MIN);
////    Eff_Candle_2(c_orange, EFF_DURATION_5MIN);
////    Eff_SequentialColorFade(EFF_DURATION_1MIN);
//    Eff_Rainbow(EFF_DURATION_1MIN);
//
//  }

  uint32_t rnd = RGBlib_Rand(1, 5);
  switch (rnd)
  {
    case  1: Eff_ColorWithFade(RGBlib_GetRandomColor(), EFF_DURATION_5MIN); break;
    case  2: Eff_SequentialColorFade(EFF_DURATION_3MIN); break;
    case  3: Eff_Stars(RGBlib_GetRandomColor(), EFF_DURATION_1MIN); break;
    case  4: Eff_Candle_2(c_yellow, EFF_DURATION_5MIN); break;
    case  5: Eff_Rainbow(EFF_DURATION_1MIN);

    default: break;
  }

  RGBlib_Clear();
  RGBlib_Delay_ms(1000);
}

/**
 * fade in, stabel brihtness, fade out
 * @param eColor: color all leds
 * @param nDuration_ms: stable brightness duration
 */
void Eff_ColorWithFade(RGB_colors_e eColor, uint32_t nDuration_ms)
{
  RGBlib_SetBrightness(0);
  RGBlib_SetColorAll(eColor, 0);
  for (uint8_t nBrightness = 0; nBrightness <= RGBlib_GetBrightnessMax(); nBrightness++)
  {
    RGBlib_SetBrightness(nBrightness);
    RGBlib_Delay_ms(110);
  }

  RGBlib_Delay_ms(nDuration_ms);
  RGBlib_FadeOut(1300);
}

/**
 * sequential fade in random colors, fade out
 * @param nDuration_ms: stable color duration
 */
void Eff_SequentialColorFade(uint32_t nDuration_ms)
{
  for (uint8_t i = 0; i < g_nLeds; i++)
  {
    // search black (free) position
    uint32_t nPos = RGBlib_Rand(0, g_nLeds - 1);
    while (RGBlib_GetColor(nPos) != c_black)
    {
      nPos++;
      nPos %= g_nLeds;
    }

    RGB_colors_e eColor = RGBlib_GetNextColor();
    for (uint8_t b = 0; b < RGBlib_GetBrightnessMax() - 1; b++)
    {
      RGBlib_SetLEDWithBrightnessGamma(nPos, eColor, b);
      RGBlib_Show();
      RGBlib_Delay_ms(1000 / RGBlib_GetBrightnessMax());
    }

    RGBlib_Delay_ms(500);
  }

  RGBlib_Delay_ms(nDuration_ms);
  RGBlib_FadeOut(1500);
}

/**
 * All LEDs changed by rainbow color
 * @param nDuration_ms: effect duration
 */
void Eff_Rainbow(uint32_t nDuration_ms)
{
  RGBlib_Clear();

  uint32_t nEndTime = RGBlib_GetTicks() + nDuration_ms;
  uint32_t nColor = 0;
  while (RGBlib_GetTicks() < nEndTime)
  {
    nColor++;
    nColor &= RGB_COLOR_MASK;
    for (uint16_t i = 0; i < g_nLeds; i++)
    {
      RGBlib_SetLED(i, RGBlib_Wheel(nColor));
    }

    RGBlib_Show();
    RGBlib_Delay_ms(100);
  }

}

/**
 * random fade on/fade in
 * @param color: stars color
 * @param nDuration_ms: effect duration
 */
void Eff_Stars(RGB_colors_e color, uint32_t nDuration_ms)
{
  uint8_t arrBrightness[g_nLeds];
  uint8_t nMaxBrigntness = RGBlib_GetBrightnessMax();
  const uint8_t nCutDown = 0x80;
  uint32_t nStartTime = RGBlib_GetTicks();

  for (uint8_t i = 0; i < g_nLeds; i++)
  {
    arrBrightness[i] = 0;
  }

  while (RGBlib_GetTicks() < nStartTime + nDuration_ms)
  {
    for (uint8_t i = 0; i < g_nLeds; i++)
    {
      uint8_t nBrightness = arrBrightness[i];
      if (nBrightness == 0)
      {
        uint8_t nRnd = RGBlib_Rand(1, 70);
        if (nRnd == 1)
        {
          nBrightness = 1;
        }
      }
      else
      {
        // zmena jasu
        if (nBrightness & nCutDown)
        {
          nBrightness--;
          if (nBrightness == nCutDown)
          {
            nBrightness = 0;
          }
        }
        else
        {
          nBrightness++;
          if (nBrightness == nMaxBrigntness)
          {
            nBrightness |= nCutDown;
          }
        }
      }

      arrBrightness[i] = nBrightness;
      RGBlib_SetLEDWithBrightnessGamma(i, color, nBrightness & ~nCutDown);
    }

    RGBlib_Show();
    RGBlib_Delay_ms(5);
  }
}

/**
 * each led as candle, all same color
 * @param eColor: candle color
 * @param nDuration_ms: run time duration
 */
void Eff_Candle_1(RGB_colors_e eColor, uint32_t nDuration_ms)
{
  const uint8_t pole[] =
  {
    0x77, 0x7B, 0x7D, 0x7B, 0x78, 0xBA, 0x95, 0x53, 0x5E, 0x3E, 0x3E, 0x43, 0x52, 0x35, 0x3E, 0x75,
    0x4B, 0x65, 0x7B, 0x52, 0x63, 0x58, 0x6B, 0x55, 0x62, 0x77, 0x72, 0x87, 0x85, 0x8C, 0x5D, 0x7A,
    0x53, 0x5D, 0x50, 0x62, 0x55, 0x6F, 0x67, 0x58, 0x78, 0x4E, 0x55, 0x95, 0x6B, 0x6D, 0x7D, 0x73,
    0x7D, 0x5B, 0x6B, 0x68, 0x6A, 0x6A, 0x60, 0x6B, 0x77, 0x77, 0x98, 0x7A, 0x87, 0x60, 0x5B, 0x6B,
    0x53, 0x4A, 0x53, 0x68, 0x45, 0x3B, 0x65, 0x67, 0x9C, 0x60, 0x67, 0x53, 0x73, 0x75, 0x63, 0x8A,
    0x7F, 0x83, 0x88, 0x80, 0x63, 0x58, 0x58, 0x6B, 0x7A, 0x78, 0x7B, 0x83, 0x8A, 0x87, 0x8A, 0x85,
    0x83, 0x88, 0x8A, 0x8A, 0x8A, 0x8A, 0x8A, 0x8C, 0x8A, 0x8A, 0x8A, 0x8A, 0x8A, 0x88, 0x83, 0x7F,
    0x7D, 0x7B, 0x7A, 0x78, 0x77, 0x75, 0x70, 0x70, 0x72, 0x70, 0x70, 0x4D, 0x41, 0x6D, 0x68, 0x60,
    0x35, 0x35, 0x3D, 0x3B, 0x41, 0x45, 0x52, 0x5E, 0x41, 0x53, 0x5D, 0x60, 0x65, 0x6A, 0x50, 0x48,
    0x4B, 0x4E, 0x35, 0x35, 0x31, 0x33, 0x33, 0x36, 0x3B, 0x40, 0x50, 0x4E, 0x52, 0x5D, 0x60, 0x53,
    0x56, 0x4B, 0x35, 0x2D, 0x2E, 0x2E, 0x35, 0x38, 0x38, 0x39, 0x3B, 0x38, 0x31, 0x58, 0x40, 0x60,
    0x4D, 0x50, 0x5A, 0x5D, 0x43, 0x40, 0x53, 0x58, 0x5A, 0x55, 0x4E, 0x31, 0x31, 0x2B, 0x2E, 0x33,
    0x31, 0x36, 0x35, 0x36, 0x38, 0x39, 0x39, 0x38, 0x40, 0x4A, 0x41, 0x3B, 0x50, 0x62, 0x40, 0x36,
    0x29, 0x2D, 0x45, 0x5E, 0x5D, 0x52, 0x3E, 0x33, 0x3B, 0x43, 0x35, 0x45, 0x38, 0x35, 0x31, 0x33,
    0x36, 0x36, 0x39, 0x36, 0x38, 0x3B, 0x41, 0x36, 0x36, 0x30, 0x39, 0x33, 0x2B, 0x29, 0x33, 0x5A,
    0x63, 0x56, 0x41, 0x3D, 0x50, 0x52, 0x55, 0x60, 0x65, 0x55, 0x3B, 0x30, 0x2E, 0x30, 0x3B, 0x4E,
    0x36, 0x2E, 0x2B, 0x3B, 0x39, 0x3D, 0x4A, 0x50, 0x3D, 0x45, 0x58, 0x4E, 0x4B, 0x4E, 0x4A, 0x45,
    0x58, 0x4B, 0x55, 0x5D, 0x5B, 0x56, 0x58, 0x5E, 0x60, 0x77, 0x5E, 0x38, 0x5A, 0x52, 0x46, 0x4B,
    0x50, 0x4A, 0x4A, 0x35, 0x4E, 0x41, 0x2E, 0x36, 0x36, 0x38, 0x52, 0x4B, 0x46, 0x3B, 0x33, 0x40,
    0x4E, 0x60, 0x5A, 0x50, 0x4D, 0x43, 0x4A, 0x50, 0x4B, 0x48, 0x40, 0x3D, 0x40, 0x46, 0x52, 0x5B,
    0x62, 0x63, 0x63, 0x5B, 0x52, 0x46, 0x5B, 0x43, 0x55, 0x45, 0x26, 0x35, 0x3B, 0x5B, 0x43, 0x4D,
    0x40, 0x56, 0x58, 0x5A, 0x5D, 0x50, 0x46, 0x45, 0x45, 0x41, 0x3B, 0x43, 0x72, 0x87, 0x90, 0x8A,
    0x8F, 0x97, 0x9D, 0x95, 0x73, 0x65, 0x6B, 0x4D, 0x46, 0x45, 0x55, 0x55, 0x41, 0x56, 0x55, 0x55,
    0x56, 0x5A, 0x5A, 0x5B, 0x5E, 0x56, 0x62, 0x55, 0x65, 0x58, 0x5A, 0x62, 0x68, 0x6D, 0x6D, 0x6B,
    0x68, 0x6A, 0x6F, 0x65, 0x6D, 0x31, 0x6F, 0x55, 0x48, 0x50, 0x55, 0x67, 0x5A, 0x41, 0x55, 0x5E,
    0x60, 0x65, 0x68, 0x68, 0x63, 0x60, 0x6A, 0x60, 0x67, 0x6A, 0x7F, 0x83, 0x8C, 0x87, 0x88, 0x92,
    0x8D, 0x8F, 0x88, 0x8C, 0x8C, 0x85, 0x82, 0x6A, 0x4E, 0x35, 0x23, 0x11, 0x19, 0x43, 0x3B, 0x41,
    0x67, 0x4A, 0x4A, 0x3B, 0x2E, 0x30, 0x45, 0x41, 0x4A, 0x58, 0x48, 0x70, 0x5B, 0x6D, 0x72, 0x62,
    0x75, 0x67, 0x56, 0x5A, 0x5E, 0x55, 0x4D, 0x77, 0x53, 0x2D, 0x36, 0x41, 0x5D, 0x55, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x3E, 0x41, 0x5E, 0x82, 0x92, 0x88, 0x88, 0x90, 0x94, 0x88, 0x85, 0x7B, 0x63,
    0x55, 0x53, 0x56, 0x55, 0x50, 0x53, 0x55, 0x53, 0x34, 0x31, 0x3A, 0x4E, 0x5F, 0x41, 0x60, 0x3E,
    0x3E, 0x28, 0x41, 0x6E
  };

  uint16_t nSize = sizeof (pole);
  uint16_t arrLedIndex[g_nLeds];
  for (uint8_t i = 0; i < g_nLeds; i++)
  {
    arrLedIndex[i] = RGBlib_Rand(0, nSize - 1);
  }

  uint32_t nEndTime = RGBlib_GetTicks() + nDuration_ms;
  while (RGBlib_GetTicks() < nEndTime)
  {
    for (uint8_t i = 0; i < g_nLeds; i++)
    {
      uint16_t nBrightness = pole[arrLedIndex[i]] + 30;
      if (nBrightness > 255)
      {
        nBrightness = 255;
      }

      RGBlib_SetLEDWithBrightness(i, eColor, nBrightness);
//      RGBlib_SetLEDWithBrightness(i, eColor, nBrightness);
      arrLedIndex[i]++;
      arrLedIndex[i] %= nSize;
    }

    RGBlib_Show();
    RGBlib_Delay_ms(80);
  }
}

void Eff_Candle_2(RGB_colors_e eColor, uint32_t nDuration_ms)
{
  //  Flicker, based on our initial RGB values
  for(uint8_t i = 0; i < g_nLeds; i++)
  {
    if (RGBlib_Rand(1, 2))
    {
      int r = RGBlib_GetR(eColor) - RGBlib_Rand(1, 40);
      int g = RGBlib_GetG(eColor) - RGBlib_Rand(1, 30);
      int b = RGBlib_GetB(eColor) - RGBlib_Rand(1 ,10);

      // remove negative values
      g = MAX(g, 0);
      r = MAX(r, 0);
      b = MAX(b, 0);

      RGBlib_SetLED(i, RGBlib_GetColorFromRGB(r, g, b));
    }
  }

  RGBlib_Show();

  //  Adjust the delay here, if you'd like.  Right now, it randomizes the
  //  color switch delay to give a sense of realism
  RGBlib_Delay_ms(RGBlib_Rand(50, 100));
}

void Eff_Test()
{
  RGBlib_Delay_ms(300);

	RGBlib_SetColorAll(c_red, 1000);
	RGBlib_SetColorAll(c_green, 1000);
	RGBlib_SetColorAll(c_blue, 1000);
	RGBlib_Clear();
	RGBlib_Delay_ms(1000);
}
