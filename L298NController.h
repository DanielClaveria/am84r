#ifndef L298NCRONTROLLER_H
#define L298NCRONTROLLER_H
#include <L298NX2.h>


class L298NController {
    private:
    const unsigned int EN_A = 12;
    const unsigned int IN1_A = 14;
    const unsigned int IN2_A = 27;

    const unsigned int IN1_B = 26;
    const unsigned int IN2_B = 25;
    const unsigned int EN_B = 33;


    public:
        L298NController();
        void init();
        void set_speed(unsigned short pwmSpeed);
        void forward();
        void backward();
        void left();
        void right();
        void stop();
        
};

#endif