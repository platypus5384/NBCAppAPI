#pragma once

#include "Arduino.h"
#include "Common.h"

#define HZ_TIMES_RATE  10



class Speaker {
  private:
    uint8_t _input_pin;
    uint8_t _hz;
    
  public:
    Speaker(uint8_t input_pin);
    void setBeepHz(uint8_t hz);

    void setVolume( uint8_t value);

    void dotbeep();
    void shortbeep();
    void beep();
    void longbeep();
    void longlongbeep();
    void aleat();
};
