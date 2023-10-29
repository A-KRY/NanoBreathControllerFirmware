//
// Created by Admin on 2023/10/29.
//

#ifndef NANOBREATHCONTROLLER_FIRMWARE_MAIN_H
#define NANOBREATHCONTROLLER_FIRMWARE_MAIN_H

#include <Arduino.h>

/**
 * @brief   <br><p>TM7711 SCK 所连接的 Arduino Nano 的引脚</p>
 * <p>The pin of Arduino Nano connected by SCK of TM7711</p>
 * @author  A-KRY
 * @date    2023/10/29 14:03
 */
#define SENSOR_SCK PD2

/**
 * @brief   <br><p>TM7711 DOUT 所连接的 Arduino Nano 的引脚</p>
 * <p>The pin of Arduino Nano connected by DOUT of TM7711</p>
 * @author  A-KRY
 * @date    2023/10/29 14:03
 */
#define SENSOR_OUT PD3

/**
 * @brief   <br><p>当 TM7711 转化完成时，DOUT 降至 LOW</p>
 * <p>When conversion of TM7711 finished, DOUT drops to LOW.</p>
 * @author  A-KRY
 * @date    2023/10/29 13:59
 */
void onConvertFinished();

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
* @brief   <br><p>sendDataTask 的任务标志</p>
* <p>Flag for sendDataTask</p>
* @author  A-KRY
* @date    2023/10/29 14:06
*/
bool sendDataFlag = false;

/**
 * @brief   <br><p>读取 TM7711 的值</p>
 * <p>Read value from TM7711</p>
 * @param   
 * @return  <br><p>ADC</p>
 * @author  A-KRY
 * @date    2023/10/29 14:14
 */
uint32_t readSensorData();

/**
 * @brief   <br><p>TM7711 数据长度</p>
 * <p>Data length of TM7711.</p>
 * @author  A-KRY
 * @date    2023/10/29 16:29
 */
#define SENSOR_DATA_LENGTH 24

/**
 * @brief   <br><p>TM7711 <b>差分信号-10Hz</b> 模式所追加的 SCK 脉冲数</p>
 * <p>Number of SCK pulses to append in <<b>Differential Signal-10Hz</b> mode.</p>
 * @author  A-KRY
 * @date    2023/10/29 16:35
 */
#define CH1_10HZ_APPEND 1

/**
 * @brief   <br><p>TM7711 <b>差分信号-40Hz</b> 模式所追加的 SCK 脉冲数</p>
 * <p>Number of SCK pulses to append in <<b>Differential Signal-40Hz</b> mode.</p>
 * @author  A-KRY
 * @date    2023/10/29 16:32
 */
#define CH1_40HZ_APPEND 3

#define SCK_HIGH digitalWrite(SENSOR_SCK, HIGH);
#define SCK_LOW digitalWrite(SENSOR_SCK, LOW);
#define SCK_DELAY delayMicroseconds(1);

/**
 * @brief   <br><p>从 24 位补码获取 32 位无符号数</p>
 * <p>Get unsigned 32-bit from 24-bit complement</p>
 * @warning <p>VAL 必须为 32 位整型</p>
 * <p>VAL must be a 32-bit integer.</p>
 * @author  A-KRY
 * @date    2023/10/29 14:41
 */
#define C24_TO_U32(VAL) \
    if (((VAL)>>23)&0x1) {                                                                                                \
        VAL |= 0xFF000000;                                                                                                \
    }                                                                                                                     \
    VAL += 1UL<<23;

#endif //NANOBREATHCONTROLLER_FIRMWARE_MAIN_H
