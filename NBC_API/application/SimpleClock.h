#pragma once

#include <Arduino.h>
#include "NBClockApp.h"
#include "func.h"


/*
アプリ名:シンプル時計
色設定:グローバル

シンプルな時計

時時/分分/秒秒

ボタン1:無し
ボタン2:無し
ボタン3:12/24時間制の切り替え
*/


class SimpleClock : public NBClockApp{
	public:
	SimpleClock() : NBClockApp(){};
	~SimpleClock();
	int8_t app_setup(AppArg *apparg);
	int8_t app_loop(AppArg *apparg);
};

SimpleClock::~SimpleClock(){
}



int8_t SimpleClock::app_setup(AppArg *apparg){
	apparg->use_global = 1;
	local_init(apparg);
	return 0;
}


int8_t SimpleClock::app_loop(AppArg *apparg){
	uint8_t num1, num2, num3;
	
	
	if (apparg->controller->state(BT_3) == PRESS)
	{
		apparg->rtc->setMode12(apparg->rtc->getMode12()^1);
		apparg->speaker->dotbeep();
	}
	

	num1 = apparg->rtc->hour();
	num2 = apparg->rtc->minute();
	num3 = apparg->rtc->second();
	apparg->number[5] = num1/10;
	apparg->number[4] = num1%10;
	apparg->number[3] = num2/10;
	apparg->number[2] = num2%10;
	apparg->number[1] = num3/10;
	apparg->number[0] = num3%10;
	return 0;
}