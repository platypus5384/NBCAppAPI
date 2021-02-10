#include "Display.h"



LedString::LedString() {
  FastLED.setBrightness( 250);
  //  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(_leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
}

void LedString::_init() {
  int i;
  _management_offset[0] = 0;
  for (i = 1; i < DIGIT_PCS; i++) {
    _management_offset[i] = _management_offset[i - 1] + _digit[i - 1]->getLedPcs();
  }
}


void LedString::showLEDs() {
  FastLED.show();
}


void LedString::setDigitNumber( uint8_t digit_number, uint8_t number) {
  _digit[digit_number]->set( number);
}

void LedString::setDigitColor( uint8_t digit_number, Color color){
  _digit[digit_number]->setColor( color);
}

void LedString::setDigitColor( uint8_t digit_number, uint8_t color_element1, uint8_t color_element2, uint8_t color_element3) {
  _digit[digit_number]->setColor( color_element1, color_element2, color_element3);
}

void LedString::setDigitWave( uint8_t digit_number, COLOR_ELEMENT element, Wave wave){
  _digit[digit_number]->setWave( wave, element);
}


void LedString::calc( uint32_t time_ms) {
  uint8_t digit_i, led_i;
  uint16_t led_number;
  Color drive_color;

  for (digit_i = 0; digit_i < DIGIT_PCS; digit_i++) {
    for (led_i = 0; led_i < _digit[digit_i]->getLedPcs(); led_i++) {
      led_number = _management_offset[digit_i] + led_i;
      leds[led_number] = CHSV( 0, 0, 0);
    }
    _digit[digit_i]->calc( time_ms);
    led_number = _management_offset[digit_i] + _digit[digit_i]->getDriveNumber();
    drive_color = _digit[digit_i]->getDriveColor();
    leds[led_number] = CHSV( drive_color.element[0], drive_color.element[1], drive_color.element[2]);
  }
}

/* ------------------------------------------------- */

LedStringNBClock6::LedStringNBClock6() {
  _digit[0] = new DigitNBClockNormal10 ();
  _digit[1] = new DigitNBClockInverse10();
  _digit[2] = new DigitNBClockNormal10 ();
  _digit[3] = new DigitNBClockInverse10();
  _digit[4] = new DigitNBClockNormal10 ();
  _digit[5] = new DigitNBClockInverse10();

  _init();
}
