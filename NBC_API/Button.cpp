#include "Button.h"


Button::Button( uint8_t pin) {
  _input_pin = pin;
  _flag.ispress = digitalRead(_input_pin);
}


int8_t Button::update(uint32_t time_ms) {
  uint32_t elapse_time;
  _state = NONE;

  elapse_time = CalcElapseTime(time_ms, _b_time_ms);
  _flag.b_ispress = _flag.ispress;
  _flag.ispress = digitalRead(_input_pin);

  if (_flag.b_ispress == BT_RELEASE && _flag.ispress == BT_PRESS) {
    _state        = PRESS;
    _state_repeat = PRESS_REPEAT;
    _b_time_ms = time_ms;
    _hold_time = 0;
    _flag.hold_flag = false;
    _flag.hold_long_flag = false;
  } else if (_flag.b_ispress == BT_PRESS && _flag.ispress == BT_PRESS) {
    if (elapse_time > 0xFFFF) {
      _hold_time = 0xFFFF;
    } else {
      _hold_time = elapse_time;
    }
    if (_hold_time >= HOLD_LONG_TIME_MS  &&  _flag.hold_long_flag == false) {
      _state        = HOLD_LONG;
      _state_repeat = HOLD_REPEAT;
      _flag.hold_long_flag = true;
    } else if (_hold_time >= HOLD_TIME_MS  &&  _flag.hold_flag == false) {
      _state        = HOLD;
      _state_repeat = HOLD_REPEAT;
      _flag.hold_flag = true;
    }
  } else if (_flag.b_ispress == BT_PRESS && _flag.ispress == BT_RELEASE) {
    if (_hold_time <= HOLD_TIME_MS) {
      _state        = RELEASE;
      _state_repeat = RELEASE_REPEAT;
    } else {
      _state        = HOLD_RELEASE;
      _state_repeat = RELEASE_REPEAT;
    }
  }
  return 0;
}


BT_STATE Button::state() {
  return _state;
}


BT_STATE Button::stateRepeat() {
  return _state_repeat;
}
