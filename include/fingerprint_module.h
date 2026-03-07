#ifndef FINGERPRINT_MODULE_H
#define FINGERPRINT_MODULE_H

#include <Arduino.h>

void initFingerprint();
void handleFingerprint();

bool isFingerprintReady();

bool enrollFingerAuto(uint8_t &assignedId);
bool deleteFinger(uint8_t id);

uint8_t getFingerCount();
uint8_t findEmptyFingerID();

#endif