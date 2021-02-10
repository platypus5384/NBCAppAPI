#pragma once

#include <Arduino.h>
#include "NBClockApp.h"
#include "func.h"


/*
アプリ名:ストップウォッチ

ストップウォッチ

精度は20ppm(日差±2秒)
時計の精度は5ppm

時時/分分/秒秒/ミリ秒ミリ秒
秒秒/秒秒/秒秒/ミリ秒ミリ秒

ボタン1:ストップ・スタート
ボタン2:ストップ・リセット
ボタン3:分/秒を切り替え
*/


void StopWatch_setup(AppArg *apparg){
  apparg->use_global = 1;
}


void StopWatch_loop(AppArg *apparg){
  uint8_t bt1, bt2, bt3;
  uint8_t i;
  uint32_t elapse_time_ms;

  bt1 = apparg->controller->state(BT_1);
  bt2 = apparg->controller->state(BT_2);
  bt3 = apparg->controller->state(BT_3);
  
  if (bt1 == PRESS){
	  apparg->timewatch->pause( apparg->timewatch->is_pause()^1);
  }
  if (bt2 == PRESS){
	  apparg->timewatch->reset();
  }
  if (bt3 == PRESS){
	  
  }
  
  
  elapse_time_ms = apparg->timewatch->get();
  apparg->number[5] = (elapse_time_ms/1000000)%10;
  apparg->number[4] = (elapse_time_ms/100000)%10;
  apparg->number[3] = (elapse_time_ms/10000)%10;
  apparg->number[2] = (elapse_time_ms/1000)%10;
  apparg->number[1] = (elapse_time_ms/100)%10;
  apparg->number[0] = (elapse_time_ms/10)%10;
}