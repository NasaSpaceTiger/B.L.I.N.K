#include "sender.h"

SenderClass Sender;

void SenderClass::init() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTPN_PIN_START, INPUT_PULLUP);
  digitalWrite(LED_PIN, HIGH);
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

  // Startbit (immer HIGH)
  unsigned long t = micros();
  digitalWrite(LED_PIN, HIGH);
  waitNextBit(t);

  // Jetzt die echten Datenbits
  for (int i = 0; i < txt.length(); i++) {
    sendLetter(txt[i]);
  }

  digitalWrite(LED_PIN, HIGH); // Idle
}
