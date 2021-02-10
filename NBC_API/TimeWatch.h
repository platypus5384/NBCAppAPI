#pragma once

#include <Arduino.h>
#include "Common.h"


class TimeWatch {
  private:
    bool _pause;
    uint32_t _b_time_us;
    uint32_t _elapse_time_us;
    uint32_t _b_elapse_time_us;
  public:
    TimeWatch();
    ~TimeWatch(){};

    uint32_t get();
    void update( uint32_t time_us);
    
    void pause(bool pause);
    bool is_pause();
    void reset();
};
