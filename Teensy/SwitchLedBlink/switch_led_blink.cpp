#include "class_led.hpp"
#include "class_wait.hpp"
#include "Arduino.h"

// Prototype Declaration
void sequence();
void changeStatus();

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
}

// Sequence
void sequence()
{
    changeStatus();
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
        
        case 2:
            led.turnOn();
            if(!wait.isWaiting(1000))
            {
                status = 3;
            }
            break;

        case 3:
            led.turnOff();
            if(!wait.isWaiting(1000))
            {
                status = 2;
            }
            break;
        
        default:
            Serial.println("error");
            status = 0;
            break;
    }
}

// Function
void changeStatus()
{
    if(Serial.available() > 0)
    {
        char key = Serial.read();

        if(key == 'u')
        {
            status += 2;
            Serial.println("change");
        }
        else if(key == 'd')
        {
            status -= 2;
            Serial.println("change");
        }
    }
}