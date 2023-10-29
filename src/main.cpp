#include "main.h"

void setup() {
// write your initialization code here
    Serial.begin(9600);

    // setup for SENSOR_SCK pin
    pinMode(SENSOR_SCK, OUTPUT);
    // 重要：SCK 初始应为低电平
    // Important: SCK must be LOW initially.
    digitalWrite(SENSOR_SCK, LOW);

    // setup for SENSOR_OUT pin
    pinMode(SENSOR_OUT, INPUT);
    attachInterrupt(digitalPinToInterrupt(SENSOR_OUT), onConvertFinished, FALLING);
}

void loop() {
// write your code here
    if (sendDataFlag) {
        sendDataTask();
    }
}

void onConvertFinished() {
    noInterrupts();

    sendDataFlag = true;

    interrupts();
}

void sendDataTask() {
    if (Serial) {
        // Standardize 24-bit sensor value into MIDI CC range.
        Serial.write(byte(readSensorData()/16777215.0*127.0)); // NOLINT(*-narrowing-conversions)
        sendDataFlag = false;
    }
    else {
        delay(1);
    }
}

uint32_t readSensorData() {
    // detach interrupt for reading data
    noInterrupts();
    detachInterrupt(digitalPinToInterrupt(SENSOR_OUT));
    interrupts();

    // 延迟，对应 : DOUT 下降沿到 PD_SCK 脉冲上升沿
    // Delay for DOUT falling edge to PD_SCK pulse raising edge
    SCK_DELAY;

    uint8_t i;
    uint32_t data = 0;

    for (i = 0; i < SENSOR_DATA_LENGTH; ++i) {
        SCK_HIGH
        data <<= 1;
        SCK_DELAY
        if (digitalRead(SENSOR_OUT) == HIGH) {
            data |= 1;
        }
        SCK_LOW
    }
    for (i = 0; i < CH1_40HZ_APPEND; ++i) {
        SCK_DELAY
        SCK_HIGH
        SCK_DELAY
        SCK_LOW
    }

    // Attach interrupt for capturing ADC conversion completion.
    noInterrupts();
    attachInterrupt(digitalPinToInterrupt(SENSOR_OUT), onConvertFinished, FALLING);
    interrupts();

    C24_TO_U32(data)
    return data;
}
