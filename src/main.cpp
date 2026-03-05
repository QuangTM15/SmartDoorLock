#include <Arduino.h>

#include "lcd_display.h"
#include "door.h"

void setup()
{
    initLCD();
    initDoor();

    showReady();

    delay(2000);
    openDoor();
}

void loop()
{
    checkDoorTimeout();
}