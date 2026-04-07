#include "sender.h"

SenderClass Sender;

void SenderClass::init() {
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTPN_PIN_START, INPUT_PULLUP);
    digitalWrite(LED_PIN, HIGH); // Idle
}

bool SenderClass::wantsToSend() {

    if (digitalRead(BUTTPN_PIN_START) == LOW) { //gedrückt

        if (!Receiver.ledIsOn()) {
            // Der andere sendet
            return false;
        }

        // sonst ich senden
        return true;
    }

    return false;
}

void SenderClass::startSignal() {
    digitalWrite(LED_PIN, LOW);
    delay(1000); // 1s AUS -> Start
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

    digitalWrite(LED_PIN, HIGH); // Idle
}
