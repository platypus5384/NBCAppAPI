#pragma once

#include <Arduino.h>
#include "NBClockApp.h"
#include "func.h"



/*
アプリ名:時計合わせ

時計合わせ

HH/MM/SS


ボタン1:時間の変更
ボタン2:分の変更
ボタン3:決定
*/


class AdjustClock : public NBClockApp{
	private:
	tmElements_t _adjust_tm;
	
	public:
	AdjustClock() : NBClockApp(){};
	~AdjustClock();
	int8_t app_setup(AppArg *apparg);
	int8_t app_loop(AppArg *apparg);
};


AdjustClock::~AdjustClock(){
}


int8_t AdjustClock::app_setup(AppArg *apparg){
	apparg->use_global = 0;
	local_init(apparg);
	
	uint8_t i;
	
	_adjust_tm.Year   = apparg->rtc->year();
	_adjust_tm.Month  = apparg->rtc->month();
	_adjust_tm.Day    = apparg->rtc->day();
	_adjust_tm.Wday   = apparg->rtc->wday();
	_adjust_tm.Hour   = apparg->rtc->hour24();
	_adjust_tm.Minute = apparg->rtc->minute();
	_adjust_tm.Second = 0;
	
	for (i=0;i<DIGIT_PCS;i++){
		apparg->local_color[i].element[HSV_H] = 0;
		apparg->local_color[i].element[HSV_S] = 0;
		apparg->local_color[i].element[HSV_V] = apparg->global_color[i].element[HSV_V];
	}
}


int8_t AdjustClock::app_loop(AppArg *apparg){
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
	
	
	if ( bt1==PRESS   ||   (bt1rp==HOLD_REPEAT && (apparg->count&0x07)==0)  ){
		_adjust_tm.Hour++;
		apparg->speaker->dotbeep();
	}
	if ( bt2==PRESS   ||   (bt2rp==HOLD_REPEAT && (apparg->count&0x07)==0)  ){
		_adjust_tm.Minute++;
		apparg->speaker->dotbeep();
	}
	
	if (_adjust_tm.Hour   > 23)_adjust_tm.Hour = 0;
	if (_adjust_tm.Minute > 59)_adjust_tm.Minute = 0;
	
	if (bt3 == PRESS){
		apparg->rtc->adjust( _adjust_tm, 0);
		apparg->speaker->longbeep();
	}
	
	
	num1 = _adjust_tm.Hour;
	num2 = _adjust_tm.Minute;
	num3 = _adjust_tm.Second;
	apparg->number[5] = num1/10;
	apparg->number[4] = num1%10;
	apparg->number[3] = num2/10;
	apparg->number[2] = num2%10;
	apparg->number[1] = num3/10;
	apparg->number[0] = num3%10;
	return 0;
}