#pragma once

#include <Arduino.h>
#include "../Common.h"

#include "../AppArg.h"
#include "NONE.h"
#include "ACK.h"
#include "WHO.h"
#include "ADJUST_CLOCK.h"
#include "SET_EEPROM.h"
#include "STAINS_GATE.h"
#include "CHANGE_WAVE.h"
#include "CHANGE_COLOR.h"
/*-----　ここにユーザ定義シリアルコマンドのヘッダincludeを書く　-----*/


/*-----　ここにユーザ定義シリアルコマンドのヘッダincludeを書く　-----*/
/*-----　　-----*/



#define TIME_OUT 1000
#define COMMAND_NS  "NBC_CMD"
#define ACK "ACK"  //



typedef enum {
	CN_NONE,
	CN_ACK,
	CN_WHO,
	CN_ADJUST_CLOCK,
	CN_SET_EEPROM,
	CN_STAINS_GATE,
	CN_CHANGE_WAVE,
	CN_CHANGE_COLOR,
	/*-----　ここにユーザ定義シリアルコマンドの識別子を入れる　-----*/
	
	
	/*-----　ここにユーザ定義シリアルコマンドの識別子を入れる　-----*/
	COMMAND_NUMBER_PCS,
} COMMAND_NUMBER;




void processSerial(AppArg* apparg);

void (*command_pointer(COMMAND_NUMBER command_number, uint8_t *arg_pcs))
{
	
	uint8_t (*argpcs_func)() = NBClockCmdArgPcs_NONE;
	uint8_t (*cmd_func)(AppArg*, uint8_t[8]) = NBClockCmd_NONE;
	
	switch (command_number) {
	case CN_NONE:
		argpcs_func = NBClockCmdArgPcs_NONE;
		cmd_func = NBClockCmd_NONE;
		break;

	case CN_ACK:
		argpcs_func = NBClockCmdArgPcs_ACK;
		cmd_func = NBClockCmd_ACK;
		break;

	case CN_WHO:
		argpcs_func = NBClockCmdArgPcs_WHO;
		cmd_func = NBClockCmd_WHO;
		break;

	case CN_ADJUST_CLOCK:
		argpcs_func = NBClockCmdArgPcs_ADJUST_CLOCK;
		cmd_func = NBClockCmd_ADJUST_CLOCK;
		break;

	case CN_SET_EEPROM:
		argpcs_func = NBClockCmdArgPcs_SET_EEPROM;
		cmd_func = NBClockCmd_SET_EEPROM;
		break;

	case CN_STAINS_GATE:
		argpcs_func = NBClockCmdArgPcs_STAINS_GATE;
		cmd_func = NBClockCmd_STAINS_GATE;
		break;

	case CN_CHANGE_WAVE:
		argpcs_func = NBClockCmdArgPcs_CHANGE_WAVE;
		cmd_func = NBClockCmd_CHANGE_WAVE;
		break;

	case CN_CHANGE_COLOR:
		argpcs_func = NBClockCmdArgPcs_CHANGE_COLOR;
		cmd_func = NBClockCmd_CHANGE_COLOR;
		break;
		
		/*-----　ここでユーザ定義シリアルコマンドの引数の数を返す関数ポインタと、処理関数の関数ポインタを渡す　-----*/
		
		
		
		
		/*-----　ここでユーザ定義シリアルコマンドの引数の数を返す関数ポインタと、処理関数の関数ポインタを渡す　-----*/
		
		default:
		argpcs_func = NBClockCmdArgPcs_NONE;
		cmd_func = NBClockCmd_NONE;
		break;
	}
	*arg_pcs = argpcs_func();
	return cmd_func;
}


























/*arduinoは同ディレクトリ以外のmakefileの設定を上手く生成してくれない気がする、なのでヘッダに書く*/
/*-----　ここ以下はいじらないこと　-----*/
void processSerial(AppArg* apparg) {
	if (Serial.available() > 0) {
		String command_string;
		uint8_t command_number;
		char command_char_array[8] = {0};
		uint32_t b_time_ms;
		uint8_t command_argument_pcs = 0;
		uint8_t cmdarg[8] = {0};
		bool timeout = false;
		command_string = Serial.readStringUntil('\n');
		command_string.toCharArray(command_char_array, 8);

		if (strcmp( command_char_array, COMMAND_NS) == 0) {
			Serial.println("ACK");
			#ifdef DEBUG
			Serial.println("--- CMD MODE START ---");
			Serial.println("NBC<(Please command number)");
			#endif

			b_time_ms = millis();
			while (Serial.available() < 1) {
				if (CalcElapseTime( millis(), b_time_ms) > TIME_OUT) {
					Serial.println("timeout!");
					timeout = true;
					break;
				}
			}

			command_number = Serial.read();
			if ( (command_number < 0)  || (command_number >= COMMAND_NUMBER_PCS)) {
				command_number = 0;
			}
			
			
			uint8_t (*cmd_func)(AppArg*, uint8_t[]) = command_pointer( command_number, &command_argument_pcs);
			
			Serial.print ("command_number is ");
			Serial.println(command_number);
			Serial.print ("command_argument pcs is ");
			Serial.println(command_argument_pcs);
			Serial.println("NBC<(Please command argument)");


			b_time_ms = millis();
			while (Serial.available() < command_argument_pcs) {
				if (CalcElapseTime( millis(), b_time_ms) > TIME_OUT) {
					Serial.println("timeout!");
					timeout = true;
					break;
				}
			}

			Serial.println("--- result ---");
			if (timeout == true) {
				Serial.println("timeout !");
				} else{
				for (uint8_t i = 0; i < command_argument_pcs; i++) {
					cmdarg[i] = Serial.read();
				}
				cmd_func( apparg, &cmdarg[0]);
			}
			
			Serial.println("--- CMD MODE FINISH---");
		}
	}
}