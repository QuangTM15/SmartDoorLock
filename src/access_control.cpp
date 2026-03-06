#include <Arduino.h>

#include "access_control.h"
#include "door.h"
#include "lcd_display.h"
#include "buzzer.h"

/* ===============================
   ACCESS GRANTED
   =============================== */
void grantAccess()
{
    showAccessGranted();
    beepSuccess();

    openDoor();
}


/* ===============================
   ACCESS DENIED
   =============================== */
void denyAccess()
{
    showAccessDenied();
    beepError();
}


/* ===============================
   SYSTEM LOCKED
   =============================== */
void lockedAccess()
{
    showSystemLocked();
    beepAlarm();
}
