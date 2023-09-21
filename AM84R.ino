#include <Arduino.h>
#include "MPU6050Sensor.h"

MPU6050Sensor my_mpu;
float accelerationX, accelerationY, accelerationZ;
float gyroX, gyroY, gyroZ;
float temp;

void setup() {
    Serial.begin(115200);
    Serial.println("SETUP ESP");
    my_mpu.init(MPU6050_RANGE_8_G, MPU6050_RANGE_500_DEG, MPU6050_BAND_5_HZ);
}


void loop() {
    Serial.println("loop");

    // Llamar al método get_event para obtener los datos
    my_mpu.get_event(&accelerationX, &accelerationY, &accelerationZ, &gyroX, &gyroY, &gyroZ, &temp);
    
    // Ahora puedes usar los valores obtenidos en tu programa
    Serial.print("Aceleración X: ");
    Serial.println(accelerationX);
    Serial.print("Aceleración Y: ");
    Serial.println(accelerationY);
    Serial.print("Aceleración Z: ");
    Serial.println(accelerationZ);

    Serial.print("Giro X: ");
    Serial.println(gyroX);
    Serial.print("Giro Y: ");
    Serial.println(gyroY);
    Serial.print("Giro Z: ");
    Serial.println(gyroZ);

    Serial.print("Temperatura: ");
    Serial.println(temp);

    delay(1000); 
}