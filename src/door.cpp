#include <Arduino.h>
#include <Servo.h>

#include "door.h"
#include "pins.h"
#include "config.h"
#include "lcd_display.h"

Servo doorServo;

bool doorOpened = false;
unsigned long doorOpenTime = 0;

void initDoor()
{
    doorServo.attach(SERVO_PIN);
    doorServo.write(0);   // cửa đóng ban đầu
}

void openDoor()
{
    doorServo.write(90);  // mở cửa

    doorOpened = true;
    doorOpenTime = millis();

    showDoorOpen();
}

void closeDoor()
{
    doorServo.write(0);   // đóng cửa

    doorOpened = false;

    showDoorClosed();
}

void checkDoorTimeout()
{
    if (doorOpened && millis() - doorOpenTime >= DOOR_OPEN_TIME)
    {
        closeDoor();
    }
}