#include <Arduino.h>
#include <EEPROM.h>

#include "security.h"
#include "config.h"
#include "buzzer.h"
#include "fingerprint_module.h"

/* ===============================
   VARIABLES
   =============================== */

static char currentPassword[PASSWORD_LENGTH + 1];

static int failCount = 0;

static bool systemLocked = false;

static unsigned long lockStartTime = 0;


/* ===============================
   LOAD PASSWORD FROM EEPROM
   =============================== */

void loadPassword()
{
    char buffer[PASSWORD_LENGTH + 1];

    // đọc EEPROM
    for (int i = 0; i < PASSWORD_LENGTH; i++)
    {
        buffer[i] = EEPROM.read(i);
    }

    buffer[PASSWORD_LENGTH] = '\0';

    // kiểm tra password hợp lệ
    bool valid = true;

    for (int i = 0; i < PASSWORD_LENGTH; i++)
    {
        if (buffer[i] < '0' || buffer[i] > '9')
        {
            valid = false;
            break;
        }
    }

    if (!valid)
    {
        // EEPROM chứa dữ liệu rác -> reset password
        strcpy(currentPassword, DEFAULT_PASSWORD);

        for (int i = 0; i < PASSWORD_LENGTH; i++)
        {
            EEPROM.write(i, currentPassword[i]);
        }
    }
    else
    {
        // EEPROM hợp lệ
        strcpy(currentPassword, buffer);
    }
    Serial.println(currentPassword);
}

/* ===============================
   INIT
   =============================== */

void initSecurity()
{
    failCount = 0;
    systemLocked = false;

    loadPassword();
}


/* ===============================
   PASSWORD CHECK
   =============================== */

bool checkPassword(String input)
{
    if (systemLocked)
        return false;

    char inputBuffer[PASSWORD_LENGTH + 1];
    input.toCharArray(inputBuffer, PASSWORD_LENGTH + 1);

    if (strcmp(inputBuffer, currentPassword) == 0)
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
   CHANGE PASSWORD
   =============================== */

bool changePassword(String oldPass, String newPass)
{
    if (systemLocked)
        return false;

    char oldBuffer[PASSWORD_LENGTH + 1];
    char newBuffer[PASSWORD_LENGTH + 1];

    oldPass.toCharArray(oldBuffer, PASSWORD_LENGTH + 1);
    newPass.toCharArray(newBuffer, PASSWORD_LENGTH + 1);

    if (strcmp(oldBuffer, currentPassword) != 0)
        return false;

    if (strlen(newBuffer) != PASSWORD_LENGTH)
        return false;

    strcpy(currentPassword, newBuffer);

    for (int i = 0; i < PASSWORD_LENGTH; i++)
    {
        EEPROM.write(i, currentPassword[i]);
    }

    resetFailCount();

    return true;
}


/* ===============================
   FAIL MANAGEMENT
   =============================== */

void increaseFailCount()
{
    failCount++;

    if (failCount >= MAX_FAIL_ATTEMPT)
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
   SYSTEM LOCK
   =============================== */

bool isSystemLocked()
{
    return systemLocked;
}

void checkLockTimeout()
{
    if (systemLocked)
    {
        if (millis() - lockStartTime >= SYSTEM_LOCK_TIME)
        {
            systemLocked = false;
            resetFailCount();
        }
    }
}

void factoryReset()
{
    // reset password về mặc định
    strcpy(currentPassword, DEFAULT_PASSWORD);

    for (int i = 0; i < PASSWORD_LENGTH; i++)
    {
        EEPROM.write(i, currentPassword[i]);
    }

    // reset fail
    resetFailCount();
    systemLocked = false;

    // xóa toàn bộ fingerprint
    for (int id = 1; id <= 127; id++)
    {
        deleteFinger(id);
    }
}