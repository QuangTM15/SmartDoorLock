#include <Arduino.h>

#include "lcd_display.h"
#include "door.h"
#include "button.h"
#include "buzzer.h"
#include "security.h"

void setup()
{
    Serial.begin(9600);
    initLCD();
    initDoor();
    initButton();
    initBuzzer();
    initSecurity();

    showReady();
}

void loop()
{
    handleButton();
    checkDoorTimeout();
    checkLockTimeout();
}
