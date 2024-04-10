#include <SPI.h>

#include <CRC8.h>
#include "CRC.h"
#include "helper.h"


// 初始化 CRC-8 计算器
// CRC8 crc;

static constexpr size_t BUFFER_SIZE = 8;
uint8_t tx_buf[BUFFER_SIZE]{ 6, 45, 3, 5, 4, 5, 7, 34 };
uint8_t rx_buf[BUFFER_SIZE];

void setup() {
  // put your setup code here, to run once:


  Serial.begin(115200);
  // 初始化 SPI 接口
  SPI.begin();


  // 设置 SPI 时钟速度
  // SPI.setClockDivider(SPI_CLOCK_DIV4);

  // 设置 SPI 模式
  // SPI.setDataMode(SPI_MODE0);

  // SPI.beginTransaction(SPISettings(8000000,MSBFIRST,SPI_MODE0));


  SPI.setBitOrder(MSBFIRST);

  // 设置 SS 引脚为输出模式
  pinMode(SS, OUTPUT);
  pinMode(MOSI, OUTPUT);
  pinMode(MISO, INPUT);



  // 将 SS 引脚置为高电平
  digitalWrite(SS, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

  // uint8_t tx_buf[BUFFER_SIZE]{ 7, 3, 3, 4, 5, 6, 7, 8 };


  // 第一种方式计算crc8
  const char* text = "This";
  const uint8_t text_len = strlen(text);
  uint8_t text_crc8 = calcCRC8((uint8_t*)text, strlen(text));

  for (int i = 0; i < text_len; i++) {
    // SPI.transfer(text[i]);
  }

  // Serial.println(text_crc8);

  // char ch = 97 + count++ % 26;
  // Serial.println(ch);

  // memset(txbuf, ch, 56);
  // tsbuf[56] = '~';
  // memset(rxbuf, 0, 64);

  // initializeBuffers(tx_buf, rx_buf, BUFFER_SIZE);

  SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE1));

  // 选择 ESP32 从机
  digitalWrite(SS, LOW);

  for (int i = 0; i < BUFFER_SIZE; i++) {
    uint8_t ack = SPI.transfer(tx_buf[i]);
    Serial.println(ack);
  }


  // SPI.transfer(tx_buf, BUFFER_SIZE);

  // 向 ESP32 发送数据

  // SPI.transfer(text_crc8);

  // SPI.transfer(text, strlen(text));
  // SPI.transfer(text_crc8);

  // uint8_t data = 55;
  // SPI.transfer(data);
  // SPI.transfer(data);

  // uint8_t ack = SPI.transfer(0x00);
  // Serial.print("ack: ");
  // Serial.println(ack);

  // 接收应答和 CRC 校验码
  // uint8_t ack = SPI.transfer(0x00);
  // uint8_t received_crc = SPI.transfer(0x00);

  // 验证 CRC 校验码
  // crc.restart();
  // crc.add(ack, 1);
  // if (crc.calc() != received_crc) {
  //   // CRC 校验码错误
  //   // ...
  //   Serial.println(3);
  // } else {
  //   // CRC 校验码正确
  //   Serial.println(7);
  // }



  // 取消选择 ESP32 从机
  digitalWrite(SS, HIGH);
  SPI.endTransaction();


  for (int i = 0; i < 57; i++) {
  }

  delay(3000);
}
