#include "class_led.hpp"
#include "function_wait.hpp"
#include <iostream>
#include "Arduino.h"

// Prototype Declaration
void sequence();
void printStatus();
bool isWaitingWithoutWhile(unsigned int milliseconds);

// Global Variable
bool is_first_this_wait = true;
unsigned int time_start, time_end;
int status = 0;
Led led;

using namespace std;

void setup()
{
    Serial.begin(9600);
    Serial.println("time_start");
    led.setPinNumber(13);
}

void loop()
{
    sequence();
    Serial.println("loop");
}

void sequence()
{
    switch(status)
    {
        case 0:
            printStatus();
            led.turnOn();
            if(!isWaitingWithoutWhile(500))
            {
                status = 1;
            }
            break;

        case 1:
            printStatus();
            led.turnOff();
            if(!isWaitingWithoutWhile(500))
            {
                status = 0;
            }
            break;
        
        default:
            Serial.println("error");
            break;
    }
}

void printStatus()
{
    Serial.print("status = ");
    Serial.println(status);
}

bool isWaitingWithoutWhile(unsigned int milliseconds)
{
    Serial.println("waiting");
    if(is_first_this_wait)
    {
        time_start = millis();
        is_first_this_wait = false;
    }

    time_end = millis();

    if(time_end-time_start < milliseconds)
    {
        time_end = millis();
        return true;
    }

    is_first_this_wait = true;
    return false;
}
