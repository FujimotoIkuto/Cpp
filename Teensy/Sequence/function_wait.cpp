#include "function_wait.hpp"
#include "Arduino.h"

//void wait(unsigned int milliseconds)
//{
//    unsigned int start = millis(), end;
//    
//    do{
//        end = millis();
//    }while(end-start < milliseconds);
//
//    return;
//}

// bool waitWithoutWhile(unsigned int milliseconds)
// {
//     unsigned int start, end;
//     if(is_first_this_wait)
//     {
//         start = millis();
//     }
//     else if(end-start > milliseconds)
//     {
//         is_first_this_wait = true;
//         return true;
//     }
//     else
//     {
//         end = millis();
//         return false;
//     }
// }
