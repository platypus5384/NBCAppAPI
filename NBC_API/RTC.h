#pragma once

#include <Arduino.h>
#include <Wire.h>
#include "Common.h"




typedef struct{
  uint16_t ms    : 10;
  uint8_t Second : 6;
  uint8_t Minute : 6;
  uint8_t Hour   : 5;
  uint8_t Wday   : 3;
  uint8_t Day    : 5;
  uint8_t Month  : 4; 
  uint8_t Year   : 7;
}tmElements_t;


typedef union {
  struct{
    bool enable : 1;
    bool result : 1;
    uint8_t hour : 5;
    uint8_t minute : 6;
  };
}tmAlarm;


class RTC {
  protected:
    tmElements_t _tm;
    tmAlarm _alarm;
    uint32_t _b_time_ms;
    uint8_t _b_sec;

    uint8_t _mode12;

    bool virtual _read();
    bool virtual _write( tmElements_t tm);
    void virtual _write_alarm( uint8_t enable, uint8_t hour, uint8_t minute);
  public:
    RTC();
    void update();
    void update_ms(uint32_t time_sec);
    void adjust( tmElements_t tm, uint16_t delay_ms);
    void setAlarmResult(){_alarm.result=1;};
    void setAlarm( uint8_t enable, uint8_t hour, uint8_t minute);
    void setMode12( uint8_t use_12);

    uint8_t getAlarmResult(){return _alarm.result;};
    tmAlarm getAlarm(){return _alarm;};
    uint8_t getMode12(){return _mode12;};

    uint8_t year()  {return _tm.Year;};
    uint8_t month() {return _tm.Month;};
    uint8_t day()   {return _tm.Day;};
    uint8_t wday()  {return _tm.Wday;};
    uint8_t hour()  {return (_mode12==1&&_tm.Hour>=12)?_tm.Hour-12:_tm.Hour;};
    uint8_t minute(){return _tm.Minute;};
    uint8_t second(){return _tm.Second;};
    uint16_t msec(){return _tm.ms;};

    uint8_t hour24(){return _tm.Hour;};
};


/* ------------------------------------------------- */
#define RX8025T_ADRS  0x32


class RX8025T : public RTC{
  private:
    bool virtual _read();
    bool virtual _write( tmElements_t tm);
  public:
    RX8025T();
};


/* ------------------------------------------------- */
#define RX8025SA_ADRS  0x32
#define RX8025SA_CONTROL1_REGISTOR  0b00100000
#define RX8025SA_CONTROL2_REGISTOR  0b00010000

#define RX8025SA_MODE12 5
#define RX8025SA_DALE   6

#define RX8025SA_DAFG 0
#define RX8025SA_PON  4
#define RX8025SA_VDET 6

typedef union{
  uint8_t bit_field;
  struct{
    bool CT0    : 1;
    bool CT1    : 1;
    bool CT2    : 1;
    bool TEST   : 1;
    bool CLEN2  : 1;
    bool MODE12 : 1;
    bool DALE   : 1;
    bool WALE   : 1;
  };
}RX8025SA_Control1Register;

typedef union{
  uint8_t bit_field;
  struct{
    bool DAFG   : 1;
    bool WAFG   : 1;
    bool CTFG   : 1;
    bool CLEN1  : 1;
    bool PON    : 1;
    bool XST    : 1;
    bool VDET   : 1;
    bool VDSL   : 1;
  };
}RX8025SA_Control2Register;

class RX8025SA : public RTC{
  private:
    uint8_t _control1, _control2;
    bool virtual _read();
    bool virtual _write( tmElements_t tm);
    void virtual _write_alarm(uint8_t enable, uint8_t hour, uint8_t minute);
  public:
    RX8025SA();
};
