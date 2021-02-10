#pragma once

#include <Arduino.h>
#include "Common.h"
#include "StainsGate.h"
#include "AppArg.h"


void StainsGateEffect(AppArg* apparg)
{
  /*----- StainsGate Animation -----*/
  if (apparg->stainsgate_flag.enable == true) {
    if (apparg->stainsgate_flag.digit0 == true)apparg->number[0] = random(0, 10);
    if (apparg->stainsgate_flag.digit1 == true)apparg->number[1] = random(0, 10);
    if (apparg->stainsgate_flag.digit2 == true)apparg->number[2] = random(0, 10);
    if (apparg->stainsgate_flag.digit3 == true)apparg->number[3] = random(0, 10);
    if (apparg->stainsgate_flag.digit4 == true)apparg->number[4] = random(0, 10);
    if (apparg->stainsgate_flag.digit5 == true)apparg->number[5] = random(0, 10);
  }
}
