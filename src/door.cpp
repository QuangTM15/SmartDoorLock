#include <Arduino.h>
#include <Servo.h>

#include "door.h"
#include "pins.h"
#include "config.h"

Servo doorServo;

bool doorOpened = false;
unsigned long doorOpenTime = 0;

void initDoor()
{
    doorServo.attach(SERVO_PIN);
    doorServo.write(0); 
}

void openDoor()
{
    doorServo.write(90);  
    doorOpened = true;
    doorOpenTime = millis();
}

void closeDoor()
{
    doorServo.write(0);   
    doorOpened = false;
}

void checkDoorTimeout()
{
    if (doorOpened && millis() - doorOpenTime >= DOOR_OPEN_TIME)
    {
        closeDoor();
    }
}