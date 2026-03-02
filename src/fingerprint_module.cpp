#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setupFingerprint() {
    finger.begin(57600);
    if (!finger.verifyPassword()) {
        Serial.println("Khong tim thay cam bien AS608!");
        while (1) { delay(1); }
    }
}

int getFingerprintID() {
    uint8_t p = finger.getImage();
    if (p == FINGERPRINT_NOFINGER) return -2; 
    if (p != FINGERPRINT_OK) return -1;

    p = finger.image2Tz();
    if (p != FINGERPRINT_OK) return -1;

    p = finger.fingerFastSearch();
    if (p == FINGERPRINT_OK) {
        return finger.fingerID; 
    }

    return -1; 
}