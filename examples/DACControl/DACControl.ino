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

DFRobot_DAC dac;

void setup() {
  Serial.begin(115200);
  while(dac.begin() != 0){
    Serial.println("init error");
    delay(1000);
  }
  Serial.println("init succeed");
  dac.setDACOutRange(dac.eOutPutRange5V);
}

void loop(){
  dac.setDACOutVoltage(dac.eChannel1,3.5);
  delay(1000);
  dac.setDACOutVoltage(dac.eChannel2,2.5);
  delay(1000);
  dac.setDACOutVoltage(dac.eChannelAll,1.5);
  delay(1000);
}
  
