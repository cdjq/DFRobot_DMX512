/*!
 * @file DFRobot_Peripheral.cpp
 * @brief 这是DMX512外设库的实现方法部分
 * @copyright	Copyright (c) 2021 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [TangJie](jie.tang@dfrobot.com)
 * @version V1.0
 * @date 2022-2-10
 * @url https://github.com/DFRobot/DFRobot_DMX512
 */
#include "DFRobot_Peripheral.h"

DFRobot_DAC::DFRobot_DAC(TwoWire *pWire, uint8_t address){
  _pWire = pWire;
  _address = address;
}

uint8_t DFRobot_Peripheral::begin(uint8_t addr,uint8_t reg)
{
  uint8_t data;
  DBG(addr);
  if(readReg(addr,reg,&data,1) != 0){
    DBG("i2c error!!!!");
    return 1;
  }
  return 0;
}

uint8_t DFRobot_DAC::begin(void)
{
  _pWire->begin(PERIPHERALSDAPIN,PERIPHERALSCLPIN);   
  return DFRobot_Peripheral::begin(_address,0x01);
}

void DFRobot_DAC::setDACOutRange(eOutPutRange range)
{
  if(range == eOutPutRange::eOutPutRange5V){
    calculatingData = 819;
  }else{
    calculatingData = 409;
  }
  writeReg(_address,0x01,&range,1);
}

void DFRobot_DAC::setDACOutVoltage(eChannel channel, float data)
{
  uint8_t buffer[4];
  uint8_t reg = 0,length = 0;
  uint16_t _data = ceil(data * calculatingData);
	_data = _data << 4;
  buffer[0] = _data & 0xff;
  buffer[1] = (_data >> 8) & 0xff;
	buffer[2] = buffer[0];
	buffer[3] = buffer[1];
  if(channel == eChannel::eChannel1){
    reg = 0x02;
    length = 2;
  }else if(channel == eChannel::eChannel2){
		reg = 0x04;
    length = 2;
  }else{
		reg = 0x02;
    length = 4;
  }
	writeReg(_address,reg,&buffer[0],length);
}

void DFRobot_Peripheral::writeReg(uint8_t addr,uint8_t reg, void* pBuf, size_t size)
{
  if(pBuf == NULL){
	  DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t * _pBuf = (uint8_t *)pBuf;
  _pWire->beginTransmission(addr);
  _pWire->write(&reg,1);
  for(uint16_t i = 0; i < size; i++){
    _pWire->write(_pBuf[i]);
  }
  _pWire->endTransmission();
}

uint8_t DFRobot_Peripheral::readReg(uint8_t addr, uint8_t reg, void* pBuf, size_t size)
{
  if(pBuf == NULL){
    DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t * _pBuf = (uint8_t *)pBuf;
  _pWire->beginTransmission(addr);
  _pWire->write(&reg,1);
  if(_pWire->endTransmission() != 0)
    return 1;
  delay(100);
  _pWire->requestFrom(addr, (uint8_t) size);
  for(uint16_t i = 0; i < size; i++){
    _pBuf[i] = _pWire->read();
  }
  return 0;
}

DFRobot_RTC::DFRobot_RTC(TwoWire *pWire, uint8_t address)
{
  _pWire = pWire;
  _address = address;
}

uint8_t DFRobot_RTC::begin(void)
{ 
  _pWire->begin(PERIPHERALSDAPIN,PERIPHERALSCLPIN);   
  return DFRobot_Peripheral::begin(_address, 0x09);
}

void DFRobot_RTC::startClock(void)
{
  uint8_t data = 0;
  writeReg(_address, CONTROLSTATUS1,&data,1);
}

void DFRobot_RTC::stopClock(void)
{
  uint8_t data = (1<<5);
  writeReg(_address, CONTROLSTATUS1,&data,1);
}

void DFRobot_RTC::setYear(uint8_t year)
{
  uint8_t data = ((getSecondNumber(year)<<4)| getFirstNumber(year));
  writeReg(_address, YEARS,&data,1);
}

void DFRobot_RTC::setMonth(eMonth month)
{
  uint8_t data = ((getSecondNumber(month)<<4)| getFirstNumber(month));
  writeReg(_address, CENTURYMONTHS,&data,1);
}

void DFRobot_RTC::setDay(uint8_t day)
{
  uint8_t data = ((getSecondNumber(day)<<4)| getFirstNumber(day));
  writeReg(_address, DAYS,&data,1);
}

void DFRobot_RTC::setWeekDay(eWeekDay weekDay)
{
  uint8_t data = ((getSecondNumber(weekDay)<<4)| getFirstNumber(weekDay));
  writeReg(_address, WEEKDAYS,&data,1);
}

void DFRobot_RTC::setHour(uint8_t hour)
{
  uint8_t data = ((getSecondNumber(hour)<<4)| getFirstNumber(hour));
  writeReg(_address, HOURS,&data,1);
}

void DFRobot_RTC::setMinut(uint8_t minut)
{
  uint8_t data = ((getSecondNumber(minut)<<4)| getFirstNumber(minut));
  writeReg(_address, MINUTES,&data,1);
}

void DFRobot_RTC::setSecond(uint8_t second)
{
  uint8_t data = ((getSecondNumber(second)<<4)| getFirstNumber(second));
  writeReg(_address, VLSECONDS,&data,1);
}

sTime_t DFRobot_RTC::getTime(void)
{
  sTime_t output;
  uint8_t year,month,day,weekday,hour,minute,seconds; 
  readReg(_address, YEARS,&year,1);
  readReg(_address, CENTURYMONTHS,&month,1);
  readReg(_address, DAYS,&day,1);
  readReg(_address, WEEKDAYS,&weekday,1);
  readReg(_address, HOURS,&hour,1);
  readReg(_address, MINUTES,&minute,1);
  readReg(_address, VLSECONDS,&seconds,1);
  output.year    = bcdToNumber((year&0b11110000)>>4,year&0b00001111);
  output.month   = bcdToNumber((month&0b00010000)>>4,month&0b00001111);
  output.day     = bcdToNumber((day&0b00110000)>>4,day&0b00001111);
  output.weekday = bcdToNumber(0,weekday&0b00000111);
  output.hour    = bcdToNumber((hour&0b00110000)>>4,hour&0b00001111);
  output.minute  = bcdToNumber((minute&0b01110000)>>4,minute&0b00001111);
  output.second  = bcdToNumber((seconds&0b01110000)>>4,seconds&0b00001111);
  return output;
}

uint8_t DFRobot_RTC::getSecondNumber(uint8_t number)
{
  uint8_t output = number/10;
  return output;
}

uint8_t DFRobot_RTC::getFirstNumber(uint8_t number)
{
  uint8_t output = number % 10;
  return output;
}

uint8_t DFRobot_RTC::bcdToNumber(uint8_t first, uint8_t second)
{
  uint8_t output;
  output = first * 10;
  output = output + second;
  return output;
}

DFRobot_ADC::DFRobot_ADC(TwoWire *pWire, uint8_t address)
{
  _pWire = pWire;
  _address = address;
}

uint8_t DFRobot_ADC::begin(void)
{
  _pWire->begin(PERIPHERALSDAPIN,PERIPHERALSCLPIN);   
  return DFRobot_Peripheral::begin(_address, 0x08);
}
uint16_t DFRobot_ADC::getADCData(eChannel channel)
{
  uint16_t data = 0;
  uint8_t buf[2];
  if(channel == eChannel::eChannel1){
    readReg(_address, 0x08, buf, 2);
    data = buf[0] << 8 | buf[1];
  }else if(channel = eChannel::eChannel2){
    readReg(_address, 0x0a, buf, 2);
    data = buf[0] << 8 | buf[1];
  }
  return data;
}

