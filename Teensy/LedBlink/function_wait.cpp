#include "function_wait.hpp"
#include "Arduino.h"

void wait(unsigned int milliseconds)
{
    unsigned int start = millis(), end;
    
    do{
        end = millis();
    }while(end-start < milliseconds);

    return;
}
