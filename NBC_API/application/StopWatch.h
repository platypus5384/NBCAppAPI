#pragma once

#include <Arduino.h>
#include "NBClockApp.h"
#include "func.h"


/*
�A�v����:�X�g�b�v�E�H�b�`

�X�g�b�v�E�H�b�`

���x��20ppm(�����}2�b)
���v�̐��x��5ppm

����/����/�b�b/�~���b�~���b
�b�b/�b�b/�b�b/�~���b�~���b

�{�^��1:�X�g�b�v�E�X�^�[�g
�{�^��2:�X�g�b�v�E���Z�b�g
�{�^��3:��/�b��؂�ւ�
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