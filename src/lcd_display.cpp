#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "pins.h"
#include "lcd_display.h"

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLS, LCD_ROWS);


/* ===============================
   INIT
   =============================== */

void initLCD()
{
    lcd.init();
    lcd.backlight();
    Serial.println("LCD INIT");
}


/* ===============================
   GENERIC DISPLAY
   =============================== */

void displayMessage(const char* line1, const char* line2)
{
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print(line1);

    lcd.setCursor(0,1);
    lcd.print(line2);
}

/* ===============================
   SYSTEM STATES
   =============================== */

void showReady()
{
    displayMessage("Smart Door Lock", "Scan Finger...");
    Serial.println("System Ready - Scan Finger");
}

void showAccessGranted()
{
    displayMessage("Access Granted", "");
    Serial.println("Access Granted");
}

void showAccessDenied()
{
    displayMessage("Access Denied", "");
    Serial.println("Access Denied");
}

void showDoorOpen()
{
    displayMessage("Door Open", "");
    Serial.println("Door Open");
}

void showDoorClosed()
{
    displayMessage("Door Closed", "");
    Serial.println("Door Closed");
}

void showSystemLocked()
{
    displayMessage("System Locked!", "");
    Serial.println("System Locked!");
}