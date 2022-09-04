#include "Arduino.h"

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    char key;
    if(Serial.available() > 0)
    {
        key = Serial.read();
        Serial.println(key);
    }
    delay(100);
}
