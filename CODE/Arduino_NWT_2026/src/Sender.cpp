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
    delay(200);

    digitalWrite(LED_PIN, HIGH);
    delay(STEP_TIME * 2);
}



void SenderClass::waitNextBit(unsigned long &t) {
    t += STEP_TIME * 1000;// Zeit für nächstes Bit setzen
    while (micros() < t);// warten bis Bitdauer vorbei ist
}

void SenderClass::sendLetter(char c) {
    byte ascii = c;
    unsigned long t = micros();

    // Startbit = 0
    digitalWrite(LED_PIN, LOW);
    waitNextBit(t);

    // 7 Datenbits
    for (int i = 6; i >= 0; i--) {
        bool bit = (ascii >> i) & 1;
        digitalWrite(LED_PIN, bit ? HIGH : LOW);
        waitNextBit(t);
    }

    // Stopbit = 1
    digitalWrite(LED_PIN, HIGH);
    waitNextBit(t);
}

void SenderClass::send(String txt) {
    for (int i = 0; i < txt.length(); i++) {
        sendLetter(txt[i]);
    }

    // Endmarkierung: 500ms AUS
    digitalWrite(LED_PIN, LOW);
    delay(500);

    digitalWrite(LED_PIN, HIGH); // Idle
}

