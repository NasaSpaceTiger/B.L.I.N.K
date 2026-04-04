#include "sender.h"

SenderClass Sender;

void SenderClass::init() {
  pinMode(LED_PIN, OUTPUT);
}

void SenderClass::Sync() {
  digitalWrite(LED_PIN, HIGH);
  delay(SYNC_ON_TIME);
  digitalWrite(LED_PIN, LOW);
  delay(SYNC_OFF_TIME);
}


void SenderClass::waitNextBit(unsigned long &t) {
  t += STEP_TIME * 1000;
  while (micros() < t);
}

void SenderClass::sendLetter(char c) {
  byte ascii = c;
  unsigned long t = micros();

  for (int i = 6; i >= 0; i--) {
    bool bit = (ascii >> i) & 1;
    digitalWrite(LED_PIN, bit ? HIGH : LOW);
    waitNextBit(t);
  }
}

void SenderClass::send(String txt) {
  for (int i = 0; i < txt.length(); i++) {
    sendLetter(txt[i]);
  }

  while (true) {
    digitalWrite(LED_PIN, HIGH);
  }
}

