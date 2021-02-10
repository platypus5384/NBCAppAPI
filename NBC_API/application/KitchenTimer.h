#pragma once

#include <Arduino.h>
#include "NBClockApp.h"
#include "func.h"


/*
アプリ名:ストップウォッチ

ストップウォッチ

精度は20ppm(日差±2秒)
時計の精度は5ppm

分分/秒秒/ミリ秒ミリ秒

ボタン1:ストップ・スタート
ボタン2:ストップ・リセット
ボタン3:分/秒を切り替え
*/


class KitchenTimer : public NBClockApp{
	private:
	uint8_t _minute;
	uint8_t _sec;
	
	public:
	KitchenTimer() : NBClockApp(){};
	~KitchenTimer();
	int8_t app_setup(AppArg *apparg);
	int8_t app_loop(AppArg *apparg);
};

KitchenTimer::~KitchenTimer(){
}



int8_t KitchenTimer::app_setup(AppArg *apparg){
  apparg->use_global = 1;
  _minute = 0;
  _sec = 0;
}


int8_t KitchenTimer::app_loop(AppArg *apparg){
  uint8_t num1, num2, num3;
  uint8_t i;
  int32_t elapse_time_ms;
  uint32_t now_time_ms;
  uint8_t bt1, bt2, bt3, bt1rp, bt2rp, bt3rp;
  
  now_time_ms = apparg->timewatch->get() / 1000;
  
  
  bt1   = apparg->controller->state(BT_1);
  bt2   = apparg->controller->state(BT_2);
  bt3   = apparg->controller->state(BT_3);
  bt1rp = apparg->controller->stateRepeat(BT_1);
  bt2rp = apparg->controller->stateRepeat(BT_2);
  bt3rp = apparg->controller->stateRepeat(BT_3);
  
  
  if ( bt1==PRESS   ||   (bt1rp==HOLD_REPEAT && (apparg->count&0x07)==0)  ){
	if (apparg->timewatch->is_pause() == 1){
		elapse_time_ms = (int32_t)(_minute)*60000 +(int32_t)(_sec)*1000 - now_time_ms;
		_minute = (elapse_time_ms/60000)% 100;
		_sec = (elapse_time_ms/1000) % 60;
		_minute++;
		apparg->timewatch->reset();
	}else{
	  apparg->timewatch->pause(true);
	}
	apparg->speaker->dotbeep();
  }
  
  if ( bt2==PRESS   ||   (bt2rp==HOLD_REPEAT && (apparg->count&0x07)==0)  ){
	if (apparg->timewatch->is_pause() == 1){
		elapse_time_ms = (int32_t)(_minute)*60000 +(int32_t)(_sec)*1000 - now_time_ms;
		_minute = (elapse_time_ms/60000)% 100;
		_sec = (elapse_time_ms/1000) % 60;
		_sec++;
		apparg->timewatch->reset();
	}else{
		apparg->timewatch->pause(true);
	}
	apparg->speaker->dotbeep();
  }
  
  if ( bt3==PRESS){
	  apparg->timewatch->pause( apparg->timewatch->is_pause()^1);
	  apparg->speaker->dotbeep();
  }
  
  if ((bt1rp==PRESS_REPEAT || bt1rp==HOLD_REPEAT) && (bt2rp==PRESS_REPEAT || bt2rp==HOLD_REPEAT)){
	  _minute = 0;
	  _sec = 0;
	  apparg->timewatch->reset();
	  apparg->speaker->shortbeep();
  }
  
  
  if (_minute > 60)_minute = 60;
  if (_sec > 59)_sec = 0;
  elapse_time_ms = (int32_t)(_minute)*60000 +(int32_t)(_sec)*1000 - now_time_ms;
  if (elapse_time_ms < 0){
	  elapse_time_ms=0;
	  apparg->rtc->setAlarmResult();
	  apparg->timewatch->pause( 1);
  }
  num1 = (elapse_time_ms/60000)% 100;
  num2 = (elapse_time_ms/1000) % 60;
  num3 = (elapse_time_ms/10) % 100;
  
  apparg->number[5] = num1/10;
  apparg->number[4] = num1%10;
  apparg->number[3] = num2/10;
  apparg->number[2] = num2%10;
  apparg->number[1] = num3/10;
  apparg->number[0] = num3%10;
}