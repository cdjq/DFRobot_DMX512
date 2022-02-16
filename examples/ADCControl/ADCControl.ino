/*!
 * @file DACControl.ino
 * @brief 这是一个DAC的用例，执行用例不同通道输出不同值
 * @copyright  Copyright (c) 2021 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [TangJie](jie.tang@dfrobot.com)
 * @version V1.0
 * @date 2022-02-14
 * @url https://github.com/DFRobot/DFRobot_DMX512
 */
#include "DFRobot_Peripheral.h"

DFRobot_ADC adc;

void setup() {
  Serial.begin(115200);
  while(adc.begin() != 0){
    Serial.println("init error");
    delay(1000);
  }
  Serial.println("init succeed");
}

void loop(){
  uint16_t ADCData1 = adc.getADCData(adc.eChannel1);
  uint16_t ADCData2 = adc.getADCData(adc.eChannel2);
  Serial.print("ADC1:");
  Serial.println(ADCData1);
  Serial.print("ADC2:");
  Serial.println(ADCData2);
  delay(1000);
}
  