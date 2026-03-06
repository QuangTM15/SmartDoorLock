#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

void initLCD();

/* Generic display */
void displayMessage(const char* line1, const char* line2);

/* System states */
void showReady();
void showAccessGranted();
void showAccessDenied();
void showDoorOpen();
void showDoorClosed();
void showSystemLocked();

#endif