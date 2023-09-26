#ifndef ROBOTAM84R_H
#define ROBOTAM84R_H

#include <WiFi.h>
#include "MPU6050Sensor.h"
#include "L298NController.h"
#define TRIG_PIN 15 // ESP32 pin GPIO23 connected to Ultrasonic Sensor's TRIG pin OUT
#define ECHO_PIN 2 // ESP32 pin GPIO22 connected to Ultrasonic Sensor's ECHO pin IN

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
    void init_echo();
    float get_distance();
};

#endif