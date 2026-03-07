#include <Arduino.h>

#include "lcd_display.h"
#include "door.h"
#include "button.h"
#include "buzzer.h"
#include "security.h"
#include "cmd.h"
#include "fingerprint_module.h"

void setup()
{
    Serial.begin(9600);

    initLCD();
    initDoor();
    initButton();
    initBuzzer();
    initSecurity();
    initFingerprint();

    showReady();

    Serial.println("===== SMART DOOR LOCK READY =====");
}

void loop()
{
    handleCommand();
    handleButton();
    handleFingerprint();

    checkDoorTimeout();
    checkLockTimeout();
}
