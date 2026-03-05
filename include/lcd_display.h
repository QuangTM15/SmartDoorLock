#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H
#include <LiquidCrystal_I2C.h>

extern LiquidCrystal_I2C lcd;

void initLCD();

void showReady();
void showAccessGranted();
void showAccessDenied();
void showDoorOpen();
void showDoorClosed();
void showSystemLocked();

#endif