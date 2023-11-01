//
// Created by Admin on 2023/10/29.
//

#ifndef NANOBREATHCONTROLLER_FIRMWARE_MAIN_H
#define NANOBREATHCONTROLLER_FIRMWARE_MAIN_H

#include <Arduino.h>

/**
 * @brief   <br><p>模拟输入引脚</p>
 * <p>Analog Input Pin</p>
 * @author  A-KRY
 * @date    2023/11/1 14:06
 */
#define ANALOG_IN A7

/**
 * @brief   <br><p>最小 ADC 值</p>
 * <p>Minimum ADC value</p>
 * @author  A-KRY
 * @date    2023/11/1 20:39
 */
#define ADC_MIN 32.0f

/**
 * @brief   <br><p>最大 ADC 值</p>
 * <p>Maximum ADC value</p>
 * @author  A-KRY
 * @date    2023/11/1 20:40
 */
#define ADC_MAX 80.0f

/**
 * @brief   <br><p>ADC 区间长度</p>
 * <p>Length of ADC range.</p>
 * @author  A-KRY
 * @date    2023/11/1 20:47
 */
#define ADC_LEN (ADC_MAX-ADC_MIN)

/**
 * @brief   <br><p>MIDI CC 取值区间长度</p>
 * <p>Length of MIDI CC range.</p>
 * @author  A-KRY
 * @date    2023/11/1 20:52
 */
#define CC_LEN 127.0f

#define CC_MAX CC_LEN

/**
 * @brief   <br><p>发送 MIDI CC 的值</p>
 * <p>Send value of MIDI CC.</p>
 * @param
 * @return
 * @author  A-KRY
 * @date    2023/10/29 14:05
 */
void sendDataTask();

 /**
  * @brief   <br><p>标准化 ADC 输出至 MIDI CC 范围</p>
  * <p>Standardize ADC output to MIDI CC range.</p>
  * @param
  * @return
  * @author  A-KRY
  * @date    2023/11/1 20:45
  */
uint8_t getNext();

#endif //NANOBREATHCONTROLLER_FIRMWARE_MAIN_H
