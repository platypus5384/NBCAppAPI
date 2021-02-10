#include "Digit.h"


Digit::Digit( uint8_t led_pcs) {
  _drive_info.enable = 1;
  _drive_info.led_pcs = led_pcs;
  _drive_info.drive_number = 0;
}

uint8_t Digit::set( uint8_t number) {
  int8_t result;
  if ( 0 <= number && number < _drive_info.led_pcs) {
    result = 0;
    _drive_info.number = number;
  } else {
    result = 1;
    _drive_info.number = 0;
  }
  return result;
}

void Digit::setColor( uint8_t color_element1, uint8_t color_element2, uint8_t color_element3) {
  _color.element[0] = color_element1;
  _color.element[1] = color_element2;
  _color.element[2] = color_element3;
}


void Digit::calc( uint32_t time_ms) {
  float t, hz;
  int16_t hue = _color.element[0];
  int16_t sat = _color.element[1];
  int16_t val = _color.element[2];

  if (_wave[HSV_H].enable == 1) {
    if (_wave[HSV_H].peroid_ms != 0) {
      t = (float)(time_ms%_wave[HSV_H].peroid_ms + _wave[HSV_H].faze) / 1.0 ;
      hue = _color.element[0] + (int16_t)(t / (float)_wave[HSV_H].peroid_ms * 255.0);
      hue %= 256;
    }
  }
  if (_wave[HSV_S].enable == 1) {
    t = (float)(time_ms%_wave[HSV_S].peroid_ms + _wave[HSV_S].faze) / 1000.0;
    hz = 1000.0 / (float)(_wave[HSV_S].peroid_ms);
    sat = _color.element[1] + (int16_t)(sin( 2 * PI * t * hz) * _wave[HSV_S].amp);
    sat = max( sat,   0);
    sat = min( sat, 255);
  }
  if (_wave[HSV_V].enable == 1) {
    t = (float)(time_ms%_wave[HSV_V].peroid_ms + _wave[HSV_V].faze) / 1000.0;
    hz = 1000.0 / (float)(_wave[HSV_V].peroid_ms);
    val = _color.element[2] + (int16_t)(sin( 2 * PI * t * hz) * _wave[HSV_V].amp);
    val = max( val,   0);
    val = min( val, 255);
  }

  _drive_color.element[0] = hue;
  _drive_color.element[1] = sat;
  _drive_color.element[2] = val;
  _drive_info.drive_number = _calcNumber();
}


/* ------------------------------------------------- */
uint8_t _DigitNBClockNormal10_dict( uint8_t number) {
  const uint8_t assign_even[10] = { 1, 0, 2, 3, 5, 4, 6, 7, 9, 8};
  return assign_even[ number];
}

int8_t DigitNBClockNormal10::_calcNumber() {
  return _DigitNBClockNormal10_dict( _drive_info.number);
}


/* ------------------------------------------------- */
int8_t _DigitNBClockInverse10_dict( uint8_t number) {
  const uint8_t assign_odd[10] = { 9, 8, 6, 7, 5, 4, 2, 3, 1, 0};
  return assign_odd[ number];
}

int8_t DigitNBClockInverse10::_calcNumber() {
  return _DigitNBClockInverse10_dict( _drive_info.number);
}
