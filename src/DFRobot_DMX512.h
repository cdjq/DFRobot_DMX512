/*!
 * @file  DFRobot_DMX512.h
 * @brief 这是一个通过DMX512控制灯的库
 * @copyright	Copyright (c) 2021 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license   The MIT License (MIT)
 * @author    [TangJie](jie.tang@dfrobot.com)
 * @version   V1.0
 * @date      2022-01-24
 * @url       https://github.com/DFRobot/DFRobot_DMX512
 */
#ifndef DFROBOT_DMX512_H
#define DFROBOT_DMX512_H

#include "Arduino.h"
#include "String.h"
#include "driver/uart.h"
#include "esp32-hal-uart.h"
#include "math.h"


#if 1
#define DBG(...) {Serial.print("["); Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif

#define DMX512_RX  7
#define DMX512_TX  5
#define DMX512_DE  6
#define DMX512_UART  1

#define DMX512_LENGTH_ERROR 1
#define DMX512_OK         0


class DFRobot_DMX512
{
public:
  /**
   * @fn eColour
   * @brief 颜色选择
   */
  typedef enum{
    eRed = 0,
    eGreen,
    eBlue,
  }eColour;

  /**
   * @fn DFRobot_DMX512
   * @brief 构造函数接口
   */
  DFRobot_DMX512(void){};

  /**
   * @fn begin
   * @brief 初始化函数
   * @return 返回初始化状态
   * @return NONE
   */
  void begin(void);

  /**
   * @fn ledON
   * @brief 打开对应通道的led灯,起始通道地址加长度小于513
   * @param addr 起始通道地址，范围1~512
   * @param luminance 亮度等级，范围0~255
   * @param chanelNum  通道数，范围1~512
   * @return 返回配置状态信息
   * @retval DMX512_OK 数据长度正常
   * @retval DMX512_LENGTH_ERROR 超出数据长度
   */
  uint8_t ledON(uint16_t addr, uint8_t luminance, uint16_t chanelNum);

  /**
   * @fn ledON
   * @brief 关闭对应通道的led灯,起始通道地址加长度小于513
   * @param addr 起起始通道地址，范围1~512
   * @param chanelNum  通道数，范围1~512
   * @return 返回配置状态信息
   * @retval DMX512_OK 数据长度正常
   * @retval DMX512_LENGTH_ERROR 超出数据长度
   */
  uint8_t ledOFF(uint16_t addr, uint16_t chanelNum);

  /**
   * @fn ledWate
   * @brief led流水灯,起始通道地址加长度小于513
   * @param addr 起始通道地址，范围1~512    
   * @param chanelNum 通达数量范围1~512
   * @param luminance 亮度等级，范围0~255
   * @param speed  流水灯速度，范围0~100
   * @return 返回配置状态信息
   * @retval DMX512_OK 数据长度正常
   * @retval DMX512_LENGTH_ERROR 超出数据长度
   */
  uint8_t ledWate(uint16_t addr, uint16_t chanelNum, uint8_t luminance, uint8_t speed);

  /**
   * @fn ledRespire
   * @brief led呼吸灯,起始通道地址加长度小于513
   * @param addr 起始通道地址，范围1~512
   * @param chanelNum 通达数量范围1~512
   * @param speed  流水灯速度，范围0~100
   * @return 返回配置状态信息
   * @retval DMX512_OK 数据长度正常
   * @retval DMX512_LENGTH_ERROR 超出数据长度
   */
  uint8_t ledRespire(uint16_t addr, uint16_t chanelNum, uint8_t speed);

  /**
   * @fn ledSpectrum
   * @brief led频谱,起始通道地址加长度小于513
   * @param addr 起始通道地址，范围1~512
   * @param chanelNum 通达数量范围1~512
   * @param luminance 亮度等级，范围0~255
   * @param mode  切换频谱模式
   * @return 返回配置状态信息
   * @retval DMX512_OK 数据长度正常
   * @retval DMX512_LENGTH_ERROR 超出数据长度
   */
  uint8_t ledSpectrum(uint16_t addr, uint16_t chanelNum, uint8_t luminance, uint8_t mode);
    
  /**
   * @fn ledTwinkle
   * @brief led频闪,起始通道地址加长度小于513
   * @param addr 起始通道地址，范围1~512
   * @param chanelNum 通达数量范围1~512
   * @param luminance 亮度等级，范围0~255
   * @param speed  流水灯速度，范围0~100
   * @return 返回配置状态信息
   * @retval DMX512_OK 数据长度正常
   * @retval DMX512_LENGTH_ERROR 超出数据长度
   */
  uint8_t ledTwinkle(uint16_t addr, uint16_t chanelNum, uint8_t luminance, uint8_t speed);

  /**
   * @fn rgbColor
   * @brief RGB灯光颜色控制
   * @param addr 起始通道地址，范围1~511
   * @param lightswithNumber 灯带数量，范围1~170
   * @param red 红色灯亮度等级，范围0~255
   * @param green 绿色灯亮度等级，范围0~255
   * @param blue  蓝色灯亮度等级，范围0~255
   * @return 返回配置状态信息
   * @retval DMX512_OK 数据长度正常
   * @retval DMX512_LENGTH_ERROR 超出数据长度
   */
  uint8_t rgbColor(uint16_t addr, uint8_t lightswithNumber,uint8_t red, uint8_t green, uint8_t blue);

  /**
   * @fn rgbOff
   * @brief RGB灯带熄灭控制
   * @param start 开始的RGB灯带条数
   * @param stop  结束的RGB灯带条数
   * @return 返回配置状态信息
   * @retval DMX512_OK 数据长度正常
   * @retval DMX512_LENGTH_ERROR 超出数据长度
   */
  uint8_t rgbOff(uint8_t start, uint8_t stop);

  /**
   * @fn rgbRainbow
   * @brief RGB显示彩虹颜色
   * @param addr RGB灯起始地址，范围1~508
   * @param lightswithNumber 灯带数量，范围1~170
   * @return 返回配置状态信息
   * @retval DMX512_OK 数据长度正常
   * @retval DMX512_LENGTH_ERROR 超出数据长度
   */
  uint8_t rgbRainbow(uint16_t addr, uint8_t lightswithNumber);
  
	/**
   * @fn rgbRespire
   * @brief RGB七彩呼吸灯
   * @param addr RGB灯起始地址，范围1~511
   * @param lightswithNumber 灯带数量，范围1~170
   * @param colour 呼吸颜色选择
   * @param light 亮度选择
   * @param speed 呼吸速度，范围0~100
   * @return 返回配置状态信息
   * @retval DMX512_OK 数据长度正常
   * @retval DMX512_LENGTH_ERROR 超出数据长度 
   */
  uint8_t rgbRespire(uint16_t addr, uint8_t lightswithNumber,eColour colour, uint8_t light,uint8_t speed);

  /**
   * @fn rgbJump
   * @brief RGB七彩跳变
   * @param addr RGB灯起始地址，范围1~511
   * @param lightswithNumber 灯带数量，范围1~170
   * @param speed 跳变速度，范围0~100
   * @return 返回配置状态信息
   * @retval DMX512_OK 数据长度正常
   * @retval DMX512_LENGTH_ERROR 超出数据长度
   */
  uint8_t rgbJump(uint16_t addr, uint8_t lightswithNumber,uint8_t speed);

  /**
   * @fn rgbGradual
   * @brief RGB七彩渐变
   * @param addr RGB灯起始地址，范围1~511
   * @param lightswithNumber 灯带数量，范围1~170
   * @param speed 渐变速度，范围0~100
   * @return 返回配置状态信息
   * @retval DMX512_OK 数据长度正常
   * @retval DMX512_LENGTH_ERROR 超出数据长度
   */
  uint8_t rgbGradual(uint16_t addr, uint8_t lightswithNumber,uint8_t speed);

  /**
   * @fn rgbSpectrum
   * @brief RGB七彩频谱
   * @param addr RGB灯起始地址，范围1~511
   * @param lightswithNumber 灯带数量，范围1~170
   * @param mode 频谱模式
   * @return 返回配置状态信息
   * @retval DMX512_OK 数据长度正常
   * @retval DMX512_LENGTH_ERROR 超出数据长度 
   */
  uint8_t rgbSpectrum(uint16_t addr, uint8_t lightswithNumber, uint8_t mode);

private:
  void writeData(uint16_t addr, uint8_t luminance, size_t len);
  void writeBuf(uint16_t addr, void *buf, size_t len);
  uint8_t _dataBuf[513];


};
#endif
