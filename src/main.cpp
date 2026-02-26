#include <Arduino.h>

void setup() {
  Serial.begin(9600);
  Serial.println("Smart Door Lock Test Start");
}

void loop() {
  Serial.println("System Running...");
  delay(2000);
}