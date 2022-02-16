#include "DFRobot_DMX512.h"

void DFRobot_DMX512::begin(void)
{   
  pinMode(DMX512_DE, OUTPUT);
  digitalWrite(DMX512_DE, HIGH);
  if (uart_is_driver_installed(DMX512_UART)) {
    uart_driver_delete(DMX512_UART);
  }
  uart_config_t uart_config = {
    .baud_rate = 250000,
    .data_bits = UART_DATA_8_BITS,
    .parity    = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_2,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    .source_clk = UART_SCLK_APB,
  };
  ESP_ERROR_CHECK(uart_driver_install(DMX512_UART, 1024, 0, 0, NULL, 0));
  ESP_ERROR_CHECK(uart_param_config(DMX512_UART, &uart_config));
  ESP_ERROR_CHECK(uart_set_pin(DMX512_UART, DMX512_TX, DMX512_RX, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
  uart_wait_tx_done(DMX512_UART, 1000);
}

uint8_t DFRobot_DMX512::ledON(uint16_t addr, uint8_t luminance, uint16_t chanelNum)
{
  if((addr + chanelNum)>513){
    return DMX512_LENGTH_ERROR;
  }
  writeData(addr,luminance,chanelNum);
  return DMX512_OK;
}

uint8_t DFRobot_DMX512::ledOFF(uint16_t addr, uint16_t chanelNum)
{
  if((addr + chanelNum)>513){
    return DMX512_LENGTH_ERROR;
  }
  writeData(addr,0,chanelNum);
  return DMX512_OK;
}

uint8_t DFRobot_DMX512::ledWate(uint16_t addr, uint16_t chanelNum, uint8_t luminance, uint8_t speed)
{
  uint16_t time = 25500;
  uint16_t i = 0;
  if((addr + chanelNum)>513){
    return DMX512_LENGTH_ERROR;
  }
  for(;i < chanelNum; ++i){
    writeData(((addr+i))-1,0,1);
    delay(5);
    writeData((addr+i),luminance,1);
    delay(time/speed);
  }
  writeData(((addr+i)-1),0,1);
  return DMX512_OK;
}

uint8_t DFRobot_DMX512::ledSpectrum(uint16_t addr, uint16_t chanelNum, uint8_t luminance, uint8_t mode)
{
  uint16_t i = 0;
  if((addr + chanelNum)>513){
    return DMX512_LENGTH_ERROR;
  }
  for(;i < chanelNum; ++i){
    writeData(addr+i,luminance,1);
    delay(200);
  }
  for(i=chanelNum;i > 0; i--){
    writeData(((addr+i)-1),0,1);
    delay(200);
  }
  return DMX512_OK;
}

uint8_t DFRobot_DMX512::ledTwinkle(uint16_t addr, uint16_t chanelNum, uint8_t luminance, uint8_t speed)
{
  uint16_t time = 12750 / speed;
  uint8_t i = 0;
  if((addr + chanelNum)>513){
    return DMX512_LENGTH_ERROR;
  }
  for(uint8_t i = 0; i < 10;i++){
    writeData(addr,luminance,chanelNum);
    delay(time);
    writeData(addr,0,chanelNum);
    delay(time);
  }
  return DMX512_OK;
}

uint8_t DFRobot_DMX512::ledRespire(uint16_t addr, uint16_t chanelNum, uint8_t speed)
{
  uint16_t time = 12750 / speed;
  uint8_t i = 0;
  if((addr + chanelNum)>513){
    return DMX512_LENGTH_ERROR;
  }
  for(;i < 80; ++i){
    writeData(addr,i,chanelNum);
    delay(time);
  }
  for(i=80;i > 0; i--){
    writeData(addr,i,chanelNum);
    delay(time);
  }
  writeData(addr,0,chanelNum);
  return DMX512_OK;
}

uint8_t DFRobot_DMX512::rgbColor(uint16_t addr, uint8_t lightswithNumber,uint8_t red, uint8_t green, uint8_t blue)
{
  uint16_t dataLength = lightswithNumber * 3;
  uint8_t buffer[dataLength];
  uint8_t state =0;
  if((addr + (lightswithNumber*3))>513){
    return DMX512_LENGTH_ERROR;
  }
  for(uint8_t i = 0;i < lightswithNumber;i++){
    buffer[i+0+state] = red;
    buffer[i+1+state] = green;
    buffer[i+2+state] = blue;
    state += 2;
  }
  writeBuf(addr, &buffer, dataLength);
  return DMX512_OK;
}

uint8_t DFRobot_DMX512::rgbOff(uint8_t start, uint8_t stop)
{
  uint16_t addr;
  uint8_t dataLen;
  if(stop >= 170 && start >= 170){
    return DMX512_LENGTH_ERROR;
  }
  addr = start +(2*(start-1));
  dataLen = (stop-start + 1) * 3;
  writeData(addr,0,dataLen);
  return DMX512_OK;
}

uint8_t DFRobot_DMX512::rgbRainbow(uint16_t addr, uint8_t lightswithNumber)
{
  uint16_t dataLength = lightswithNumber * 3;
  uint8_t buffer[dataLength];
  uint8_t state =0;
  if((addr + (lightswithNumber*3))>513){
    return DMX512_LENGTH_ERROR;
  }
  for(uint8_t i = 0; i < lightswithNumber; i++){
    if(i < lightswithNumber/3){
      buffer[i+0+state] = 255;
      buffer[i+1+state] = ceil(255*3*i/lightswithNumber);
      buffer[i+2+state] = 0;
    }else if(i < lightswithNumber/2){
      buffer[i+0+state] = ceil(750-i*(250*6/lightswithNumber));
      buffer[i+1+state] = 255;
      buffer[i+2+state] = 0;
    }else if(i < lightswithNumber*2/3){
      buffer[i+0+state] = 0;
      buffer[i+1+state] = 255;
      buffer[i+2+state] = ceil(i*(250*6/lightswithNumber)-750);
    }else if(i < lightswithNumber*5/6){
      buffer[i+0+state] = 0;
      buffer[i+1+state] = ceil(1250-i*(250*6/lightswithNumber));
      buffer[i+2+state] = 255;
    }else{
      buffer[i+0+state] = ceil(150*i*(6/lightswithNumber)-750);
      buffer[i+1+state] = 0;
      buffer[i+2+state] = 255;
    }
    state += 2;
  }
  writeBuf(addr, &buffer, dataLength);
  return DMX512_OK;
}

uint8_t DFRobot_DMX512::rgbRespire(uint16_t addr, uint8_t lightswithNumber,eColour colour, uint8_t light,uint8_t speed)
{
  uint16_t dataLength = lightswithNumber * 3;
  uint8_t buffer[dataLength];
  uint8_t state =0,i = 0,k = 0,j = 0;
  uint16_t time = 1275 / speed;
  if((addr + (lightswithNumber*3))>513){
    return DMX512_LENGTH_ERROR;
  }
  for(uint8_t i = 0;i < dataLength;i++)
    buffer[i] = 0;
    for(; k < light; k++){
      for(;j < lightswithNumber;j++){
        buffer[colour+j+state] = k;
        state += 2;
      }
      j=0;
      state = 0;
      delay(time);
      writeBuf(addr, &buffer, dataLength);
    }
    for(;k > 0; --k){
      for(;j < lightswithNumber;j++){
        buffer[colour+j+state] = k-1;
        state += 2;
      }
      j=0;
      state = 0;
      delay(time);
      writeBuf(addr, &buffer, dataLength);
    }
  return DMX512_OK;
}

uint8_t DFRobot_DMX512::rgbJump(uint16_t addr, uint8_t lightswithNumber,uint8_t speed)
{
  uint16_t dataLength = lightswithNumber * 3;
  uint8_t buffer[dataLength];
  uint8_t state =0,i = 0,k = 0,j = 0;
  uint16_t time = 12750 / speed;
  if((addr + (lightswithNumber*3))>513){
    return DMX512_LENGTH_ERROR;
  }
  for(uint8_t i = 0;i < dataLength;i++)
    buffer[i] = 0;
  for(; i < 3; i++){
    for(;j < lightswithNumber;j++){
      buffer[i+j+state] = 80;
      state += 2;
    }
    j=0;
    state = 0;
    delay(time);
    writeBuf(addr, &buffer, dataLength);
    for(;j < lightswithNumber;j++){
      buffer[i+j+state] = 0;
      state += 2;
    }
    j=0;
    state = 0;
    delay(time);
    writeBuf(addr, &buffer, dataLength);
  }
  return DMX512_OK;
}

uint8_t DFRobot_DMX512::rgbGradual(uint16_t addr, uint8_t lightswithNumber,uint8_t speed)
{
  uint16_t dataLength = lightswithNumber * 3;
  uint8_t buffer[dataLength];
  uint8_t state =0,i = 0,k = 0,j = 0,f = 0;
  uint16_t time = 12750 / speed;
  if((addr + (lightswithNumber*3))>513){
    return DMX512_LENGTH_ERROR;
  }
  for(uint8_t i = 0;i < dataLength;i++)
    buffer[i] = 0;

  for(;f<80;f++){
    for(;k < 80;k++){
      for(;i < 80; i++){
        for(;j < lightswithNumber;j++){
          buffer[j+0+state] = i;
          state += 2;
        }
        state = 0;
        j = 0;
        delay(time);
        writeBuf(addr, &buffer, dataLength);
      } 
      for(;j < lightswithNumber;j++){
          buffer[j+0+state] = 79 - k;
          buffer[j+1+state] = k;
          state += 2;
        }
      state = 0;
        j = 0;
      delay(time);
      writeBuf(addr, &buffer, dataLength);
    }
    for(;j < lightswithNumber;j++){
      buffer[j+1+state] = 79 - f;
      buffer[j+2+state] = f;
      state += 2;
    }
    state = 0;
    j = 0;
    delay(time);
    writeBuf(addr, &buffer, dataLength);
  }
  state = 0;
  j = 0;
  for(;f>0;f--){
    for(;j < lightswithNumber;j++){
      buffer[j+2+state] = f-1;
      state += 2;
    }
    state = 0;
    j = 0;
    delay(time);
    writeBuf(addr, &buffer, dataLength);
  }
  return DMX512_OK;
}

uint8_t DFRobot_DMX512::rgbSpectrum(uint16_t addr, uint8_t lightswithNumber,uint8_t mode)
{
  uint16_t dataLength = lightswithNumber * 3;
  uint8_t i = 0,j = 0;
  if((addr + (lightswithNumber*3))>513){
    return DMX512_LENGTH_ERROR;
  }
  for(;j < 3; j++){
    for(;i < dataLength;){
      writeData(addr+i+j,80,1);
      delay(200);
      i+=3;
    }
    for(i=dataLength;i > 0;){
      i-=3;
      writeData(((addr+i+j)),0,1);
      delay(200);
    }
  }
  return DMX512_OK;
}

void DFRobot_DMX512::writeData(uint16_t addr, uint8_t luminance, size_t len)
{
  //DBG(addr);
  uart_wait_tx_done(DMX512_UART, 500);
  uart_set_line_inverse(DMX512_UART, 38);
  ets_delay_us(88);
  uart_set_line_inverse(DMX512_UART, 0);
  ets_delay_us(8);
  for(uint16_t i=0; i < len; i++){
    _dataBuf[addr + i] = luminance;
  }
  for(uint16_t i =0;i < 513;i++){
    uart_write_bytes(DMX512_UART, &_dataBuf[i], 1);
    ets_delay_us(10);
  }
}

void DFRobot_DMX512::writeBuf(uint16_t addr, void *buf, size_t len)
{
  //DBG(addr);
  uint8_t *_pbuf = (uint8_t*)buf;
  uart_wait_tx_done(DMX512_UART, 500);
  uart_set_line_inverse(DMX512_UART, 38);
  ets_delay_us(88);
  uart_set_line_inverse(DMX512_UART, 0);
  ets_delay_us(8);
  for(uint16_t i=0; i < len; i++){
    _dataBuf[addr + i] = _pbuf[i];
  }
  for(uint16_t i =0;i < 513;i++){
    uart_write_bytes(DMX512_UART, &_dataBuf[i], 1);
    ets_delay_us(10);
  }
}



