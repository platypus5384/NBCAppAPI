#pragma once

#include <Arduino.h>
#include "NBClockApp.h"
#include "func.h"


/*
�A�v����:�V���v�����v
�F�ݒ�:�O���[�o��

�V���v���Ȏ��v

����/����/�b�b

�{�^��1:����
�{�^��2:����
�{�^��3:12/24���Ԑ��̐؂�ւ�
*/

int8_t _view_digit;
int8_t _hour12;

typedef enum{
	DIGIT_SECOND,
	DIGIT_MINUTE,
	DIGIT_HOUR,
	DIGIT_DAY,
	DIGIT_MONTH,
	DIGIT_CALEMDER_ELEMENT_NUM,
	DIGIT_YEAR,
};


int8_t ExtendClock_setup(AppArg *apparg){
	_view_digit  = DIGIT_SECOND;
	apparg->use_global = 1;
	local_init(apparg);
	return 0;
}


int8_t ExtendClock_loop(AppArg *apparg){
	uint8_t bt1, bt2, bt3;

	bt1 = apparg->controller->state(BT_1);
	bt2 = apparg->controller->state(BT_2);
	bt3 = apparg->controller->state(BT_3);
	
	if (bt1 == PRESS)_view_digit++;
	if (bt2 == PRESS)_view_digit--;
	if (bt3 == PRESS)apparg->rtc->setMode12(apparg->rtc->getMode12()^1);
	
	if (_view_digit < 0)_view_digit = 0;
	if (_view_digit >= (DIGIT_CALEMDER_ELEMENT_NUM-2))_view_digit = DIGIT_CALEMDER_ELEMENT_NUM-3;
	
	uint8_t digit_array[DIGIT_CALEMDER_ELEMENT_NUM*2];
	digit_array[DIGIT_SECOND*2+0] = (apparg->rtc->second()) %10;
	digit_array[DIGIT_SECOND*2+1] = (apparg->rtc->second()) /10;
	digit_array[DIGIT_MINUTE*2+0] = (apparg->rtc->minute()) %10;
	digit_array[DIGIT_MINUTE*2+1] = (apparg->rtc->minute()) /10;
	digit_array[DIGIT_HOUR*2+0]   = (apparg->rtc->hour())   %10;
	digit_array[DIGIT_HOUR*2+1]   = (apparg->rtc->hour())   /10;
	digit_array[DIGIT_DAY*2+0]    = (apparg->rtc->day())    %10;
	digit_array[DIGIT_DAY*2+1]    = (apparg->rtc->day())    /10;
	digit_array[DIGIT_MONTH*2+0]  = (apparg->rtc->month())  %10;
	digit_array[DIGIT_MONTH*2+1]  = (apparg->rtc->month())  /10;
	
	digitArray(apparg, digit_array, DIGIT_CALEMDER_ELEMENT_NUM*2, _view_digit*2);
	return 0;
}