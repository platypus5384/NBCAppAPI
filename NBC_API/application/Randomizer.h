#pragma once

#include <Arduino.h>
#include "NBClockApp.h"
#include "func.h"


/*
アプリ名:ランダマイザー
色設定:グローバル

シュタインズゲートのような演出を行うApp
演出1: 永遠に全ランダム
演出2: シュタインズゲート
演出3: 全ランダム→右から順に終了

時時/分分/秒秒

ボタン1:演出の変更
ボタン2:無し
ボタン3:12/24時間制の切り替え
*/


class Randomizer : public NBClockApp{
	private:
	uint16_t ct;
	uint8_t mode;
	AppArg* mApparg;
	uint8_t random_flag[DIGIT_PCS];
	public:
	Randomizer() : NBClockApp(){};
	~Randomizer();
	int8_t app_setup(AppArg *apparg);
	int8_t app_loop(AppArg *apparg);
};

Randomizer::~Randomizer(){
	mApparg->stainsgate_flag.flag = 0b00000000;
}



int8_t Randomizer::app_setup(AppArg *apparg){
	ct = 0;
	mode = 0;
	apparg->use_global = 1;
	local_init(apparg);
	mApparg = apparg;
	for (uint8_t i; i<DIGIT_PCS;i++){ random_flag[i] = i; }
	return 0;
}


int8_t Randomizer::app_loop(AppArg *apparg){
	uint8_t num1, num2, num3;
	
	if (++ct > 750)ct=0;

	if (mode == 0)
	{
		apparg->stainsgate_flag.enable = 1;
		apparg->stainsgate_flag.digit0 = 1;
		apparg->stainsgate_flag.digit1 = 1;
		apparg->stainsgate_flag.digit2 = 1;
		apparg->stainsgate_flag.digit3 = 1;
		apparg->stainsgate_flag.digit4 = 1;
		apparg->stainsgate_flag.digit5 = 1;
	}else if (mode == 1)
	{
		if (ct == 1)
		{
			apparg->stainsgate_flag.enable = 1;
			apparg->stainsgate_flag.digit0 = 1;
			apparg->stainsgate_flag.digit1 = 1;
			apparg->stainsgate_flag.digit2 = 1;
			apparg->stainsgate_flag.digit3 = 1;
			apparg->stainsgate_flag.digit4 = 1;
			apparg->stainsgate_flag.digit5 = 1;
			for (uint8_t i; i<10; i++){
				uint8_t rnd = random(0, DIGIT_PCS);
				uint8_t tmp = random_flag[0];
				random_flag[0] = random_flag[rnd];
				random_flag[rnd] = tmp;
			}
		}
		else if (ct == 150)
		{
			apparg->stainsgate_flag.flag &= ~(0b00000010 << random_flag[0]);
		}
		else if (ct == 200)
		{
			apparg->stainsgate_flag.flag &= ~(0b00000010 << random_flag[1]);
		}
		else if (ct == 250)
		{
			apparg->stainsgate_flag.flag &= ~(0b00000010 << random_flag[2]);
		}
		else if (ct == 300)
		{
			apparg->stainsgate_flag.flag &= ~(0b00000010 << random_flag[3]);
		}
		else if (ct == 350)
		{
			apparg->stainsgate_flag.flag &= ~(0b00000010 << random_flag[4]);
		}
		else if (ct == 400)
		{
			apparg->stainsgate_flag.flag &= ~(0b00000010 << random_flag[5]);
		}
		
	}else if (mode == 2)
	{
		if (ct == 1)
		{
			apparg->stainsgate_flag.enable = 1;
			apparg->stainsgate_flag.digit0 = 1;
			apparg->stainsgate_flag.digit1 = 1;
			apparg->stainsgate_flag.digit2 = 1;
			apparg->stainsgate_flag.digit3 = 1;
			apparg->stainsgate_flag.digit4 = 1;
			apparg->stainsgate_flag.digit5 = 1;
			
		}
		else if (ct == 150)
		{
			apparg->stainsgate_flag.digit0 = 0;
		}
		else if (ct == 200)
		{
			apparg->stainsgate_flag.digit1 = 0;
		}
		else if (ct == 250)
		{
			apparg->stainsgate_flag.digit2 = 0;
		}
		else if (ct == 300)
		{
			apparg->stainsgate_flag.digit3 = 0;
		}
		else if (ct == 350)
		{
			apparg->stainsgate_flag.digit4 = 0;
		}
		else if (ct == 400)
		{
			apparg->stainsgate_flag.digit5 = 0;
			apparg->stainsgate_flag.enable = 0;
		}
	}
	
	if (apparg->controller->state(BT_1) == PRESS)
	{
		ct = 0;
		if (++mode >= 3)mode = 0;
		apparg->speaker->dotbeep();
	}
	
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