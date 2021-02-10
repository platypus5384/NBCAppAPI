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
/*-----�@�����Ƀ��[�U��`�A�v���̃w�b�_include�������@-----*/


/*-----�@�����Ƀ��[�U��`�A�v���̃w�b�_include�������@-----*/



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
	
	
	/*-----�@�����Ƀ��[�U��`�A�v���̎��ʎq������@-----*/
	NBCAPP_PCS,
	NBCAPP_NONE,
	NBCAPP_RETURN,
}NBCAPP_NAME;


/*-----�@��{�A�v�����X�g�@�@����N�����͂���@-----*/
extern NBCAPP_NAME basic_app_list[  BASIC_APPLIST_LENGTH] = {
  NBCAPP_SIMPLE_CLOCK,
  NBCAPP_KITCHEN_TIMER,
  NBCAPP_ALARM,
  NBCAPP_RETURN,
  NBCAPP_RETURN
};

/*-----�@�F�ݒ�A�v�����X�g�@�@�@�\�{�^���𒷉������邱�Ƃňڍs�@-----*/
extern NBCAPP_NAME color_app_list[  COLOR_APPLIST_LENGTH] = {
  NBCAPP_COLOR_CONTROLLER,
  NBCAPP_WAVE_CONTROLLER,
  NBCAPP_RETURN,
  NBCAPP_RETURN,
  NBCAPP_RETURN
};

/*-----�@�g���A�v�����X�g�@�@�@�\�{�^���𒴒��������邱�Ƃňȍ~�@-----*/
extern NBCAPP_NAME extend_app_list[EXTEND_APPLIST_LENGTH] = {
  NBCAPP_ADJUST_CLOCK,
  NBCAPP_RETURN,
  NBCAPP_RETURN,
  NBCAPP_RETURN,
  NBCAPP_RETURN
};



/*-----�@�A�v���I�u�W�F�N�g�̍Đ����E�ă������m�ہ@-----*/
/*-----�@main()����delete, �^���R���X�g���N�^, �^���f�X�g���N�g�̋N�����s���Ă���.�@------*/
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