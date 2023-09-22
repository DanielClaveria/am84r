#include "L298NController.h"

const unsigned int EN_A = 12;
const unsigned int IN1_A = 14;
const unsigned int IN2_A = 27;

const unsigned int IN1_B = 26;
const unsigned int IN2_B = 25;
const unsigned int EN_B = 33;

L298NX2 motors(EN_A, IN1_A, IN2_A, EN_B, IN1_B, IN2_B);

L298NController::L298NController()
{

}   

void L298NController::init()
{
    //motors = L298NX2(pEN_A, pIN1_A, pIN2_A, pEN_B, pIN1_B, pIN2_B);
}


void L298NController::set_speed(unsigned short pwmSpeed)
{
    motors.setSpeed(pwmSpeed);
}

void L298NController::forward()
{
    motors.forward();
}

void L298NController::backward()
{
    motors.backward();
}

void L298NController::left()
{
    motors.backwardA();
    motors.forwardB();
}

void L298NController::right()
{
    motors.backwardB();
    motors.forwardA();
}

void L298NController::stop()
{
    motors.stop();
}