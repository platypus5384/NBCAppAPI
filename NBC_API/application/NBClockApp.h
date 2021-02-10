#pragma once

#include <Arduino.h>
#include "../AppArg.h"




class NBClockApp {
  public:
    NBClockApp(){};
    virtual ~NBClockApp(){};
    
    int8_t virtual app_setup(AppArg *apparg){};
    int8_t virtual app_loop( AppArg *apparg){};
    int8_t virtual app_destroy( AppArg *apparg){};
};
