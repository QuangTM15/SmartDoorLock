#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int failCount = 0;

void hienthibandau() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Hay nhap van tay!!! ");
}

void xulydungVanTay() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Da mo cua");
    failCount = 0;
}

void xulysaiVanTay() {
    failCount++;
    lcd.clear();

    if (failCount > 2) {
        lcd.setCursor(0, 0);
        lcd.print("Ban da nhap sai qua 3 lan!");
        lcd.setCursor(0, 1);
        lcd.print("Vui long nhap mat khau!");
    } else {
        lcd.setCursor(0, 0);
        lcd.print("Van tay khong dung!");
        lcd.setCursor(0, 1);
        lcd.print("Vui long thu lai!");
    }
}