#include <Arduino.h>
#include "door.h"
#include "button.h"
#include "buzzer.h"
#include "security.h"
#include "cmd.h"
#include "fingerprint_module.h"

void setup()
{
    Serial.begin(9600);

    initBluetooth();
    initDoor();
    initButton();
    initBuzzer();
    initSecurity();
    initFingerprint();
}

void loop()
{
    handleCommand();       // Bluetooth command
    handleButton();        // inside button

    handleFingerprint();   // fingerprint scan

    checkDoorTimeout();    // auto close door
    checkLockTimeout();    // unlock system after timeout
}

