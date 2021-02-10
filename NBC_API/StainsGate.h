#pragma once



typedef union {
  uint8_t flag;
  struct {
    bool enable : 1;
    bool digit0 : 1;
    bool digit1 : 1;
    bool digit2 : 1;
    bool digit3 : 1;
    bool digit4 : 1;
    bool digit5 : 1;
  };
} StainsGateFlag;
