#ifndef L298NCRONTROLLER_H
#define L298NCRONTROLLER_H
#include <L298NX2.h>


class L298NController {
    private:
    const unsigned int EN_A = 13;
    const unsigned int IN1_A = 4;
    const unsigned int IN2_A = 16;

    const unsigned int IN1_B = 17;
    const unsigned int IN2_B = 5;
    const unsigned int EN_B = 12;

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