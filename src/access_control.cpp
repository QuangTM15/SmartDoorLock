#include <Arduino.h>

#include "access_control.h"
#include "door.h"
#include "buzzer.h"

/* ===============================
   ACCESS GRANTED
   =============================== */
void grantAccess()
{
    beepSuccess();
    openDoor();
}


/* ===============================
   ACCESS DENIED
   =============================== */
void denyAccess()
{
    beepError();
}


/* ===============================
   SYSTEM LOCKED
   =============================== */
void lockedAccess()
{
    beepAlarm();
}
