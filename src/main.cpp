#include "main.h"

#define DEBUG(VAL) static auto str = new char[10];\
Serial.write(itoa(VAL, str, 10)); \
Serial.write('\n');

#if defined(ANALOG_IN)

void setup() {
// write your initialization code here
    /**
     * @attention <p>切记开发板波特率要与上位机驱动匹配！</p>
     * <p>Remember to match the development board's baud rate with the upper computer driver!</p>
     */
    Serial.begin(115200);
}

void loop() {
    sendDataTask();

    delay(75);
}

void sendDataTask() {
    if (Serial) {
        // Standardize 24-bit sensor value into MIDI CC range.
        uint8_t value = getNext();
//        DEBUG(value)
        Serial.write(value);
    }
}

uint8_t getNext() {
    float normalized = (analogRead(ANALOG_IN) - ADC_MIN) / ADC_LEN;

    if (normalized < 0.0f) {
        return 0;
    }
    else if (normalized > 1.0f) {
        return CC_MAX;
    }
    else {
        return mapper(normalized) * CC_MAX;  // NOLINT(*-narrowing-conversions)
    }
}

float mapper(float normalized) {
        return 1.0f- logf(1.0f+ expf(0.5f-5.5f*normalized)); // NOLINT(*-narrowing-conversions)
}

#endif