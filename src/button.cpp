#include <Arduino.h>
#include <Servo.h>

Servo doorServo;
const int buttonPin = 2;
const int servoPin = 9;

void setup() {
    doorServo.attach(servoPin);
    pinMode(buttonPin, INPUT_PULLUP);
    doorServo.write(0); 
}

void loop() {
    if (digitalRead(buttonPin) == LOW) {
        doorServo.write(90);
        delay(10000); 
        doorServo.write(0); 
    }
}
