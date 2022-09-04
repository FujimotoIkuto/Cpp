#ifndef CLASS_LED_HPP
#define CLASS_LED_HPP

class Led
{
    private:
        int _pin_number;
    
    public:
        void setPinNumber(int pin_number);
        void turnOn();
        void turnOff();
};

#endif    // CLASS_LED_HPP