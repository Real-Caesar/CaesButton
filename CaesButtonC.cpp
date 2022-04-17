#include "CaesButton.h"

CaesButton::CaesButton(uint8_t pin, uint16_t debounce, uint16_t timeout) {
  _PIN = pin;
  _DEBOUNCE = debounce;
  _TIMEOUT = timeout;
  pinMode(_PIN, INPUT_PULLUP);
}
void CaesButton::update(bool enableTick) {
  _ENABLETICK = enableTick;
  if (_ENABLETICK == true) {
    uint16_t firstButtonPressTime;
    uint16_t previousHoldingTime;

    bool previousButtonState = false;
    bool buttonState;

    buttonState = !digitalRead(_PIN);
    if (buttonState == HIGH && previousButtonState == false && (millis() - firstButtonPressTime) > _DEBOUNCE) {
      buttonFlag = true;
      firstButtonPressTime = millis();
    }
    if (buttonState == false && previousButtonState == true) {
      holdFlag = false;
      singleFlag = false;
      buttonFlag = false;
    }
    uint16_t holdingTime = (millis() - firstButtonPressTime);

    if (holdingTime > _DEBOUNCE) {
      if (buttonState == false && previousButtonState == true) {
        if (holdingTime <= _TIMEOUT) {
          singleFlag = true;
        }
        if (holdingTime > _TIMEOUT) {
        Serial.println("Click");
          holdFlag = true;
        }
      }
    }
    previousButtonState = buttonState;
    previousHoldingTime = holdingTime;
  } else return;
};

boolean CaesButton::isPressed() {
CaesButton::update(true);
  if (singleFlag == true)
  {return true;} 
  else return false;
  
}
boolean CaesButton::isPressedLong() {
CaesButton::update(true);
  if (holdFlag == true) {
    return true;
  } else return false;
}