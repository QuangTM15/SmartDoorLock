#ifndef CMD_H
#define CMD_H

#include <Arduino.h>

/* ===============================
   INIT BLUETOOTH
   =============================== */
void initBluetooth();

/* ===============================
   HANDLE COMMAND
   =============================== */
void handleCommand();

/* ===============================
   SEND RESPONSE
   =============================== */
void sendResponse(String msg);

#endif