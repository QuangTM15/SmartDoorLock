#include <Arduino.h>

#include "buzzer.h"
#include "pins.h"
#include "config.h"

void initBuzzer()
{
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, HIGH);
}

void beepSuccess()
{
    digitalWrite(BUZZER_PIN, LOW);
    delay(BUZZER_SHORT_BEEP);
    digitalWrite(BUZZER_PIN, HIGH);
}

void beepError()
{
    for(int i=0;i<2;i++)
    {
        digitalWrite(BUZZER_PIN, LOW);
        delay(BUZZER_SHORT_BEEP);

        digitalWrite(BUZZER_PIN, HIGH);
        delay(100);
    }
}

void beepAlarm()
{
    for(int i=0;i<10;i++)
    {
        digitalWrite(BUZZER_PIN, LOW);
        delay(200);

        digitalWrite(BUZZER_PIN, HIGH);
        delay(200);
    }
}