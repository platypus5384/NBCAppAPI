#pragma once

#include <Arduino.h>



#define TO_MSEC_FACTOR 100
#define FROM_MSEC_FACTOR 10

typedef enum {
  HSV_H,
  HSV_S,
  HSV_V,
  NUM_COLOR_ELEMENT,
}COLOR_ELEMENT;

typedef struct{
  uint8_t element[ NUM_COLOR_ELEMENT];
}Color;

typedef struct{
  bool enable : 1;
  uint16_t peroid_ms : 15;
  uint8_t amp : 8;
  uint16_t faze : 15;
}Wave;


typedef struct{
    bool enable : 1;
    uint8_t number : 5;
    uint8_t led_pcs : 5;
    uint8_t drive_number : 5;
}DigitDriveInfo;


/* ------------------------------------------------- */
class Digit {
  protected:
    DigitDriveInfo _drive_info;
    Wave    _wave[NUM_COLOR_ELEMENT];
    Color   _color;
    Color _drive_color;
    int8_t virtual _calcNumber();
    
  public:
    Digit( uint8_t led_pcs);

    uint8_t set( uint8_t number);
    void setColor( Color color){ _color = color;};
    void setWave(Wave wave, COLOR_ELEMENT element){ _wave[element] = wave;};
    void setHueWave( Wave wave){ _wave[HSV_H] = wave;};
    void setSatWave( Wave wave){ _wave[HSV_S] = wave;};
    void setValWave( Wave wave){ _wave[HSV_V] = wave;};
    void setColor( uint8_t color_element1, uint8_t color_element2, uint8_t color_element3);
    
    uint8_t getDriveNumber(){return _drive_info.drive_number;};
    Color   getDriveColor(){ return _drive_color;};
    uint8_t getEnable(){return _drive_info.enable;};
    uint8_t getLedPcs(){return _drive_info.led_pcs;};
    Wave getWave(COLOR_ELEMENT element){ return _wave[element];};
    Color getColor(){ return _color;};

    void calc( uint32_t time_ms);
};



class DigitNBClockNormal10 : public Digit {
  private:
    int8_t virtual _calcNumber();
  public:
    DigitNBClockNormal10() : Digit( 10){};
};



class DigitNBClockInverse10 : public Digit {
  private:
    int8_t virtual _calcNumber();
  public:
    DigitNBClockInverse10() : Digit( 10){};
};
