#include <Arduino.h>
#include <Wire.h>


#include "Common.h"
#include "EEPROM_func.h"
#include "application/NBClockAppList.h"
#include "command/NBClockCommandList.h"
#include "Effect.h"



AppArg _apparg;
LedStringNBClock6 _disp;
Controller        _controller;
TimeWatch         _time_watch;
Speaker           _speaker(5);

AppArg*  apparg;
LedString* disp;
NBClockApp* app;


uint8_t i;

void setup()
{
  delay(10); // RTCの起動待ち.
  Wire.begin();
  delay(1);
  Serial.begin(9600);
  delay(1);

  // ポインタ渡し
  apparg = &_apparg;
  apparg->rtc        = new RX8025SA(); // Wire.begin()以降に生成する事(コンストラクタでWire通信を行うため)
  apparg->controller = &_controller;
  apparg->timewatch  = &_time_watch;
  apparg->speaker    = &_speaker;
  disp = &_disp;

  // 初期化
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>( disp->leds, LED_PCS).setCorrection(TypicalLEDStrip);
  apparg->speaker->setBeepHz(44);
  apparg->rtc->update();

  // app初期化
  app = new SimpleClock();
  app->app_setup(apparg);

  // LEDのColorとWaveの初期化
  initColorWave( apparg); // 初回起動時のみ実行される.
  loadColorWave( apparg); // 色
  apparg->speaker->shortbeep(); //起動音を鳴らす.
  delay(100);
}




//---------------------------------------------------
uint32_t time_ms;
uint32_t time_us;
uint32_t rtc_read_time_ms = 0;




AppList app_list_number   = BASIC_APPLIST;
AppList b_app_list_number = BASIC_APPLIST;
NBCAPP_NAME app_name = NBCAPP_SIMPLE_CLOCK;
uint8_t app_number = 0;
bool app_change = false;


void loop()
{
  while (true) {
    /*----- update -----*/
    apparg->count++;
    time_ms = millis();
    time_us = micros();
    apparg->controller->update(time_ms);
    apparg->time_ms = time_ms;
    apparg->rtc->update_ms(time_ms);
    apparg->timewatch->update(time_us);
    if ( CalcElapseTime(time_ms, rtc_read_time_ms) > 10) {
      rtc_read_time_ms = time_ms;
      apparg->rtc->update();
    }

    /*----- BT_EXT Process -----*/
    if (apparg->controller->state(BT_EXT) == RELEASE) {
      app_change = true;
      app_number += 1;
      apparg->speaker->dotbeep();
    } else if (apparg->controller->state(BT_EXT) == HOLD) {
      app_change = true;
      app_number = 0;
      b_app_list_number = app_list_number;
      app_list_number = COLOR_APPLIST;
      if (b_app_list_number == COLOR_APPLIST) {
        app_list_number = BASIC_APPLIST;
      }
      apparg->speaker->shortbeep();
      delay(100);
    } else if (apparg->controller->state(BT_EXT) == HOLD_LONG) {
      app_change = true;
      app_number = 0;
      if (b_app_list_number == BASIC_APPLIST) {
        app_list_number = EXTEND_APPLIST;
      } else if (b_app_list_number == COLOR_APPLIST) {
        app_list_number = EXTEND_APPLIST;
      } else if (b_app_list_number == EXTEND_APPLIST) {
        app_list_number = BASIC_APPLIST;
      }
      apparg->speaker->beep();
      delay(100);
    }

    if (app_list_number < 0)app_list_number = 0;
    if (app_list_number >= APPLIST_PCS)app_list_number = 0;

    if (app_number < 0)app_number = 0;
    if (app_list_number == BASIC_APPLIST) {
      if (app_number >= BASIC_APPLIST_LENGTH)app_number = 0;
      if (basic_app_list[app_number] == NBCAPP_RETURN)app_number = 0;
      app_name = basic_app_list[app_number];
    } else if (app_list_number == COLOR_APPLIST) {
      if (app_number >= COLOR_APPLIST_LENGTH)app_number = 0;
      if (color_app_list[app_number] == NBCAPP_RETURN)app_number = 0;
      app_name = color_app_list[app_number];
    } else if (app_list_number == EXTEND_APPLIST) {
      if (app_number >= EXTEND_APPLIST_LENGTH)app_number = 0;
      if (extend_app_list[app_number] == NBCAPP_RETURN)app_number = 0;
      app_name = extend_app_list[app_number];
    } else {
      app_name = NBCAPP_SIMPLE_CLOCK;
    }

    if (app_change == true) {
      app_change = false;
      app->app_destroy(apparg);
      delete app;
      app_new( app_name, app);
      app->app_setup(apparg);
    }
    
    /*----- Function pointer -----*/
    app->app_loop( apparg);

    /*----- Serial -----*/
    processSerial(apparg);

    /*----- Speaker -----*/
    if (apparg->rtc->getAlarmResult() == 1) {
      if ( apparg->controller->state(BT_1) == PRESS || apparg->controller->state(BT_2) == PRESS || apparg->controller->state(BT_3) == PRESS) {
        apparg->rtc->setAlarm(0, 0, 0);
      }
      if ((apparg->count & 0x3F) == 0) {
        apparg->speaker->beep();
      }
    }

    /*----- Effect -----*/
    StainsGateEffect( apparg);
    

    /*----- Set digit -----*/
    if  (apparg->use_global == 1) {
      for (i = 0; i < DIGIT_PCS; i++) {
        disp->setDigitWave(  i, HSV_H, apparg->global_wave[HSV_H][i]);
        disp->setDigitWave(  i, HSV_S, apparg->global_wave[HSV_S][i]);
        disp->setDigitWave(  i, HSV_V, apparg->global_wave[HSV_V][i]);
        disp->setDigitColor( i, apparg->global_color[i]);
        disp->setDigitNumber( i, apparg->number[i]);
      }
    } else {
      for (i = 0; i < DIGIT_PCS; i++) {
        disp->setDigitWave(  i, HSV_H, apparg->local_wave[HSV_H][i]);
        disp->setDigitWave(  i, HSV_S, apparg->local_wave[HSV_S][i]);
        disp->setDigitWave(  i, HSV_V, apparg->local_wave[HSV_V][i]);
        disp->setDigitColor( i, apparg->local_color[i]);
        disp->setDigitNumber( i, apparg->number[i]);
      }
    }
    disp->calc( time_ms);
    disp->showLEDs();
  }
}



//-----------------------------------------------------
