#pragma once

#include <Arduino.h>
#include "NBClockApp.h"



void local_init( AppArg *apparg){
	int i;
	for (i=0;i<DIGIT_PCS;i++){
		apparg->local_wave[HSV_H][i].enable = 0;
		apparg->local_wave[HSV_H][i].peroid_ms = 0;
		apparg->local_wave[HSV_H][i].amp       = 0;
		apparg->local_wave[HSV_H][i].faze      = 0;
		apparg->local_wave[HSV_S][i].enable = 0;
		apparg->local_wave[HSV_S][i].peroid_ms = 0;
		apparg->local_wave[HSV_S][i].faze      = 0;
		apparg->local_wave[HSV_V][i].enable = 0;
		apparg->local_wave[HSV_V][i].peroid_ms = 0;
		apparg->local_wave[HSV_V][i].amp       = 0;
		apparg->local_wave[HSV_V][i].faze      = 0;
		
		apparg->local_color[i].element[HSV_H] = 0;
		apparg->local_color[i].element[HSV_S] = 0;
		apparg->local_color[i].element[HSV_V] = 255;
	}
}



void digitArray(AppArg* apparg, uint8_t* digit_array, uint8_t digit_array_length, uint8_t view_digit){
	uint8_t i=0;
	
	if (view_digit > (digit_array_length - DIGIT_PCS))view_digit = (digit_array_length - DIGIT_PCS);
	for (i=0;i<DIGIT_PCS;i++){
		apparg->number[i] = *(digit_array+i+view_digit);
	}
}