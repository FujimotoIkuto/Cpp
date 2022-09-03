#include "class_led.hpp"
#include "function_wait.hpp"
#include "Arduino.h"

Led led;

void setup()
{
    led.setPinNumber(13);
}

void loop()
{
    led.turnOn();
    wait(1000);
    led.turnOff();
    wait(1000);
}
