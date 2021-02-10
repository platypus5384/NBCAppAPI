#include "RTC.h"


uint8_t toBCD(uint8_t num) {
  uint8_t hex0, hex1;
  hex0 = num % 10;
  hex1 = (num / 10) % 10;
  return (hex1 << 4) | hex0;
}

uint8_t fromBCD(uint8_t bcd) {
  uint8_t i0, i1;
  i0 = bcd & 0x0F;
  i1 = (bcd >> 4) * 10;
  return i0 + i1;
}


/* ------------------------------------------------- */
RTC::RTC() {
  _mode12 = 0;
  _alarm.result = 0;
};


void RTC::update() {
  delay(1);
  _read();
  delay(1);
}

void RTC::update_ms(uint32_t time_ms) {
  if (_tm.Second != _b_sec) {
    _b_time_ms = time_ms;
  }
  _tm.ms = time_ms - _b_time_ms;
  _b_sec = _tm.Second;
}


void RTC::adjust( tmElements_t tm, uint16_t delay_ms) {
  delay(delay_ms);
  delay(1);
  _write( tm);
  delay(1);
}

void RTC::setAlarm( uint8_t enable, uint8_t hour, uint8_t minute) {
  _write_alarm( enable, hour, minute);
}

void RTC::setMode12( uint8_t use_12) {
  _mode12 = use_12;
}



/* ------------------------------------------------- */
RX8025T::RX8025T() {
    delay(1);
    Wire.beginTransmission(RX8025T_ADRS);
    Wire.write(0xE0);
    Wire.write(0b00110000);  //Control 1
    Wire.write(0b00000000);  //Control 2
    Wire.endTransmission();
    delay(1);
}


bool RX8025T::_read() {
  Wire.requestFrom(RX8025T_ADRS, 8);
  Wire.read();
  _tm.Second = fromBCD(Wire.read());
  _tm.Minute = fromBCD(Wire.read());
  _tm.Hour   = fromBCD(Wire.read());
  _tm.Wday   = Wire.read();
  _tm.Day    = Wire.read();
  _tm.Month  = Wire.read();
  _tm.Year   = Wire.read();
}


bool RX8025T::_write( tmElements_t tm) {
  Wire.beginTransmission(RX8025T_ADRS);
  Wire.write(0x00); // start register position
  Wire.write( toBCD( tm.Second)); // 0:Seconds
  Wire.write( toBCD( tm.Minute)); // 1:Minutes
  Wire.write( toBCD( tm.Hour)); // 2:Hours
  Wire.write( tm.Wday); // 3:Week
  Wire.write( tm.Day); // 4:Days
  Wire.write( tm.Month); // 5:Months
  Wire.write( tm.Year); // 6:Years
  Wire.write(0x20); // 7: digital offset ( default=32=0x20)
  Wire.endTransmission();
}



/********************************************************************************/
RX8025SA::RX8025SA() {
  delay(1);
  Wire.beginTransmission(RX8025T_ADRS);
  Wire.write(0xE0);
  Wire.write(RX8025SA_CONTROL1_REGISTOR);
  Wire.write(RX8025SA_CONTROL2_REGISTOR);
  Wire.endTransmission();
}


bool RX8025SA::_read() {
  Wire.requestFrom(RX8025T_ADRS, 17);
  Wire.read(); // ACK??
  _tm.Second = fromBCD(Wire.read());
  _tm.Minute = fromBCD(Wire.read());
  _tm.Hour   = fromBCD(Wire.read()); 
  _tm.Wday   = fromBCD(Wire.read());
  _tm.Day    = fromBCD(Wire.read());
  _tm.Month  = fromBCD(Wire.read());
  _tm.Year   = fromBCD(Wire.read());
  Wire.read(); // 
  Wire.read(); // 
  Wire.read(); // 
  Wire.read(); // 
  _alarm.minute  = fromBCD(Wire.read());
  _alarm.hour    = fromBCD(Wire.read());
  Wire.read(); //
  _control1 = Wire.read();
  _control2 = Wire.read();

  _alarm.enable = ((_control1 & (1 << RX8025SA_DALE)) >> RX8025SA_DALE);
  _alarm.result = ((_control2 & (1 << RX8025SA_DAFG)) >> RX8025SA_DAFG);
}


bool RX8025SA::_write( tmElements_t tm) {
  delay(1);
  Wire.beginTransmission(RX8025T_ADRS);
  Wire.write(0xE0);
  Wire.write(RX8025SA_CONTROL1_REGISTOR);
  Wire.write(RX8025SA_CONTROL2_REGISTOR);
  Wire.endTransmission();
  
  Wire.beginTransmission(RX8025T_ADRS);
  Wire.write(0x00); // start register position
  Wire.write( toBCD( tm.Second)); // 0:Seconds
  Wire.write( toBCD( tm.Minute)); // 1:Minutes
  Wire.write( toBCD( tm.Hour)); // 2:Hours
  Wire.write( toBCD( tm.Wday)); // 3:Week
  Wire.write( toBCD( tm.Day)); // 4:Days
  Wire.write( toBCD( tm.Month)); // 5:Months
  Wire.write( toBCD( tm.Year)); // 6:Years
  Wire.write(0x00); // 7: digital offset ( default=32=0x20)
  Wire.endTransmission();

  
}

void RX8025SA::_write_alarm( uint8_t enable, uint8_t hour, uint8_t minute) {
  if (enable == 1){
    delay(1);
    Wire.beginTransmission(RX8025T_ADRS);
    Wire.write(0xB0); // start register position
    Wire.write(toBCD(minute)); // B:Alarm_D;Minute
    Wire.write(toBCD(hour)); // C:Alarm_D;Hour
    Wire.endTransmission();
  }

  delay(1);
  Wire.beginTransmission(RX8025T_ADRS);
  Wire.write(0xE0); // start register position
  Wire.write(RX8025SA_CONTROL1_REGISTOR | (enable << RX8025SA_DALE)); // E:Control1
  
  Wire.endTransmission();
}

/********************************************************************************/
