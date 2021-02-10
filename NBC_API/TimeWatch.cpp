#include "TimeWatch.h"



TimeWatch::TimeWatch() {
  _pause = 1;
  _elapse_time_us = 0;
}


uint32_t TimeWatch::get() {
  return _elapse_time_us;
}


void TimeWatch::pause(bool pause) {
  _pause = pause;
}


bool TimeWatch::is_pause() {
  return _pause;
}


void TimeWatch::reset() {
  _pause = 1;
  _elapse_time_us = 0;
  _b_elapse_time_us = 0;
}


void TimeWatch::update( uint32_t time_us) {
  if (_pause == true) {
    _b_time_us = time_us;
    _b_elapse_time_us = _elapse_time_us;
  }
  _elapse_time_us = _b_elapse_time_us + CalcElapseTime(time_us, _b_time_us);
}
