#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Adafruit_Fingerprint.h>

#include "fingerprint_module.h"
#include "pins.h"
#include "access_control.h"
#include "buzzer.h"
#include "security.h"

/* ===============================
   CONFIG
   =============================== */

static const uint32_t FINGER_BAUDRATE = 57600;
static const unsigned long SCAN_INTERVAL = 200;
static const unsigned long FINGER_REMOVE_TIMEOUT = 8000;

/* ===============================
   SENSOR OBJECT
   =============================== */

static SoftwareSerial fingerSerial(FINGER_RX, FINGER_TX);
static Adafruit_Fingerprint finger(&fingerSerial);

/* ===============================
   MODULE STATE
   =============================== */

static bool fingerprintReady = false;
static bool enrolling = false;

static unsigned long lastScan = 0;
static bool fingerPreviouslyDetected = false;

/* ===============================
   INTERNAL
   =============================== */

static int scanFinger();
static bool waitFingerRemoved();

/* ===============================
   INIT
   =============================== */

void initFingerprint()
{
    fingerprintReady = false;

    fingerSerial.begin(FINGER_BAUDRATE);
    delay(500);

    finger.begin(FINGER_BAUDRATE);
    delay(500);

    fingerSerial.listen();

    if (finger.verifyPassword())
    {
        fingerprintReady = true;
        Serial.println("OK:FINGERPRINT:READY");
    }
    else
    {
        Serial.println("ERROR:FINGERPRINT:NOT_FOUND");
    }
}

/* ===============================
   READY
   =============================== */

bool isFingerprintReady()
{
    return fingerprintReady;
}

/* ===============================
   BACKGROUND SCAN
   =============================== */

void handleFingerprint()
{
    // sensor chưa sẵn sàng hoặc đang enroll
    if (!fingerprintReady || enrolling)
        return;

    // nếu hệ thống đang lock thì không scan
    if (isSystemLocked())
        return;

    // giới hạn tần suất scan
    if (millis() - lastScan < SCAN_INTERVAL)
        return;

    lastScan = millis();

    int id = scanFinger();

    // nếu match thành công
    if (id > 0)
    {
        Serial.print("OK:FINGER_MATCH:");
        Serial.println(id);

        resetFailCount();   
        grantAccess();     
    }
}

/* ===============================
   SINGLE SCAN
   =============================== */

static int scanFinger()
{
    fingerSerial.listen();

    uint8_t p = finger.getImage();

    // không có ngón tay
    if (p == FINGERPRINT_NOFINGER)
    {
        fingerPreviouslyDetected = false;
        return -1;
    }

    // tránh trigger nhiều lần khi vẫn đặt tay
    if (fingerPreviouslyDetected)
        return -1;

    fingerPreviouslyDetected = true;

    if (p != FINGERPRINT_OK)
        return -1;

    p = finger.image2Tz(1);
    if (p != FINGERPRINT_OK)
        return -1;

    p = finger.fingerFastSearch();

    /* ===============================
       MATCH FOUND
       =============================== */
    if (p == FINGERPRINT_OK)
    {
        resetFailCount();   // reset fail counter
        return finger.fingerID;
    }

    /* ===============================
       FINGER NOT FOUND
       =============================== */
    if (p == FINGERPRINT_NOTFOUND)
    {
        Serial.println("ERROR:FINGER_NOT_FOUND");

        increaseFailCount();

        if (isSystemLocked())
        {
            lockedAccess();
        }
        else
        {
            denyAccess();
        }

        return -1;
    }

    return -1;
}

/* ===============================
   FIND EMPTY SLOT
   =============================== */

uint8_t findEmptyFingerID()
{
    if (!fingerprintReady)
        return 0;

    fingerSerial.listen();

    for (uint8_t id = 1; id <= 127; id++)
    {
        uint8_t p = finger.loadModel(id);

        if (p != FINGERPRINT_OK)
        {
            return id;
        }
    }

    return 0;
}

/* ===============================
   GET COUNT
   =============================== */

uint8_t getFingerCount()
{
    if (!fingerprintReady)
        return 0;

    fingerSerial.listen();

    if (finger.getTemplateCount() != FINGERPRINT_OK)
        return 0;

    return finger.templateCount;
}

/* ===============================
   WAIT REMOVE
   =============================== */

static bool waitFingerRemoved()
{
    Serial.println("STEP:REMOVE_FINGER");

    unsigned long start = millis();

    while (millis() - start < FINGER_REMOVE_TIMEOUT)
    {
        fingerSerial.listen();

        if (finger.getImage() == FINGERPRINT_NOFINGER)
            return true;

        delay(50);
    }

    Serial.println("ERROR:FINGER_REMOVE_TIMEOUT");
    return false;
}

/* ===============================
   ENROLL AUTO
   =============================== */

bool enrollFingerAuto(uint8_t &assignedId)
{
    assignedId = 0;

    if (!fingerprintReady)
        return false;

    enrolling = true;

    uint8_t id = findEmptyFingerID();

    if (id == 0)
    {
        Serial.println("ERROR:FINGER_MEMORY_FULL");
        enrolling = false;
        return false;
    }

    Serial.print("INFO:FINGER_NEW_ID:");
    Serial.println(id);

    Serial.println("STEP:PLACE_FINGER");

    while (finger.getImage() != FINGERPRINT_OK);

    if (finger.image2Tz(1) != FINGERPRINT_OK)
    {
        Serial.println("ERROR:TEMPLATE1_FAIL");
        enrolling = false;
        return false;
    }

    if (!waitFingerRemoved())
    {
        enrolling = false;
        return false;
    }

    Serial.println("STEP:PLACE_AGAIN");

    while (finger.getImage() != FINGERPRINT_OK);

    if (finger.image2Tz(2) != FINGERPRINT_OK)
    {
        Serial.println("ERROR:TEMPLATE2_FAIL");
        enrolling = false;
        return false;
    }

    if (finger.createModel() != FINGERPRINT_OK)
    {
        Serial.println("ERROR:CREATE_MODEL");
        enrolling = false;
        return false;
    }

    if (finger.storeModel(id) != FINGERPRINT_OK)
    {
        Serial.println("ERROR:STORE_MODEL");
        enrolling = false;
        return false;
    }

    assignedId = id;

    Serial.print("OK:FINGER_ADDED:");
    Serial.println(id);

    enrolling = false;

    return true;
}

/* ===============================
   DELETE
   =============================== */

bool deleteFinger(uint8_t id)
{
    if (!fingerprintReady)
        return false;

    if (id == 0 || id > 127)
        return false;

    fingerSerial.listen();

    uint8_t p = finger.deleteModel(id);

    if (p != FINGERPRINT_OK)
    {
        Serial.println("ERROR:FINGER_DELETE_FAILED");
        return false;
    }

    Serial.print("OK:FINGER_DELETED:");
    Serial.println(id);

    return true;
}
