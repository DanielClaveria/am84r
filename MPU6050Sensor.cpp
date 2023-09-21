#include "MPU6050Sensor.h"

Adafruit_MPU6050 mpu;

MPU6050Sensor::MPU6050Sensor()
{

}

void MPU6050Sensor::init(mpu6050_accel_range_t accer_range, mpu6050_gyro_range_t gyro_range, mpu6050_bandwidth_t bandwidth)
{
    while(!mpu.begin())
    {
        delay(10);
    }
    mpu.setAccelerometerRange(accer_range);
    mpu.setGyroRange(gyro_range);
    mpu.setFilterBandwidth(bandwidth);
}

mpu6050_accel_range_t MPU6050Sensor::get_accel_range()
{
    return mpu.getAccelerometerRange();
}

mpu6050_gyro_range_t MPU6050Sensor::get_gyro_range()
{
    return mpu.getGyroRange();
}

mpu6050_bandwidth_t MPU6050Sensor::get_bandwidth()
{
    return mpu.getFilterBandwidth();
}

void MPU6050Sensor::get_event(float *accelerationX, float *accelerationY, float *accelerationZ, float *gyroX, float *gyroY, float *gyroZ, float *temp)
{
  sensors_event_t a, g, t;
  mpu.getEvent(&a, &g, &t);

    *accelerationX = a.acceleration.x;
    *accelerationY = a.acceleration.y;
    *accelerationZ = a.acceleration.z;
    *gyroX = g.gyro.x;
    *gyroY =  g.gyro.y;
    *gyroZ = g.gyro.z;
    *temp = t.temperature;
}


