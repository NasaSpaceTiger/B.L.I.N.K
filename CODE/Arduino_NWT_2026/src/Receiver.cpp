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
    delay(0);
}

bool ReceiverClass::detectStartSignal() {
    // Warten bis LED AUS geht
    if (ledIsOn()) return false;

    unsigned long t = millis();
    while (!ledIsOn()) {
        if (millis() - t > 150) {
            return true; // Start erkannt
        }
    }
    return false;
}

void ReceiverClass::sync() {
    delay(STEP_TIME * 2);
    nextSample = micros() + (STEP_TIME * 1000) / 2;
}



String ReceiverClass::read() {
    receivedText = "";
    endCheckStart = 0;

    while (true) {

        // --- 1. STARTBIT LESEN ---
        while (micros() < nextSample);
        nextSample += STEP_TIME * 1000;

        if (ledIsOn()) {
            // Startbit muss 0 sein → wenn nicht, Zeichen überspringen
            continue;
        }

        // --- 2. 7 DATENBITS LESEN ---
        byte current = 0;

        for (int i = 0; i < 7; i++) {
            while (micros() < nextSample);
            nextSample += STEP_TIME * 1000;

            current = (current << 1) | (ledIsOn() ? 1 : 0);
        }

        // --- 3. STOPBIT IGNORIEREN ---
        while (micros() < nextSample);
        nextSample += STEP_TIME * 1000;

        // --- 4. ZEICHEN SPEICHERN ---
        receivedText += (char)current;

        // --- 5. END-SIGNAL PRÜFEN ---
        if (!ledIsOn()) {
            if (endCheckStart == 0) endCheckStart = millis();
            if (millis() - endCheckStart > 400) return receivedText;
        } else {
            endCheckStart = 0;
        }
    }
}



void ReceiverClass::showText(String txt) {
    Serial.println(txt);
}
