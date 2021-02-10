#include "EEPROM_func.h"



void loadColorWave(AppArg* apparg) {
  Color color;
  Wave wave;
  uint16_t address;
  for (uint8_t i = 0; i < DIGIT_PCS; i++) {
    address = ADDRESS_DIGIT0_COLOR + sizeof(Color) * i;
    EEPROM.get( address,  color);
    apparg->global_color[i] = color;

    address = ADDRESS_DIGIT0_WAVE_H + (sizeof(Wave) * NUM_COLOR_ELEMENT * i);
    EEPROM.get( address,  wave);
    apparg->global_wave[HSV_H][i] = wave;

    address = ADDRESS_DIGIT0_WAVE_S + (sizeof(Wave) * NUM_COLOR_ELEMENT * i);
    EEPROM.get( address,  wave);
    apparg->global_wave[HSV_S][i] = wave;

    address = ADDRESS_DIGIT0_WAVE_V + (sizeof(Wave) * NUM_COLOR_ELEMENT * i);
    EEPROM.get( address,  wave);
    apparg->global_wave[HSV_V][i] = wave;
  }
}



void saveColorWave(AppArg* apparg) {
  uint16_t address;
  for (uint8_t i = 0; i < DIGIT_PCS; i++) {
    address = ADDRESS_DIGIT0_COLOR + sizeof(Color) * i;
    EEPROM.put( address, apparg->global_color[i]);
    address = ADDRESS_DIGIT0_WAVE_H + (sizeof(Wave) * 3 * i);
    EEPROM.put( address, apparg->global_wave[HSV_H][i]);
    address = ADDRESS_DIGIT0_WAVE_S + (sizeof(Wave) * 3 * i);
    EEPROM.put( address, apparg->global_wave[HSV_S][i]);
    address = ADDRESS_DIGIT0_WAVE_V + (sizeof(Wave) * 3 * i);
    EEPROM.put( address, apparg->global_wave[HSV_V][i]);
  }
}





void initColorWave(AppArg* apparg) {
  uint8_t dat = 0;
  EEPROM.get(ADDRESS_DIGIT_SETTING_ENABLE, dat);
  if (dat == EEPROM_INITED)return;
  dat = EEPROM_INITED;
  EEPROM.put(ADDRESS_DIGIT_SETTING_ENABLE, dat);

  tmElements_t adjust_tm;
  adjust_tm.Year   = 0;
  adjust_tm.Month  = 1;
  adjust_tm.Day    = 1;
  adjust_tm.Wday   = 0;
  adjust_tm.Hour   = 0;
  adjust_tm.Minute = 0;
  adjust_tm.Second = 0;
  apparg->rtc->adjust( adjust_tm, 0);

  apparg->use_global = 1;
  for (byte i = 0; i < DIGIT_PCS; i++) {
    apparg->global_color[i].element[HSV_H] = 30;
    apparg->global_color[i].element[HSV_S] = 200;
    apparg->global_color[i].element[HSV_V] = 255;
    apparg->local_color[i].element[HSV_H] = 0;
    apparg->local_color[i].element[HSV_S] = 255;
    apparg->local_color[i].element[HSV_V] = 255;

    apparg->global_wave[HSV_H][i].enable    = 0;
    apparg->global_wave[HSV_H][i].peroid_ms = 0;
    apparg->global_wave[HSV_H][i].amp       = 0;
    apparg->global_wave[HSV_H][i].faze      = 0;
    apparg->global_wave[HSV_S][i].enable    = 0;
    apparg->global_wave[HSV_S][i].peroid_ms = 0;
    apparg->global_wave[HSV_S][i].amp       = 0;
    apparg->global_wave[HSV_S][i].faze      = 0;
    apparg->global_wave[HSV_V][i].enable    = 0;
    apparg->global_wave[HSV_V][i].peroid_ms = 0;
    apparg->global_wave[HSV_V][i].amp       = 0;
    apparg->global_wave[HSV_V][i].faze      = 0;

    apparg->number[i] = 0;
  }
  saveColorWave( apparg);
  Serial.println("EEPROM init!");
}
