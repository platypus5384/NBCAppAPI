#pragma once

#include <Arduino.h>
#include "NBClockApp.h"
#include "func.h"

/*
アプリ名:色ウェーブコントローラー

グローバル色のウェーブが変更が可能
周期[s] / 周期[ms] / 位相(0~99で1週)

ボタン1:周期の変更[s]を変更
ボタン2:Sat(彩度)の変更, 0に近いほど白色に、99に近いほど濃い?
ボタン3:Val(輝度)の変更,
*/


class WaveController : public NBClockApp{
	private:
	uint8_t _hue_wave_mode;
	uint8_t _hue_faze_wave_mode;
	uint8_t _val_wave_mode;
	bool _changed;
	
	public:
	WaveController();
	~WaveController();
	int8_t app_setup(AppArg *apparg);
	int8_t app_loop(AppArg *apparg);
	int8_t app_destroy(AppArg *apparg);
};

WaveController::WaveController() : NBClockApp(){
	_changed = false;
}

WaveController::~WaveController(){
}

int8_t WaveController::app_destroy(AppArg *apparg){
	if (_changed == true){
		saveColorWave( apparg);
	}
}


int8_t WaveController::app_setup(AppArg *apparg){
	apparg->use_global = 1;
	local_init(apparg);
	
	_hue_wave_mode = 0;
	_hue_faze_wave_mode = 0;
	_val_wave_mode = 0;
}


int8_t WaveController::app_loop(AppArg *apparg){
  uint8_t num1, num2, num3;
  uint8_t i;
  uint8_t bt1, bt2, bt3, bt1rp, bt2rp, bt3rp;
  
  
  bt1   = apparg->controller->state(BT_1);
  bt2   = apparg->controller->state(BT_2);
  bt3   = apparg->controller->state(BT_3);
  bt1rp = apparg->controller->stateRepeat(BT_1);
  bt2rp = apparg->controller->stateRepeat(BT_2);
  bt3rp = apparg->controller->stateRepeat(BT_3);
  
  
  if ( bt1==PRESS   ||   (bt1rp==HOLD_REPEAT && (apparg->count&0x0F)==0)  ){
	  _hue_wave_mode++;
	  apparg->speaker->dotbeep();
	  _changed = true;
  }
  if ( bt2==PRESS   ||   (bt2rp==HOLD_REPEAT && (apparg->count&0x0F)==0)  ){
	  _hue_faze_wave_mode++;
	  apparg->speaker->dotbeep();
	  _changed = true;
  }
  if ( bt3==PRESS   ||   (bt3rp==HOLD_REPEAT && (apparg->count&0x0F)==0)  ){
	  _val_wave_mode++;
	  apparg->speaker->dotbeep();
	  _changed = true;
  }
  
  if (_hue_wave_mode      > 9)_hue_wave_mode      = 0;
  if (_hue_faze_wave_mode > 9)_hue_faze_wave_mode = 0;
  if (_val_wave_mode      > 9)_val_wave_mode      = 0;
  
  
  if (_changed==true){
	for (i=0;i<DIGIT_PCS;i++){
		if (_hue_wave_mode==0){
			apparg->global_wave[HSV_H][i].enable = 0;
			apparg->global_wave[HSV_H][i].amp = 0;
			apparg->global_wave[HSV_H][i].peroid_ms = 0;
			apparg->global_wave[HSV_H][i].faze = 0;
		}else{
			apparg->global_wave[HSV_H][i].enable = 1;
			apparg->global_wave[HSV_H][i].amp = 0;
			apparg->global_wave[HSV_H][i].peroid_ms = _hue_wave_mode * 1000;
			apparg->global_wave[HSV_H][i].faze = apparg->global_wave[HSV_H][i].peroid_ms /9 * _hue_faze_wave_mode / DIGIT_PCS * i;
		}
		if (_val_wave_mode==0){
			apparg->global_wave[HSV_V][i].enable = 0;
			apparg->global_wave[HSV_V][i].amp =  0;
			apparg->global_wave[HSV_V][i].faze = 0;
			apparg->global_wave[HSV_V][i].peroid_ms = 0;
		}else{
			apparg->global_wave[HSV_V][i].enable = 1;
			apparg->global_wave[HSV_V][i].amp = 100;
			apparg->global_wave[HSV_V][i].faze = 0;
			apparg->global_wave[HSV_V][i].peroid_ms = _val_wave_mode * 1000;
		}
	}
  }
  
  
  num1 = _hue_wave_mode;
  num2 = _hue_faze_wave_mode;
  num3 = _val_wave_mode;
  apparg->number[5] = num1/10;
  apparg->number[4] = num1%10;
  apparg->number[3] = num2/10;
  apparg->number[2] = num2%10;
  apparg->number[1] = num3/10;
  apparg->number[0] = num3%10;
  
}