#include "receiver.h"

ReceiverClass Receiver;

bool ReceiverClass::ledIsOn() {
    return analogRead(LDR_PIN) > threshold;
}

void ReceiverClass::init() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    Serial.begin(9600);
}

void ReceiverClass::calibrateThreshold() {
    Serial.println("Threshold setzen: Taste drücken...");
    while (digitalRead(BUTTON_PIN) == HIGH);
    threshold = analogRead(LDR_PIN) - THRESHOLD_OFFSET;
    Serial.print("Threshold: ");
    Serial.println(threshold);
    delay(500);
}

bool ReceiverClass::detectStartSignal() {
    if (ledIsOn()) return false;

    unsigned long t = millis();
    while (!ledIsOn()) {
        if (millis() - t > 998) {
            return true; // Startsignal erkannt
        }
    }
    return false;
}

void ReceiverClass::sync() {
    nextSample = millis() + (STEP_TIME / 2);
}

String ReceiverClass::read() {
    receivedText = "";
    endCheckStart = 0;

    byte current = 0;
    int count = 0;

    while (true) {
        while (millis() < nextSample);
        nextSample += STEP_TIME;

        bool bit = ledIsOn();

        current = (current << 1) | (bit ? 1 : 0);
        count++;

        if (count == 7) {
            receivedText += (char)current;
            current = 0;
            count = 0;
        }

        if (ledIsOn()) {
            if (endCheckStart == 0) endCheckStart = millis();
            if (millis() - endCheckStart > END_TIME) {
                return receivedText;
            }
        } else {
            endCheckStart = 0;
        }
    }
}


void ReceiverClass::showText(String txt) {
    Serial.println(txt);
}
