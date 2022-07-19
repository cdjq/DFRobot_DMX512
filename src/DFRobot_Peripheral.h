/*!
 * @file DFRobot_Peripheral.h
 * @brief 这是DMX512开发板外设库的方法
 * @copyright	Copyright (c) 2021 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [TangJie](jie.tang@dfrobot.com)
 * @version V1.0
 * @date 2022-2-10
 * @url https://github.com/DFRobot/DFRobot_DMX512
 */
#ifndef _DFROBOT_PERIPHERAL_H_
#define _DFROBOT_PERIPHERAL_H_

#include "Arduino.h"
#include "Wire.h"
#include "math.h"

#define ENABLE_DBG //!< 打开这个宏, 可以看到程序的详细运行过程
#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif

#define PERIPHERALSCLPIN 19
#define PERIPHERALSDAPIN 18

class DFRobot_Peripheral
{
public:
  /**
   * @fn begin
   * @brief 初始化外设传感器
	 * @param reg 读取的寄存器
   * @return 返回初始化状态
   */
  uint8_t begin(uint8_t addr, uint8_t reg);

  /**
   * @fn writeReg
   * @brief 写寄存器函数，设计为虚函数，由派生类实现函数体
   * @param reg  寄存器地址 8bits
   * @param pBuf 要写入数据的存放缓存
   * @param size 要写入数据的长度
   * @return None
   */
  void writeReg(uint8_t addr,uint8_t reg, void* pBuf, size_t size);

  /**
   * @fn readReg
   * @brief 读取寄存器函数，设计为虚函数，由派生类实现函数体
   * @param reg  寄存器地址 8bits
   * @param pBuf 要写入数据的存放缓存
   * @param size 要写入数据的长度
   * @return uint8_t类型,表示读寄存器状态返回
   * @retval 0 读取成功
   * @retval 1 读取失败
   */
  uint8_t readReg(uint8_t addr, uint8_t reg, void* pBuf, size_t size);

  TwoWire *_pWire;
  
};

class DFRobot_DAC:public DFRobot_Peripheral
{
public:	
	/**
	 * @fn eOutPutRange
	 * @brief 模拟电压输出的范围选择
	 */
	typedef enum{
    eOutPutRange5V = 0X00,
    eOutPutRange10V = 0X11,
  }eOutPutRange;
	/**
	 * @fn eChannel
	 * @brief 输出通道选择
	 */
	typedef enum{
    eChannel1 = 1,
    eChannel2,
		eChannelAll,
  }eChannel;

  DFRobot_DAC(TwoWire *pWire = &Wire1,uint8_t adaddressdr = 0X58);
	/**
   * @fn begin
   * @brief 初始化外设传感器
   * @return 返回初始化状态
   */
  uint8_t begin(void);

	/**
   * @fn setDACOutRange
   * @brief 设置DAC输出范围
   * @param range DAC输出范围
   * @return NONE
   */
  void setDACOutRange(eOutPutRange range);
    
  /**
   * @fn setDACOutVoltage
   * @brief 设置不同通道输出DAC值
   * @param channel 通道设置
   * @param data 需要输出的电压值
   * @return NONE
   */
  void setDACOutVoltage(eChannel channel, float data);

private:
	uint16_t calculatingData;
  uint8_t _address;
};
/**
   * @fn sTime_t
   * @brief 时间数据结构体
   */
typedef struct{
  uint8_t year;
  uint8_t month;
  uint8_t day;
  uint8_t weekday;
  uint8_t hour;
  uint8_t minute;
  uint8_t second; 
  }sTime_t;

class DFRobot_RTC:public DFRobot_Peripheral
{
  #define CONTROLSTATUS1    0X00
  #define CONTROLSTATUS2    0X01
  #define VLSECONDS         0X02
  #define MINUTES           0X03
  #define HOURS             0X04
  #define DAYS              0X05
  #define WEEKDAYS          0X06
  #define CENTURYMONTHS     0X07
  #define YEARS             0X08
  #define MINUTEALARM       0X09
  #define HOURALARM         0X0A
  #define DAYALARM          0X0B
  #define WEEKDAYALARM      0x0C

public:

  /**
   * @fn eWeekDays
   * @brief 星期选择
   */
  typedef enum{
    eSunDay = 0,
    eMonDay,
    eTuesDay,
    eWednesDay,
    eThursDay,
    eFriDay,
    eSaturDay,
  }eWeekDay;

  /**
   * @fn eMonth
   * @brief 月份选择 
   */
  typedef enum{
    eJanuary = 1,
    eFebruary,
    eMarch,
    eApril,
    eMay,
    eJune,
    eJuly,
    eAugust,
    eSeptember,
    eOctober,
    eNovember,
    eDecember,
  }eMonth;



  DFRobot_RTC(TwoWire *pWire = &Wire1,uint8_t adaddressdr = 0X51);
  /**
   * @fn begin
   * @brief 初始化外设传感器
   * @return 返回初始化状态
   */
  uint8_t begin(void);

  /**
   * @fn startClock
   * @brief 开始计时
   * @return NONE
   */
  void startClock(void);

  /**
   * @fn stopClock
   * @brief 停止计时
   * @return NONE
   */
  void stopClock(void);

  /**
   * @fn setYear
   * @brief 设置年
   * @param year 设置年份，范围0到99
   * @return NONE
   */
  void setYear(uint8_t year);

  /**
   * @fn setMonth
   * @brief 设置月
   * @param month 设置月份
   * @return NONE
   */
  void setMonth(eMonth month);

  /**
   * @fn setDay
   * @brief 设置天数
   * @param day 设置天数，范围1到31
   * @return NONE
   */
  void setDay(uint8_t day);

  /**
   * @fn setWeekday
   * @brief 设置星期
   * @param weekday 选择星期几
   * @return NONE
   */
  void setWeekDay(eWeekDay weekDay);

  /**
   * @fn setHour
   * @brief 设置小时值
   * @param hour 设置小时，范围0到23
   * @return NONE
   */
  void setHour(uint8_t hour);

  /**
   * @fn setMinut
   * @brief 设置分钟值
   * @param minut 设置分钟值，范围0到59
   * @return NONE
   */
  void setMinut(uint8_t minut);

  /**
   * @fn setSecond
   * @brief 设置秒钟值
   * @param second 设置秒钟值，范围0到59
   * @return NONE
   */
  void setSecond(uint8_t second);

  /**
   * @fn getTime
   * @brief 获取RTC中的时间
   * @return 返回时间结构体
   */
  sTime_t getTime(void);

private:
  uint8_t getSecondNumber(uint8_t number);
  uint8_t getFirstNumber(uint8_t number);
  uint8_t bcdToNumber(uint8_t first, uint8_t second);
  uint8_t _address;
};
#endif