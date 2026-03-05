#ifndef CONFIG_H
#define CONFIG_H

/* ===============================
   DOOR CONFIGURATION
   =============================== */
#define DOOR_OPEN_TIME 5000      // thời gian mở cửa (ms)


/* ===============================
   SECURITY CONFIGURATION
   =============================== */
#define MAX_FAIL_ATTEMPT 5       // số lần sai tối đa
#define SYSTEM_LOCK_TIME 30000   // khóa hệ thống (ms)


/* ===============================
   BUZZER CONFIGURATION
   =============================== */
#define BUZZER_SHORT_BEEP 200
#define BUZZER_LONG_BEEP 1000


/* ===============================
   PASSWORD CONFIGURATION
   =============================== */
#define PASSWORD_LENGTH 4
#define DEFAULT_PASSWORD "1234"


#endif