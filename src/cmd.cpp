#include <Arduino.h>

#include "cmd.h"
#include "security.h"
#include "access_control.h"

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