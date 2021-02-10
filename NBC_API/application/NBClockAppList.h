#pragma once

#include <Arduino.h>
#include "../Common.h"


#include "NBClockApp.h"
#include "SimpleClock.h"
#include "ExtendClock.h"
#include "ColorController.h"
#include "StopWatch.h"
#include "WaveController.h"
#include "Alarm.h"
#include "KitchenTimer.h"
#include "Adjust_clock.h"
/*-----　ここにユーザ定義アプリのヘッダincludeを書く　-----*/


/*-----　ここにユーザ定義アプリのヘッダincludeを書く　-----*/



#define BASIC_APPLIST_LENGTH   5
#define COLOR_APPLIST_LENGTH   5
#define EXTEND_APPLIST_LENGTH  5
typedef enum {
	BASIC_APPLIST,
	COLOR_APPLIST,
	EXTEND_APPLIST,
	APPLIST_PCS,
} AppList;


typedef enum {
	NBCAPP_SIMPLE_CLOCK,
	NBCAPP_KITCHEN_TIMER,
	NBCAPP_ALARM,
	NBCAPP_COLOR_CONTROLLER,
	NBCAPP_WAVE_CONTROLLER,
	NBCAPP_ADJUST_CLOCK,
	NBCAPP_EXTEND_CLOCK,
	NBCAPP_STOP_WATCH,
	
	
	/*-----　ここにユーザ定義アプリの識別子を入れる　-----*/
	NBCAPP_PCS,
	NBCAPP_NONE,
	NBCAPP_RETURN,
}NBCAPP_NAME;


/*-----　基本アプリリスト　　初回起動時はこれ　-----*/
extern NBCAPP_NAME basic_app_list[  BASIC_APPLIST_LENGTH] = {
  NBCAPP_SIMPLE_CLOCK,
  NBCAPP_KITCHEN_TIMER,
  NBCAPP_ALARM,
  NBCAPP_RETURN,
  NBCAPP_RETURN
};

/*-----　色設定アプリリスト　　機能ボタンを長押しすることで移行　-----*/
extern NBCAPP_NAME color_app_list[  COLOR_APPLIST_LENGTH] = {
  NBCAPP_COLOR_CONTROLLER,
  NBCAPP_WAVE_CONTROLLER,
  NBCAPP_RETURN,
  NBCAPP_RETURN,
  NBCAPP_RETURN
};

/*-----　拡張アプリリスト　　機能ボタンを超長押しすることで以降　-----*/
extern NBCAPP_NAME extend_app_list[EXTEND_APPLIST_LENGTH] = {
  NBCAPP_ADJUST_CLOCK,
  NBCAPP_RETURN,
  NBCAPP_RETURN,
  NBCAPP_RETURN,
  NBCAPP_RETURN
};



/*-----　アプリオブジェクトの再生成・再メモリ確保　-----*/
/*-----　main()内でdelete, 疑似コンストラクタ, 疑似デストラクトの起動を行っている.　------*/
int8_t app_new(  uint8_t app_number, NBClockApp * app) {
  switch ( app_number) {
    
    case NBCAPP_SIMPLE_CLOCK:
      app = new SimpleClock();
      break;
      
    /*
    case NBCAPP_EXTEND_CLOCK:
      app = new ExtendClock();
      break;
    */
      
    case NBCAPP_COLOR_CONTROLLER:
      app = new ColorController();
      break;

      
    case NBCAPP_WAVE_CONTROLLER:
      app = new WaveController();
      break;

      
    case NBCAPP_ALARM:
      app = new Alarm();
      break;

      
    case NBCAPP_KITCHEN_TIMER:
      app = new KitchenTimer();
      break;

      
    case NBCAPP_ADJUST_CLOCK:
      app = new AdjustClock();
      break;
    
    /*
    case NBCAPP_STAINSGATE_CLOCK:
      app = new StainsGate();
      break;
    */

      
    default:
      app = new SimpleClock();
      break;
  }
  return 0;
}