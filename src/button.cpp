#include <Arduino.h>

#include "button.h"
#include "pins.h"
#include "access_control.h"

const unsigned long debounceDelay = 50;

bool lastButtonState = HIGH;
bool buttonState = HIGH;

unsigned long lastDebounceTime = 0;

void initButton()
{
    pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void handleButton()
{
    bool reading = digitalRead(BUTTON_PIN);

    if (reading != lastButtonState)
    {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay)
    {
        if (reading != buttonState)
        {
            buttonState = reading;

            if (buttonState == LOW)
            {
                grantAccess(); 
            }
        }
    }

    lastButtonState = reading;
}