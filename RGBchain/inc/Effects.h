#ifndef EFFECTS_H_INCLUDED
#define EFFECTS_H_INCLUDED

#include "RGBlibrary.h"

void Eff_EffectLoop();

void Eff_ColorWithFade(RGB_colors_e eColor, uint32_t nDuration_ms);
void Eff_SequentialColorFade(uint32_t nDuration_ms);
void Eff_Rainbow(uint32_t nDuration_ms);
void Eff_Stars(RGB_colors_e color, uint32_t nDuration_ms);
void Eff_Candle_1(RGB_colors_e eColor, uint32_t nDuration_ms);
void Eff_Candle_2(RGB_colors_e eColor, uint32_t nDuration_ms);

void Eff_Test();

#endif /* EFFECTS_H_INCLUDED */
