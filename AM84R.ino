#include <Arduino.h>
#include "RobotAM84R.h"


RobotAM84R myRobot;
float accelerationX, accelerationY, accelerationZ;
float gyroX, gyroY, gyroZ;
float temp;
unsigned long previousMillis = 0;
const unsigned long interval = 1000;  // Intervalo de 1 segundo

void setup() {
    IPAddress ipAddress;
    Serial.begin(115200);
    Serial.println("SETUP ESP");
    myRobot.init();
    if (myRobot.init_server("Casa", "Dacs2403", ipAddress)) {
        Serial.println("WiFi conectado");
        Serial.print("Dirección IP asignada: ");
        Serial.println(ipAddress);
    } else {
        Serial.println("Error de conexion");
    }

}


void loop() {
    
    myRobot.web_client();
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        myRobot.get_mpu_event(&accelerationX,&accelerationY,&accelerationZ,&gyroX,&gyroY,&gyroZ,&temp);

        
        // Ahora puedes usar los valores obtenidos en tu programa
        Serial.print("NAceleración X: ");
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

    }
}