#pragma once

#include <Arduino.h>
#include "Button.h"


#define BT_1_PIN    A0
#define BT_2_PIN    A1
#define BT_3_PIN    A2
#define BT_EXT_PIN  A3

typedef enum{
  BT_1,
  BT_2,
  BT_3,
  BT_EXT,
  BUTTON_PCS,
};


class Controller {
  protected:
    Button *mButton[BUTTON_PCS];
    uint8_t _button_pcs;
  public:
    Controller();
    int8_t update(uint32_t time_ms);
    uint8_t state( uint8_t bt_number);
    uint8_t stateRepeat( uint8_t bt_number);
};
