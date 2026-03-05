#include <Arduino.h>

#include "lcd_display.h"
#include "door.h"
#include "button.h"

void setup()
{
    Serial.begin(9600);
    initLCD();
    initDoor();
    initButton();

    showReady();
}

void loop()
{
    handleButton();
    checkDoorTimeout();
}