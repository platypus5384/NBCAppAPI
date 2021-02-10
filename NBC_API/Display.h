#pragma once

#include <Arduino.h>
#include <FastLED.h>
#include "Digit.h"


#define DATA_PIN    4
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB



typedef enum {
  DIGIT1,
  DIGIT2,
  DIGIT3,
  DIGIT4,
  DIGIT5,
  DIGIT6,
  DIGIT_PCS,
};

#define LED_PCS 60


class  LedString{
  protected:
    Digit* _digit[DIGIT_PCS];
    uint16_t _management_offset[DIGIT_PCS];
    
    void _init();
  public:
    CRGB leds[LED_PCS];
    
    LedString();
    void showLEDs();
    
    void setDigitNumber( uint8_t digit_number, uint8_t number);
    void setDigitColor( uint8_t digit_number, Color color);
    void setDigitColor( uint8_t digit_number, uint8_t color_element1, uint8_t color_element2, uint8_t color_element3);
    void setDigitWave( uint8_t digit_number, COLOR_ELEMENT element, Wave wave);
    void virtual calc( uint32_t time_ms);

    Wave getDigitWave(uint8_t digit_number, COLOR_ELEMENT element){return _digit[digit_number]->getWave(element);};
    Color getDigitColor(uint8_t digit_number){return _digit[digit_number]->getColor();};
};




class LedStringNBClock6 : public LedString {
  private:
  
  public:
    LedStringNBClock6();
};
