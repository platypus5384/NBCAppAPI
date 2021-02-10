#include "Speaker.h"


Speaker::Speaker( uint8_t input_pin){
  _input_pin = input_pin;
}

void Speaker::setBeepHz( uint8_t hz){
  _hz = hz;
}

void Speaker::dotbeep(){
  tone( _input_pin, _hz*HZ_TIMES_RATE, 10);
}

void Speaker::shortbeep(){
  tone( _input_pin, _hz*HZ_TIMES_RATE, 100);
}

void Speaker::beep(){
  tone( _input_pin, _hz*HZ_TIMES_RATE, 250);
}

void Speaker::longbeep(){
  tone( _input_pin, _hz*HZ_TIMES_RATE, 500);
}

void Speaker::longlongbeep(){
  tone( _input_pin, _hz*HZ_TIMES_RATE, 1000);
}

void Speaker::aleat(){
  
}
