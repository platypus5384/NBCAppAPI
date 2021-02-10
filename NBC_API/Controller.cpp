#include"Controller.h"

Controller::Controller(){
  _button_pcs = BUTTON_PCS;
  mButton[BT_1]   = new Button( BT_1_PIN);
  mButton[BT_2]   = new Button( BT_2_PIN);
  mButton[BT_3]   = new Button( BT_3_PIN);
  mButton[BT_EXT] = new Button( BT_EXT_PIN);
}



int8_t Controller::update(uint32_t time_ms){
  uint8_t i;
  for (i=0; i<_button_pcs; i++){
    mButton[i]->update(time_ms);
  }
  return 1;
}


uint8_t Controller::state(uint8_t bt_number){
  if (bt_number<0 && _button_pcs<= bt_number)return -1;
  return mButton[bt_number]->state();
}

uint8_t Controller::stateRepeat(uint8_t bt_number){
  if (bt_number<0 && _button_pcs<= bt_number)return -1;
  return mButton[bt_number]->stateRepeat();
}
