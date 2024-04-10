// 定义引脚号
const int buttonPin = 5;
const int fanPin = 3;

void setup() {
  // put your setup code here, to run once:
// 将引脚设置为输出模式
  pinMode(buttonPin, INPUT);
  pinMode(fanPin, OUTPUT);
}

int fanStatus = LOW;

void setFanStatus() {
  if (fanStatus == HIGH) {
    fanStatus = LOW;
  } else {
    fanStatus = HIGH;
  }
  digitalWrite(fanPin, fanStatus);
}

void loop() {
  // put your main code here, to run repeatedly:

  // for (int i = 0; i <= 255; i += 5) {
  //   analogWrite(motorPin, i);
  //   delay(1000);
  // }

  // digitalWrite(motorPin, HIGH);
  // digitalWrite(motorPinFan, HIGH);
  // delay(1000);

  // digitalWrite(motorPin, LOW);
  // digitalWrite(motorPinFan, LOW);
  // delay(1000);

  int btnVal = digitalRead(buttonPin);
  if (btnVal == 0) {
    setFanStatus();
    delay(1000);
  }

}
