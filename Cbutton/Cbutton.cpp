#include <Arduino.h>
#include <Controlbutton.h>

Cbutton::Cbutton(int8_t pin)
{
    pin = _pin;
}

void update(bool enable)
{
  if (button1S && !button1F && !button1H && !button1HS && millis() - button1_timer > debounce)
  {
    button1F = 1;
    button1P = 1;
    button1_timer = millis();
  }
}

