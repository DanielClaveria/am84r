#ifndef ROBOTAM84R_H
#define ROBOTAM84R_H

#include <WiFi.h>
#include "MPU6050Sensor.h"
#include "L298NController.h"

class RobotAM84R {
private:
    MPU6050Sensor robot_mpu;
    L298NController robot_motors;
    WiFiServer server;
    String header;
    String outState;
    const int out = 2;
    int contconexion = 0;

public:
    RobotAM84R();
    void init();
    void init_mpu_sensor();
    void get_mpu_event(float *accelerationX, float *accelerationY, float *accelerationZ, float *gyroX, float *gyroY, float *gyroZ, float *temp);
    bool init_server(char *pssid, char *ppassword, IPAddress& ipAddress);
    void web_client();
    void init_motors();
    void forward();
    void backward();
    void left();
    void right();
    void stop();
    void see0();
    void see90();
    void see180();
    void distance();
};

#endif