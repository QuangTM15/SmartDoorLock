#include <Arduino.h>

#include "cmd.h"
#include "security.h"
#include "access_control.h"
#include "fingerprint_module.h"

/* ===============================
   INIT BLUETOOTH
   =============================== */

void initBluetooth()
{
    Serial.println("Bluetooth Ready");
}

/* ===============================
   SEND RESPONSE
   =============================== */

void sendResponse(String msg)
{
    Serial.println(msg);
}

/* ===============================
   PROCESS COMMAND
   =============================== */

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
            sendResponse("OK:DOOR_OPEN");
        }
        else
        {
            denyAccess();
            sendResponse("ERROR:WRONG_PASSWORD");
        }
    }

    /* ===============================
       CHANGE PASSWORD
       =============================== */

    else if (command == "CHANGE_PASS")
    {
        if (changePassword(param1, param2))
        {
            sendResponse("OK:PASS_CHANGED");
        }
        else
        {
            sendResponse("ERROR:PASS_CHANGE_FAILED");
        }
    }

    /* ===============================
       FINGER COUNT
       =============================== */

    else if (command == "FINGER_COUNT")
    {
        if (!isFingerprintReady())
        {
            sendResponse("ERROR:FINGERPRINT_NOT_READY");
        }
        else
        {
            sendResponse("OK:FINGER_COUNT:" + String(getFingerCount()));
        }
    }

    /* ===============================
       FINGER ADD
       =============================== */

    else if (command == "FINGER_ADD")
    {
        if (!checkPassword(param1))
        {
            sendResponse("ERROR:WRONG_PASSWORD");
        }
        else if (!isFingerprintReady())
        {
            sendResponse("ERROR:FINGERPRINT_NOT_READY");
        }
        else
        {
            uint8_t assignedId = 0;

            if (enrollFingerAuto(assignedId))
            {
                sendResponse("OK:FINGER_ADDED:" + String(assignedId));
            }
            else
            {
                sendResponse("ERROR:FINGER_ADD_FAILED");
            }
        }
    }

    /* ===============================
       FINGER DELETE
       =============================== */

    else if (command == "FINGER_DELETE")
    {
        if (!checkPassword(param1))
        {
            sendResponse("ERROR:WRONG_PASSWORD");
        }
        else if (!isFingerprintReady())
        {
            sendResponse("ERROR:FINGERPRINT_NOT_READY");
        }
        else
        {
            int id = param2.toInt();

            if (id <= 0 || id > 127)
            {
                sendResponse("ERROR:INVALID_FINGER_ID");
            }
            else if (deleteFinger((uint8_t)id))
            {
                sendResponse("OK:FINGER_DELETED:" + String(id));
            }
            else
            {
                sendResponse("ERROR:FINGER_DELETE_FAILED");
            }
        }
    }

    /* ===============================
       FACTORY RESET
       =============================== */

    else if (command == "RESET")
    {
        if (!checkPassword(param1))
        {
            sendResponse("ERROR:WRONG_PASSWORD");
        }
        else
        {
            factoryReset();
            sendResponse("OK:FACTORY_RESET_DONE");
        }
    }

    /* ===============================
       STATUS
       =============================== */

    else if (command == "STATUS")
    {
        if (isSystemLocked())
        {
            sendResponse("OK:STATUS:LOCKED");
        }
        else
        {
            sendResponse("OK:STATUS:READY");
        }
    }

    /* ===============================
       UNKNOWN COMMAND
       =============================== */

    else
    {
        sendResponse("ERROR:INVALID_COMMAND");
    }
}

/* ===============================
   HANDLE COMMAND
   =============================== */

void handleCommand()
{
    if (Serial.available())
    {
        String cmd = Serial.readString();
        cmd.trim();

        if (cmd.length() > 0)
        {
            processCommand(cmd);
        }
    }
}
