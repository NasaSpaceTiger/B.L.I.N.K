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
  Serial.println("Empfänger gestartet.");
}

void ReceiverClass::sync() {
  Serial.println("Starte Synchronisation...");

  bool seenOn = false;

  while (!synchronizedOnce) {

    if (digitalRead(BUTTON_PIN) == LOW) {
      threshold = analogRead(LDR_PIN) - THRESHOLD_OFFSET;
      Serial.print("Neuer Threshold: ");
      Serial.println(threshold);
    }

    bool on = ledIsOn();

    if (!seenOn) {
      if (on) {
        seenOn = true;
        Serial.println("LED wurde AN erkannt. Warte auf AUS...");
      }
      continue;
    }

    if (!on) {
      Serial.println("LED ist AUS. Prüfe ob sie 1 Sekunde AUS bleibt...");

      unsigned long start = millis();

      while (!ledIsOn()) {
        if (millis() - start >= 998) {

          nextSample = millis() + (STEP_TIME / 2);

          Serial.println("Synchronisiert!");
          synchronizedOnce = true;
          break;
        }
      }

      if (!synchronizedOnce) {
        Serial.println("LED wurde wieder AN → Neustart...");
        seenOn = false;
      }
    }
  }
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
