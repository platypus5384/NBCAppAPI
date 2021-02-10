#pragma once

#include "Common.h"
#include "AmbientLightSensor.h"
#include "Controller.h"
#include "Display.h"
#include "RTC.h"
#include "Speaker.h"
#include "StainsGate.h"
#include "TimeWatch.h"


typedef struct {
  bool use_global;
  uint8_t number[DIGIT_PCS];
  uint32_t time_ms;
  uint16_t count;
  
  Color global_color[DIGIT_PCS];
  Color local_color[DIGIT_PCS];
  Wave  global_wave[NUM_COLOR_ELEMENT][DIGIT_PCS];
  Wave  local_wave[NUM_COLOR_ELEMENT][DIGIT_PCS];
  StainsGateFlag stainsgate_flag;

  RTC* rtc;
  Controller* controller;
  TimeWatch* timewatch;
  Speaker* speaker;
}AppArg;
