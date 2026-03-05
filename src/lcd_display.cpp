#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "pins.h"
#include "lcd_display.h"

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLS, LCD_ROWS);

void initLCD()
{
    // lcd.init();
    // lcd.backlight();
    Serial.println("LCD INIT");
}

void showReady()
{
    // lcd.clear();
    // lcd.setCursor(0,0);
    // lcd.print("Smart Door Lock");
    // lcd.setCursor(0,1);
    // lcd.print("Scan Finger...");
     Serial.println("System Ready - Scan Finger");
}

void showAccessGranted()
{
    // lcd.clear();
    // lcd.setCursor(0,0);
    // lcd.print("Access Granted");
    Serial.println("Access Granted");
}

void showAccessDenied()
{
    // lcd.clear();
    // lcd.setCursor(0,0);
    // lcd.print("Access Denied");
    Serial.println("Access Denied");
}

void showDoorOpen()
{
    // lcd.clear();
    // lcd.setCursor(0,0);
    // lcd.print("Door Open");
    Serial.println("Door Open");
}

void showDoorClosed()
{
    // lcd.clear();
    // lcd.setCursor(0,0);
    // lcd.print("Door Closed");
    Serial.println("Door Close");
}

void showSystemLocked()
{
    // lcd.clear();
    // lcd.setCursor(0,0);
    // lcd.print("System Locked!");
    Serial.println("System Locked!");
}