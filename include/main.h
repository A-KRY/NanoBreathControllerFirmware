//
// Created by Admin on 2023/10/29.
//

#ifndef NANOBREATHCONTROLLER_FIRMWARE_MAIN_H
#define NANOBREATHCONTROLLER_FIRMWARE_MAIN_H

#include <Arduino.h>

/**
 * @brief   <br><p>模拟输入引脚。根据您开发板的连线来修改。</p>
 * <p>Analog Input Pin. Modify according to your board connection.</p>
 * @author  A-KRY
 * @date    2023/11/1 14:06
 */
#define ANALOG_IN A7

/**
 * @brief   <br><p>最小 ADC 值。根据您传感器的情况来修改。</p>
 * <p>Minimum ADC value. Modify according to the situation of your sensor.</p>
 * @author  A-KRY
 * @date    2023/11/1 20:39
 */
#define ADC_MIN 32.0f

/**
 * @brief   <br><p>最大 ADC 值。根据您传感器的情况来修改。</p>
 * <p>Maximum ADC value. Modify according to the situation of your sensor.</p>
 * @author  A-KRY
 * @date    2023/11/1 20:40
 */
#define ADC_MAX 65.0f

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

/**
 * @brief   <br><p>承担力度曲线的功能</p>
 * <p>This function implements the force curve.</p>
 * @attention <p>对于 [0,1] 内的自变量，返回值必须属于 [0,1]</p>
 * <p>For input values within [0,1], the return value must belong to [0,1].</p>
 * @param   normalized Normalized value.
 * @return  Mapped value in range [0,1].
 * @author  A-KRY
 * @date    2023/11/2 10:21
 */
float mapper(float normalized);

#endif //NANOBREATHCONTROLLER_FIRMWARE_MAIN_H
