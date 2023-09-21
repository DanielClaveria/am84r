#ifndef MPU6050SENSOR_H
#define MPU6050SENSOR_H
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>


class MPU6050Sensor {
private:
    Adafruit_MPU6050 mpu;

public:
    MPU6050Sensor();
    void init(mpu6050_accel_range_t accel_range, mpu6050_gyro_range_t gyro_range, mpu6050_bandwidth_t bandwidth);
    mpu6050_accel_range_t get_accel_range();
    mpu6050_gyro_range_t get_gyro_range();
    mpu6050_bandwidth_t get_bandwidth();
    void get_event(float *accelerationX, float *accelerationY, float *accelerationZ, float *gyroX, float *gyroY, float *gyroZ, float *temp);
};

#endif