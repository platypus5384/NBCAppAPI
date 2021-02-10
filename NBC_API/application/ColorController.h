#pragma once

#include <Arduino.h>
#include "NBClockApp.h"
#include "func.h"


/*
アプリ名:カラーコントローラー

HSV形式でグローバル色の変更が可能
H,S,Vはそれぞれ0~99の範囲で変更可能.

HH/SS/VV


ボタン1:Hue(色調)の変更 
ボタン2:Sat(彩度)の変更
ボタン3:Val(輝度)の変更 
*/


class ColorController : public NBClockApp{
	private:
	bool _changed;
	uint8_t _hue;
	uint8_t _sat;
	uint8_t _val;
	
	public:
	ColorController() : NBClockApp(){};
	~ColorController();
	int8_t app_setup(AppArg *apparg);
	int8_t app_loop(AppArg *apparg);
	int8_t app_destroy(AppArg *apparg);
};

ColorController::~ColorController(){
}

int8_t ColorController::app_destroy(AppArg *apparg){
	if (_changed == true){
		for (uint8_t i=0;i<DIGIT_PCS;i++){
			apparg->global_color[i].element[HSV_H] = _hue * 2.58f;
			apparg->global_color[i].element[HSV_S] = _sat * 2.58f;
			apparg->global_color[i].element[HSV_V] = _val * 2.58f;
			
			apparg->global_wave[HSV_H][i].enable = 0;
			apparg->global_wave[HSV_S][i].enable = 0;
			apparg->global_wave[HSV_V][i].enable = 0;
		}
		saveColorWave( apparg);
	}
}


int8_t ColorController::app_setup(AppArg *apparg){
	_changed = false;
	apparg->use_global = 0;
	
	local_init(apparg);
	_hue = (uint8_t)((float)apparg->global_color[0].element[HSV_H] / 2.56f);
	_sat = (uint8_t)((float)apparg->global_color[0].element[HSV_S] / 2.56f);
	_val = (uint8_t)((float)apparg->global_color[0].element[HSV_V] / 2.56f);
	
	apparg->local_color[0].element[HSV_H] = 0;
	apparg->local_color[0].element[HSV_S] = 0;
	apparg->local_color[0].element[HSV_V] = 255;
	apparg->local_color[1].element[HSV_H] = 0;
	apparg->local_color[1].element[HSV_S] = 0;
	apparg->local_color[1].element[HSV_V] = 255;
}


int8_t ColorController::app_loop(AppArg *apparg){
	uint8_t num1, num2, num3;
	uint8_t i;
	uint8_t bt1, bt2, bt3, bt1rp, bt2rp, bt3rp;
	
	
	bt1   = apparg->controller->state(BT_1);
	bt2   = apparg->controller->state(BT_2);
	bt3   = apparg->controller->state(BT_3);
	bt1rp = apparg->controller->stateRepeat(BT_1);
	bt2rp = apparg->controller->stateRepeat(BT_2);
	bt3rp = apparg->controller->stateRepeat(BT_3);
	
	
	if ( bt1==PRESS   ||   (bt1rp==HOLD_REPEAT && (apparg->count&0x07)==0)  ){
		_changed = true;
		_hue++;
		apparg->speaker->dotbeep();
	}
	if ( bt2==PRESS   ||   (bt2rp==HOLD_REPEAT && (apparg->count&0x07)==0)  ){
		_changed = true;
		_sat++;
		apparg->speaker->dotbeep();
	}
	if ( bt3==PRESS   ||   (bt3rp==HOLD_REPEAT && (apparg->count&0x03)==0)  ){
		_changed = true;
		_val++;
		apparg->speaker->dotbeep();
	}
  
	if (_hue > 99)_hue = 0;
	if (_sat > 99)_sat = 0;
	if (_val > 99)_val = 0;
  
  
	for (i=2;i<DIGIT_PCS;i++){
		apparg->local_color[i].element[HSV_H] = _hue * 2.58f;
		apparg->local_color[i].element[HSV_S] = _sat * 2.58f;
		apparg->local_color[i].element[HSV_V] = _val * 2.58f;
	}
	
	
	num1 = _hue;
	num2 = _sat;
	num3 = _val;
	apparg->number[5] = num1/10;
	apparg->number[4] = num1%10;
	apparg->number[3] = num2/10;
	apparg->number[2] = num2%10;
	apparg->number[1] = num3/10;
	apparg->number[0] = num3%10;
	return 0;
}