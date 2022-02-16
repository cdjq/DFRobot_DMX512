# DFRobot_DMX512
- [English Version](./README_CN.md)

这是一款集成多种功能的开发板，其中板载集成DMX512、RTC、ADC、DAC、串口、i2c、RS485等丰富接口，
使用方便，功能强大。


![产品效果图片](./resources/images/DFR0944.png)


## 产品链接（https://www.dfrobot.com.cn/）

    SKU：DFR0944

## 目录

  * [概述](#概述)
  * [库安装](#库安装)
  * [方法](#方法)
  * [兼容性](#兼容性)
  * [历史](#历史)
  * [创作者](#创作者)

## 概述

* edg101WE 集成多种丰富接口
* 使用方便功能强大

## 库安装

使用此库前，请首先下载库文件，将其粘贴到\Arduino\libraries目录中，然后打开examples文件夹并在该文件夹中运行演示。

## 方法 DFRobot_DMX512

```C++
  /**
   * @fn begin
   * @brief 初始化函数
   * @return 返回初始化状态
   * @return NONE
   */
  void begin(void)

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
  uint8_t ledON(uint16_t addr, uint8_t luminance, uint16_t chanelNum)

  /**
   * @fn ledON
   * @brief 关闭对应通道的led灯,起始通道地址加长度小于513
   * @param addr 起起始通道地址，范围1~512
   * @param chanelNum  通道数，范围1~512
   * @return 返回配置状态信息
   * @retval DMX512_OK 数据长度正常
   * @retval DMX512_LENGTH_ERROR 超出数据长度
   */
  uint8_t ledOFF(uint16_t addr, uint16_t chanelNum)

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
  uint8_t ledWate(uint16_t addr, uint16_t chanelNum, uint8_t luminance, uint8_t speed)

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
  uint8_t ledRespire(uint16_t addr, uint16_t chanelNum, uint8_t speed)

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
  uint8_t ledSpectrum(uint16_t addr, uint16_t chanelNum, uint8_t luminance, uint8_t mode)
    
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
  uint8_t ledTwinkle(uint16_t addr, uint16_t chanelNum, uint8_t luminance, uint8_t speed)

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
  uint8_t rgbColor(uint16_t addr, uint8_t lightswithNumber,uint8_t red, uint8_t green, uint8_t blue)

  /**
   * @fn rgbOff
   * @brief RGB灯带熄灭控制
   * @param start 开始的RGB灯带条数
   * @param stop  结束的RGB灯带条数
   * @return 返回配置状态信息
   * @retval DMX512_OK 数据长度正常
   * @retval DMX512_LENGTH_ERROR 超出数据长度
   */
  uint8_t rgbOff(uint8_t start, uint8_t stop)

  /**
   * @fn rgbRainbow
   * @brief RGB显示彩虹颜色
   * @param addr RGB灯起始地址，范围1~508
   * @param lightswithNumber 灯带数量，范围1~170
   * @return 返回配置状态信息
   * @retval DMX512_OK 数据长度正常
   * @retval DMX512_LENGTH_ERROR 超出数据长度
   */
  uint8_t rgbRainbow(uint16_t addr, uint8_t lightswithNumber)
  
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
  uint8_t rgbRespire(uint16_t addr, uint8_t lightswithNumber,eColour colour, uint8_t light,uint8_t speed)

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
  uint8_t rgbJump(uint16_t addr, uint8_t lightswithNumber,uint8_t speed)

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
  uint8_t rgbGradual(uint16_t addr, uint8_t lightswithNumber,uint8_t speed)

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
  uint8_t rgbSpectrum(uint16_t addr, uint8_t lightswithNumber, uint8_t mode)
```

## 方法 DFRobot_DAC

```C++
  /**
   * @fn begin
   * @brief 初始化外设传感器
   * @return 返回初始化状态
   */
  uint8_t begin(void)

	/**
   * @fn setDACOutRange
   * @brief 设置DAC输出范围
   * @param range DAC输出范围
   * @return NONE
   */
  void setDACOutRange(eOutPutRange range)
    
  /**
   * @fn setDACOutVoltage
   * @brief 设置不同通道输出DAC值
   * @param channel 通道设置
   * @param data 需要输出的电压值
   * @return NONE
   */
  void setDACOutVoltage(eChannel channel, float data)
```
## 方法 DFRobot_RTC

```C++
  /**
   * @fn begin
   * @brief 初始化外设传感器
   * @return 返回初始化状态
   */
  uint8_t begin(void)

  /**
   * @fn startClock
   * @brief 开始计时
   * @return NONE
   */
  void startClock(void)

  /**
   * @fn stopClock
   * @brief 停止计时
   * @return NONE
   */
  void stopClock(void)

  /**
   * @fn setYear
   * @brief 设置年
   * @param year 设置年份，范围0到99
   * @return NONE
   */
  void setYear(uint8_t year)

  /**
   * @fn setMonth
   * @brief 设置月
   * @param month 设置月份
   * @return NONE
   */
  void setMonth(eMonth month)

  /**
   * @fn setDay
   * @brief 设置天数
   * @param day 设置天数，范围1到31
   * @return NONE
   */
  void setDay(uint8_t day)

  /**
   * @fn setWeekday
   * @brief 设置星期
   * @param weekday 选择星期几
   * @return NONE
   */
  void setWeekDay(eWeekDay weekDay)

  /**
   * @fn setHour
   * @brief 设置小时值
   * @param hour 设置小时，范围0到23
   * @return NONE
   */
  void setHour(uint8_t hour)

  /**
   * @fn setMinut
   * @brief 设置分钟值
   * @param minut 设置分钟值，范围0到59
   * @return NONE
   */
  void setMinut(uint8_t minut)

  /**
   * @fn setSecond
   * @brief 设置秒钟值
   * @param second 设置秒钟值，范围0到59
   * @return NONE
   */
  void setSecond(uint8_t second)

  /**
   * @fn getTime
   * @brief 获取RTC中的时间
   * @return 返回时间结构体
   */
  sTime_t getTime(void)
```

## 方法 DFRobot_ADC

```C++
  /**
   * @fn begin
   * @brief 初始化外设传感器
   * @return 返回初始化状态
   */
  uint8_t begin(void)
  /**
   *@fn  getADCData
   * @brief 获取ADC数据
   * @param channel ADC通道选择
   * @return 返回ADC采集的原始数据
   */
  uint16_t getADCData(eChannel channel) 
  ```


## 兼容性

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | :----:
   edg101we        |      √       |              |             |



## 历史

- 2022/02/16 - 1.0.0 版本

## 创作者

Written by TangJie(jie.tang@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))





