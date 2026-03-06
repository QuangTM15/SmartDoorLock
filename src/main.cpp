#include <Arduino.h>

#include "lcd_display.h"
#include "door.h"
#include "button.h"
#include "buzzer.h"
#include "security.h"
#include "access_control.h"

void setup()
{
    Serial.begin(9600);

    initLCD();
    initDoor();
    initButton();
    initBuzzer();
    initSecurity();

    showReady();

    Serial.println("System Initialized");
}

void loop()
{
    /* INPUT */
    handleButton();       

    /* SYSTEM CHECK */
    checkDoorTimeout();    
    checkLockTimeout();   
}