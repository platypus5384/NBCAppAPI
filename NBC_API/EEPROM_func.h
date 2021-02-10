#pragma once

#include <Arduino.h>
#include <EEPROM.h>

#include "Display.h"
#include "AppArg.h"



#define EEPROM_INITED 2



typedef enum{
  ADDRESS_DIGIT_SETTING_ENABLE = 0,
  ADDRESS_DIGIT0_COLOR =   1,
  ADDRESS_DIGIT1_COLOR =   4,
  ADDRESS_DIGIT2_COLOR =   7,
  ADDRESS_DIGIT3_COLOR =  10,
  ADDRESS_DIGIT4_COLOR =  13,
  ADDRESS_DIGIT5_COLOR =  16,
  ADDRESS_DIGIT0_WAVE_H  =  20,
  ADDRESS_DIGIT0_WAVE_S  =  25,
  ADDRESS_DIGIT0_WAVE_V  =  30,
  ADDRESS_DIGIT1_WAVE_H  =  35,
  ADDRESS_DIGIT1_WAVE_S  =  40,
  ADDRESS_DIGIT1_WAVE_V  =  45,
  ADDRESS_DIGIT2_WAVE_H  =  50,
  ADDRESS_DIGIT2_WAVE_S  =  55,
  ADDRESS_DIGIT2_WAVE_V  =  60,
  ADDRESS_DIGIT3_WAVE_H  =  65,
  ADDRESS_DIGIT3_WAVE_S  =  70,
  ADDRESS_DIGIT3_WAVE_V  =  75,
  ADDRESS_DIGIT4_WAVE_H  =  80,
  ADDRESS_DIGIT4_WAVE_S  =  85,
  ADDRESS_DIGIT4_WAVE_V  =  90,
  ADDRESS_DIGIT5_WAVE_H  =  95,
  ADDRESS_DIGIT5_WAVE_S  =  100,
  ADDRESS_DIGIT5_WAVE_V  =  105,
}EEPROM_ADDRESS_NAME;


void loadColorWave(AppArg* apparg);
void saveColorWave(AppArg* apparg);
void initColorWave(AppArg* apparg);