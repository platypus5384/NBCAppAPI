#pragma once

#include <Arduino.h>
#include "Common.h"


#define BT_PRESS 0
#define BT_RELEASE  1

#define HOLD_TIME_MS      750
#define HOLD_LONG_TIME_MS 3000


typedef enum{
  NONE,
  RELEASE,
  RELEASE_REPEAT,
  PRESS,
  PRESS_REPEAT,
  HOLD,
  HOLD_REPEAT,
  HOLD_LONG,
  HOLD_LONG_REPEAT,
  HOLD_RELEASE,
}BT_STATE;


typedef struct {
  bool b_ispress      : 1;
  bool ispress        : 1;
  bool hold_flag      : 1;
  bool hold_long_flag : 1;
}BtFlag;


class Button {
  protected:
    uint8_t _input_pin;
    BtFlag _flag;
    uint32_t _b_time_ms;
    uint16_t _hold_time;
    BT_STATE _state;
    BT_STATE _state_repeat;

  public:
    Button(uint8_t pin);

    BT_STATE state();
    BT_STATE stateRepeat();
    bool isPress();
    bool isHold();
    bool isHoldLong();
    bool isPressRepeat();
    bool isHoldRepeat();
    int8_t virtual update(uint32_t time_ms);
};
