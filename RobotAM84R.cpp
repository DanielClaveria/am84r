
#include "RobotAM84R.h"
const char *name;
MPU6050Sensor robot_mpu;
L298NController robot_motors;
WiFiServer server(80);
const char *ssid;
const char *password;
String header;
String outState = "off";
const int out = 2;
int contconexion = 0;
float distance = 500;


RobotAM84R::RobotAM84R()
{
    name = "AM84R";
}

void RobotAM84R::init()
{

    init_motors();
    init_echo();
    init_mpu_sensor();
}

void RobotAM84R::init_mpu_sensor()
{
    robot_mpu.init(MPU6050_RANGE_8_G, MPU6050_RANGE_500_DEG, MPU6050_BAND_5_HZ);
}

void RobotAM84R::get_mpu_event(float *accelerationX, float *accelerationY, float *accelerationZ, float *gyroX, float *gyroY, float *gyroZ, float *temp)
{
    robot_mpu.get_event(accelerationX, accelerationY, accelerationZ, gyroX, gyroY, gyroZ, temp);
}

bool RobotAM84R::init_server(char *pssid, char *ppassword, IPAddress& ipAddress) {
        ssid = pssid;
        password = ppassword;
        WiFi.begin(ssid, password);
        while (WiFi.status() != WL_CONNECTED and contconexion < 50) {
            ++contconexion;
            delay(500);
        }
        if (contconexion < 50) {
            server.begin();
            ipAddress = WiFi.localIP(); // Obtener y asignar la dirección IP
            return true; // WiFi conectado con éxito
        } else {
            return false; // Error de conexión
        }
    }

void RobotAM84R::web_client()
{
    String html = "<!DOCTYPE html>"
              "<html>"
              "<head>"
              "<meta charset='utf-8' />"
              "<title>Servidor Web ESP32</title>"
              "</head>"
              "<body>"
              "<center>"
              "<h1>Servidor Web ESP32</h1>"
              "<table>"
              "<tr><td></td><td><a href='/forward'><button style='height:50px;width:100px'>FORWARD</button></a></td><td></td>"
              "<tr><td><a href='/left'><button style='height:50px;width:100px'>LEFT</button></a></td><td><a href='/stop'><button style='height:50px;width:100px'>STOP</button></a></td><td><a href='/right'><button style='height:50px;width:100px'>RIGHT</button></a></td>"
              "<tr><td></td><td><a href='/backward'><button style='height:50px;width:100px'>BACKWARD</button></a></td><td></td>"
        //      "<tr><td><a href='/see0'><button style='height:50px;width:100px'>SEE 0°</button></a></td><td><a href='/see90'><button style='height:50px;width:100px'>SEE 90°</button></a></td><td><a href='/see180'><button style='height:50px;width:100px'>SEE 180°</button></a></td>"
              "<tr><td></td><td><a href='/distance'><button style='height:50px;width:100px'>DISTANCE</button></a></td><td></td>"
              "<tr><td></td><td>DISTANCE" + String(distance) + "</button></a></td><td></td>"
              "</table>"
              "</center>"
              "</body>"
              "</html>";
    WiFiClient client = server.available(); // Escucha a los clientes entrantes

    if (client)
    {                                  // Si se conecta un nuevo cliente
        String currentLine = "";       //
        while (client.connected())
        { // loop mientras el cliente está conectado
            if (client.available())
            {                           // si hay bytes para leer desde el cliente
                char c = client.read(); // lee un byte
                header += c;
                if (c == '\n')
                { // si el byte es un caracter de salto de linea
                    // si la nueva linea está en blanco significa que es el fin del
                    // HTTP request del cliente, entonces respondemos:
                    if (currentLine.length() == 0)
                    {
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println("Connection: close");
                        client.println();

                        // enciende y apaga el GPIO
                        if (header.indexOf("GET /forward") >= 0)
                        {
                            forward();
                        }
                        else if (header.indexOf("GET /backward") >= 0)
                        {
                            backward();
                        }
                        else if (header.indexOf("GET /left") >= 0)
                        {
                            left();
                        }
                        else if (header.indexOf("GET /right") >= 0)
                        {
                            right();
                        }
                        else if (header.indexOf("GET /stop") >= 0)
                        {
                            stop();
                        }
                        else if (header.indexOf("GET /distance") >= 0)
                        {
                            distance = get_distance();
                        }
                        // Muestra la página web
                        client.println(html);

                        // la respuesta HTTP temina con una linea en blanco
                        client.println();
                        break;
                    }
                    else
                    { // si tenemos una nueva linea limpiamos currentLine
                        currentLine = "";
                    }
                }
                else if (c != '\r')
                {                     // si C es distinto al caracter de retorno de carro
                    currentLine += c; // lo agrega al final de currentLine
                }
            }
        }
        // Limpiamos la variable header
        header = "";
        // Cerramos la conexión
        client.stop();
    }
}

void RobotAM84R::init_motors()
{
    robot_motors.init();
}

void RobotAM84R::forward()
{
    robot_motors.forward();
}
void RobotAM84R::backward()
{
    robot_motors.backward();
}
void RobotAM84R::left()
{
    robot_motors.left();
}
void RobotAM84R::right()
{
    robot_motors.right();
}
void RobotAM84R::stop()
{
    robot_motors.stop();
}

void RobotAM84R::init_echo()
{
    pinMode(TRIG_PIN, OUTPUT);
    // configure the echo pin to input mode
    pinMode(ECHO_PIN, INPUT);
}
float RobotAM84R::get_distance()
{
    float duration_us, distance_cm;
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // measure duration of pulse from ECHO pin
    duration_us = pulseIn(ECHO_PIN, HIGH);

    // calculate the distance
    distance_cm = 0.017 * duration_us;
    return distance_cm;
}