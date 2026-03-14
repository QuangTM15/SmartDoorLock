#ifndef PINS_H
#define PINS_H

/* ===============================
   SERVO DOOR LOCK
   =============================== */
#define SERVO_PIN 9

/* ===============================
   BUZZER
   =============================== */
#define BUZZER_PIN 8

/* ===============================
   BUTTON (OPEN DOOR FROM INSIDE)
   =============================== */
#define BUTTON_PIN 7

/* ===============================
   FINGERPRINT SENSOR (SoftwareSerial)
   =============================== */
#define FINGER_RX 2
#define FINGER_TX 3

/* ===============================
   BLUETOOTH HC05 (SoftwareSerial)
   =============================== */
//#define BT_RX D1
//#define BT_TX D0

/* ===============================
   LCD I2C
   =============================== */
#define LCD_ADDRESS 0x27
#define LCD_COLS 16
#define LCD_ROWS 2
#define LCD_SDA A4
#define LCD_SCL A5


#endif