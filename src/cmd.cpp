#include <Arduino.h>

#include "cmd.h"
#include "security.h"
#include "access_control.h"
#include "fingerprint_module.h"

void processCommand(String cmd);

void handleCommand()
{
    if (Serial.available())
    {
        String cmd = Serial.readStringUntil('\n');
        cmd.trim();

        processCommand(cmd);
    }
}

void processCommand(String cmd)
{
    int firstColon = cmd.indexOf(':');

    String command = cmd;
    String param1 = "";
    String param2 = "";

    if (firstColon != -1)
    {
        command = cmd.substring(0, firstColon);

        int secondColon = cmd.indexOf(':', firstColon + 1);

        if (secondColon == -1)
        {
            param1 = cmd.substring(firstColon + 1);
        }
        else
        {
            param1 = cmd.substring(firstColon + 1, secondColon);
            param2 = cmd.substring(secondColon + 1);
        }
    }

    command.trim();
    param1.trim();
    param2.trim();

    /* ===============================
       OPEN
       =============================== */
    if (command == "OPEN")
    {
        if (checkPassword(param1))
        {
            grantAccess();
            Serial.println("OK:DOOR_OPEN");
        }
        else
        {
            denyAccess();
            Serial.println("ERROR:WRONG_PASSWORD");
        }
    }

    /* ===============================
       CHANGE PASSWORD
       =============================== */
    else if (command == "CHANGE_PASS")
    {
        if (changePassword(param1, param2))
        {
            Serial.println("OK:PASS_CHANGED");
        }
        else
        {
            Serial.println("ERROR:PASS_CHANGE_FAILED");
        }
    }

    /* ===============================
       FINGER COUNT
       =============================== */
    else if (command == "FINGER_COUNT")
    {
        if (!isFingerprintReady())
        {
            Serial.println("ERROR:FINGERPRINT_NOT_READY");
        }
        else
        {
            Serial.print("OK:FINGER_COUNT:");
            Serial.println(getFingerCount());
        }
    }

    /* ===============================
       FINGER ADD
       FORMAT: FINGER_ADD:<password>
       =============================== */
    else if (command == "FINGER_ADD")
    {
        if (!checkPassword(param1))
        {
            Serial.println("ERROR:WRONG_PASSWORD");
        }
        else if (!isFingerprintReady())
        {
            Serial.println("ERROR:FINGERPRINT_NOT_READY");
        }
        else
        {
            uint8_t assignedId = 0;

            if (enrollFingerAuto(assignedId))
            {
                Serial.print("OK:FINGER_ADDED:");
                Serial.println(assignedId);
            }
            else
            {
                Serial.println("ERROR:FINGER_ADD_FAILED");
            }
        }
    }

    /* ===============================
       FINGER DELETE
       FORMAT: FINGER_DELETE:<password>:<id>
       =============================== */
    else if (command == "FINGER_DELETE")
    {
        if (!checkPassword(param1))
        {
            Serial.println("ERROR:WRONG_PASSWORD");
        }
        else if (!isFingerprintReady())
        {
            Serial.println("ERROR:FINGERPRINT_NOT_READY");
        }
        else
        {
            int id = param2.toInt();

            if (id <= 0 || id > 127)
            {
                Serial.println("ERROR:INVALID_FINGER_ID");
            }
            else if (deleteFinger((uint8_t)id))
            {
                Serial.print("OK:FINGER_DELETED:");
                Serial.println(id);
            }
            else
            {
                Serial.println("ERROR:FINGER_DELETE_FAILED");
            }
        }
    }

    /* ===============================
       STATUS
       =============================== */
    else if (command == "STATUS")
    {
        if (isSystemLocked())
        {
            Serial.println("OK:STATUS:LOCKED");
        }
        else
        {
            Serial.println("OK:STATUS:READY");
        }
    }

    /* ===============================
       UNKNOWN COMMAND
       =============================== */
    else
    {
        Serial.println("ERROR:INVALID_COMMAND");
    }
}
