#include "receiver.h"

ReceiverClass Receiver;

bool ReceiverClass::ledIsOn() {
  return analogRead(LDR_PIN) > threshold;
}

bool ReceiverClass::readBit() {
  while (millis() < nextSample);
  bool on = ledIsOn();
  nextSample += STEP_TIME;
  return on;
}

char ReceiverClass::readAsciiChar() {
  byte value = 0;

  for (int i = 0; i < 7; i++) {
    bool bit = readBit();
    value = (value << 1) | (bit ? 1 : 0);
  }

  return (char)value;
}

void ReceiverClass::init() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(9600);
}

void ReceiverClass::calibrateThreshold() {
  threshold = analogRead(LDR_PIN) - THRESHOLD_OFFSET;
  Serial.print("Threshold gesetzt auf: ");
  Serial.println(threshold);
  delay(500);
}

void ReceiverClass::sync() {

  // Warten auf StartSignal (LED AN)
  while (!ledIsOn());

  // Jetzt beginnt gleich Bit 0
  nextSample = millis() + (STEP_TIME / 2);
}

String ReceiverClass::read() {

  char letter = readAsciiChar();
  receivedText += letter;

  if (ledIsOn()) {
    if (endCheckStart == 0) endCheckStart = millis();

    if (millis() - endCheckStart > END_TIME) {
      return receivedText;
    }
  } else {
    endCheckStart = 0;
  }

  return "";
}

void ReceiverClass::showText(String txt) {
  Serial.println(txt);
}
