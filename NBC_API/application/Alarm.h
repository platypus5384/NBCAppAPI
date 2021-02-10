#pragma once

#include <Arduino.h>
#include "NBClockApp.h"
#include "func.h"


/*
アプリ名:アラーム

アラーム設定が可能
H,Mをそれぞれ設定可能

HH/MM/SS


ボタン1:時間の変更
ボタン2:分の変更
ボタン3:決定 
*/


class Alarm : public NBClockApp{
	private:
	uint8_t _hour;
	uint8_t _minute;
	
	public:
	Alarm() : NBClockApp(){};
	~Alarm();
	int8_t app_setup(AppArg *apparg);
	int8_t app_loop(AppArg *apparg);
};


Alarm::~Alarm(){
}


int8_t Alarm::app_setup(AppArg *apparg){
	apparg->use_global = 0;
	local_init(apparg);
	
	uint8_t i;
	
	_hour   = apparg->rtc->getAlarm().hour;
	_minute = apparg->rtc->getAlarm().minute;
	
	for (i=0;i<DIGIT_PCS;i++){
		apparg->local_color[i].element[HSV_H] = 0;
		apparg->local_color[i].element[HSV_S] = 255;
		apparg->local_color[i].element[HSV_V] = apparg->global_color[i].element[HSV_V];
	}
}


int8_t Alarm::app_loop(AppArg *apparg){
  uint8_t num1, num2, num3;
  uint8_t i;
  uint8_t sat;
  uint8_t bt1, bt2, bt3, bt1rp, bt2rp, bt3rp;
  
  
  bt1   = apparg->controller->state(BT_1);
  bt2   = apparg->controller->state(BT_2);
  bt3   = apparg->controller->state(BT_3);
  bt1rp = apparg->controller->stateRepeat(BT_1);
  bt2rp = apparg->controller->stateRepeat(BT_2);
  bt3rp = apparg->controller->stateRepeat(BT_3);
  
  
  if ( bt1==PRESS   ||   (bt1rp==HOLD_REPEAT && (apparg->count&0x0F)==0)  ){
	  _hour++;
	  apparg->speaker->dotbeep();
  }
  if ( bt2==PRESS   ||   (bt2rp==HOLD_REPEAT && (apparg->count&0x07)==0)  ){
	  _minute++;
	  apparg->speaker->dotbeep();
  }
  
  if (_hour > 23)_hour = 0;
  if (_minute > 59)_minute = 0;
  
  if (bt3 == PRESS){
	  if (apparg->rtc->getAlarm().enable==0){
		apparg->rtc->setAlarm(1, _hour, _minute);
	  }else{
		apparg->rtc->setAlarm(0, _hour, _minute);
	  }
  }
  
  sat = (apparg->rtc->getAlarm().enable==0) ? 255 : 0;
  for (i=0; i<DIGIT_PCS; i++){
	apparg->local_color[i].element[HSV_S] = sat;
  }
  
  num1 = _hour;
  num2 = _minute;
  num3 = 0;
  apparg->number[5] = num1/10;
  apparg->number[4] = num1%10;
  apparg->number[3] = num2/10;
  apparg->number[2] = num2%10;
  apparg->number[1] = num3/10;
  apparg->number[0] = num3%10;
  return 0;
}