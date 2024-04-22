#include <ESP32SPISlave.h>
#include <SPI.h>
#include "helper.h"

ESP32SPISlave slave;

static constexpr size_t BUFFER_SIZE = 8;
static constexpr size_t QUEUE_SIZE = 1;

uint8_t rx_buf[BUFFER_SIZE]{ 1, 2,3,4,5,6,7,8 };
uint8_t tx_buf[BUFFER_SIZE]{ 1, 2,3,4,5,6,7,8 };


void setup() {

  Serial.begin(115200);
  Serial.print(1);
  SPI.setFrequency(4000000);

  slave.setDataMode(SPI_MODE1);  // default: SPI_MODE0 怎么换成SPI_MODE1数据就不丢失了？？？

  slave.setQueueSize(QUEUE_SIZE);  // default: 1

  // begin() after setting
  slave.begin(VSPI);  // default: HSPI (please refer README for pin assignments)
  pinMode(SS, INPUT);
  pinMode(MISO, OUTPUT);
  pinMode(MOSI, INPUT);
}

void loop() {

  // 以下生意0.6.0的代码
  const size_t received_bytes = slave.transfer(tx_buf, rx_buf, BUFFER_SIZE);
  Serial.print("received_bytes: ");
  Serial.println((int)received_bytes);

  for (int i = 0; i < (int)received_bytes; i++) {
    Serial.print(rx_buf[i]);
    Serial.print(" ");
  }
  Serial.println();

  // for (int i = 0; i < BUFFER_SIZE; i++) {
  //   Serial.print(tx_buf[i]);
  //   Serial.print(" ");
  // }
  // Serial.println();

  // 以下是0.2.0的代码
  // while (!slave.wait(rx_buf, tx_buf, BUFFER_SIZE))
  //   ;
  // char ch = NULL;

  // while (slave.available()) {

  //   int len = slave.size();

  //   Serial.print(len);

  //   for (int i = 0; i < len; i++) {

  //     ch = rx_buf[i];
  //     Serial.print('~');
  //     Serial.print(rx_buf[i]);

  //     // tx_buf[i] = 123;
  //   }

  //   Serial.println();
  //   slave.pop();
  // }
}