#pragma once
#include <Arduino.h>

#define hold 500
#define button1B 7

class Cbutton
{  
public:
    Cbutton::Cbutton(int8_t pin, boolean status);

    void setDebounce(uint16_t debounce);
    void update(bool enable);

    boolean isSingleClick();
    boolean isHoldClick();
    boolean isSpamHoldClick();
private:
    int8_t _pin;
    boolean _status;
    int8_t _debounce;
    boolean _button1S;
    boolean _button1F;
    boolean _button1R;
    boolean _button1P;
    boolean _button1H;
    boolean _button1HS;

    uint16_t debounce;

    unsigned long _button1_timer;
};

Cbutton::Cbutton(int8_t pin, boolean status)
{
    pin = _pin;
    status = _status;
    if (_status){pinMode(button1B,INPUT_PULLUP);}
    else{pinMode(button1B,INPUT);}
    
}

void Cbutton::update(bool enable)
{
    _button1S = !digitalRead(_pin);
    if (_button1S && !_button1F && !_button1H && !_button1HS && millis() - _button1_timer > debounce)
    {
        _button1F = 1;
        _button1P = 1;
        _button1_timer = millis();
    }
    if (!_button1S && _button1F && millis() - _button1_timer > debounce)
    {
        _button1R = 1;
        _button1F = 0;
        _button1_timer = millis();
    }

    if (_button1S && !_button1H && millis() - _button1_timer >= hold)
    {
        _button1H = 1;
        _button1_timer = millis();
    }
    if (_button1S && !_button1HS && millis() - _button1_timer >= hold)
    {
        _button1HS = 1;
    }
}

boolean Cbutton::isSingleClick()
{
    if(_button1P)
    return true;
    else return false;
}