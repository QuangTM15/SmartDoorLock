#include <Arduino.h>

#include "security.h"
#include "config.h"
#include "buzzer.h"

/* ===============================
   VARIABLES
   =============================== */

static String currentPassword = DEFAULT_PASSWORD;

static int failCount = 0;

static bool systemLocked = false;

static unsigned long lockStartTime = 0;


/* ===============================
   INIT
   =============================== */

void initSecurity()
{
    failCount = 0;
    systemLocked = false;
}


/* ===============================
   PASSWORD CHECK
   =============================== */

bool checkPassword(String input)
{
    if(systemLocked)
    {
        return false;
    }

    if(input == currentPassword)
    {
        resetFailCount();
        return true;
    }
    else
    {
        increaseFailCount();
        return false;
    }
}


/* ===============================
   FAIL MANAGEMENT
   =============================== */

void increaseFailCount()
{
    failCount++;

    if(failCount >= MAX_FAIL_ATTEMPT)
    {
        systemLocked = true;
        lockStartTime = millis();
        beepAlarm();
    }
}

void resetFailCount()
{
    failCount = 0;
}


/* ===============================
   SYSTEM LOCK CHECK
   =============================== */

bool isSystemLocked()
{
    return systemLocked;
}

void checkLockTimeout()
{
    if(systemLocked)
    {
        if(millis() - lockStartTime >= SYSTEM_LOCK_TIME)
        {
            systemLocked = false;
            resetFailCount();
        }
    }
}
