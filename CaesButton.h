#pragma once

#include <Arduino.h>

class CaesButton {
  public:
    CaesButton(uint8_t pin, uint16_t debounce, uint16_t timeout);
  void update(bool enableTick);

  bool isPressed();
  bool isPressedLong();
  private:
    uint8_t _PIN = 0;
    uint8_t _DEBOUNCE = 60;
    uint8_t _TIMEOUT = 500;
    bool _ENABLETICK = true;

  bool buttonFlag;
  bool holdFlag;
  bool singleFlag;

};