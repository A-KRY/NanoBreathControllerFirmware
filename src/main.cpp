#include "main.h"

#define DEBUG(VAL) static auto str = new char[3];\
Serial.write(itoa(VAL, str, 10)); \
Serial.write('\n');

#if defined(ANALOG_IN)

void setup() {
// write your initialization code here
    Serial.begin(115200);
}

void loop() {
    sendDataTask();

    delay(100);
}

void sendDataTask() {
    if (Serial) {
        // Standardize 24-bit sensor value into MIDI CC range.
        int value = getNext();
//        DEBUG(value)
        Serial.write(value);
    }
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
uint8_t getNext() {
    float normalized = (analogRead(ANALOG_IN) - ADC_MIN) / ADC_LEN;

    if (normalized < 0) {
        return 0;
    }
    else if (normalized > 1) {
        return CC_MAX;
    }
    else {
        return normalized * CC_MAX;
    }
}
#pragma clang diagnostic pop

#endif