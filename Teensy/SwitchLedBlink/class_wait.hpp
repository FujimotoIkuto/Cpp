#ifndef CLASS_WAIT_HPP
#define CLASS_WAIT_HPP

class Wait
{
    private:
        unsigned int _start, _end;
        bool _is_first true;
    
    public:
        void wait(unsigned int milliseconds);
        bool isWaiting(unsigned int milliseconds);
};

#endif    //CLASS_WAIT_HPP