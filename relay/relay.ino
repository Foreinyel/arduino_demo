const int PinRelay = 3;
const int PinButton = 5;

int relayStatus = LOW;

void setRelayStatus() {
  if (relayStatus == HIGH) {
    relayStatus = LOW;
  } else {
    relayStatus = HIGH;
  }
  digitalWrite(PinRelay, relayStatus);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(PinRelay, OUTPUT);
  pinMode(PinButton, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  int btnVal = digitalRead(PinButton);
  if (btnVal == 0) {
    setRelayStatus();
    delay(1000);
  }

}
