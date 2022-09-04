#include "class_led.hpp"
#include "class_wait.hpp"
#include "Arduino.h"

// Prototype Declaration
void sequence();

// Global Variable
int status = 0;

// Object
Led led;
Wait wait;

// Name Space
using namespace std;

// Set Up
void setup()
{
    Serial.begin(9600);
    led.setPinNumber(13);
}

// Loop
void loop()
{
    sequence();
    Serial.println("loop");
}

// Sequence
void sequence()
{
    switch(status)
    {
        case 0:
            led.turnOn();
            if(!wait.isWaiting(500))
            {
                status = 1;
            }
            break;

        case 1:
            led.turnOff();
            if(!wait.isWaiting(500))
            {
                status = 0;
            }
            break;
        
        default:
            Serial.println("error");
            break;
    }
}