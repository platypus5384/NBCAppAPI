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
#include "Randomizer.h"

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
	NBCAPP_RANDOMIZER,
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
NBClockApp* app_new(  NBCAPP_NAME app_number) {
  NBClockApp* tmp;
  switch ( app_number) {
    
    case NBCAPP_SIMPLE_CLOCK:
      tmp = new SimpleClock();
      break;
      
    /*
    case NBCAPP_EXTEND_CLOCK:
      tmp = new ExtendClock();
      break;
    */
      
    case NBCAPP_COLOR_CONTROLLER:
      tmp = new ColorController();
      break;

      
    case NBCAPP_WAVE_CONTROLLER:
      tmp = new WaveController();
      break;

      
    case NBCAPP_ALARM:
      tmp = new Alarm();
      break;

      
    case NBCAPP_KITCHEN_TIMER:
      tmp = new KitchenTimer();
      break;

      
    case NBCAPP_ADJUST_CLOCK:
      tmp = new AdjustClock();
      break;
    
    /*
    case NBCAPP_STAINSGATE_CLOCK:
      tmp = new StainsGate();
      break;
    */
	
	
	case NBCAPP_RANDOMIZER:
	  tmp = new Randomizer();
	  break;

      
    default:
      tmp = new SimpleClock();
      break;
  }
  return tmp;
}