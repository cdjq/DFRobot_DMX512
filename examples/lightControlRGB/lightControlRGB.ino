/*!
 * @file lightControlLED.ino
 * @brief 这是一个使用DMX512控制RGB灯的用例
 * @copyright  Copyright (c) 2021 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [TangJie](jie.tang@dfrobot.com)
 * @version V1.0
 * @date 2022-02-14
 * @url https://github.com/DFRobot/DFRobot_DMX512
 */
#include "DFRobot_DMX512.h"

DFRobot_DMX512 dmx512;

void setup() {
    Serial.begin(115200);
    dmx512.begin();
    dmx512.rgbOff(1,10);
}

void loop() {
  dmx512.rgbOff(1,10);
  delay(1000);
  dmx512.rgbRainbow(1,50);
  delay(1000);
  dmx512.rgbRespire(1,10,dmx512.eRed,255,100);
  delay(1000);
  dmx512.rgbJump(1,10,50);
  delay(1000);
  dmx512.rgbGradual(1,10,100);
  delay(1000);
  dmx512.rgbSpectrum(1,10,100);
  delay(1000);
}
  
