#include <Arduino.h>

#include "button.h"
#include "pins.h"
#include "door.h"

bool lastButtonState = HIGH;

void initButton()
{
    pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void handleButton()
{
    bool buttonState = digitalRead(BUTTON_PIN);

    if (buttonState == LOW && lastButtonState == HIGH)
    {
        openDoor();
    }

    lastButtonState = buttonState;
}