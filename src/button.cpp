#include <Arduino.h>
#include <Servo.h>

Servo doorServo;
const int servoPin = 9;
void initDoor()
{
    doorServo.attach(servoPin);
    doorServo.write(0);
}

void openDoor()
{
    doorServo.write(90);
    delay(5000);
    doorServo.write(0);
}


