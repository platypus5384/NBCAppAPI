#pragma once

#include <Arduino.h>
#include "Wire.h"



#define OPT3001_ADRS 0x44
#define OPT3001_CONFIG 0x01

class AmbientLightSensor {
  private:
  public:
    AmbientLightSensor();
    ~AmbientLightSensor() {};

    virtual uint16_t read();
};
