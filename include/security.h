#ifndef SECURITY_H
#define SECURITY_H

#include <Arduino.h>

/* ===============================
   SECURITY INIT
   =============================== */
void initSecurity();

/* ===============================
   PASSWORD CHECK
   =============================== */
bool checkPassword(String input);

/* ===============================
   PASSWORD CHANGE
   =============================== */
bool changePassword(String oldPass, String newPass);

/* ===============================
   FAIL MANAGEMENT
   =============================== */
void increaseFailCount();
void resetFailCount();

/* ===============================
   SYSTEM LOCK
   =============================== */
bool isSystemLocked();
void checkLockTimeout();

void factoryReset();

#endif