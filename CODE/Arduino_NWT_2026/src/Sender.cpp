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
    t += STEP_TIME * 1000;// Zeit für nächstes Bit setzen
    while (micros() < t);// warten bis Bitdauer vorbei ist
}

void SenderClass::sendLetter(char c) {
    byte ascii = c;// ASCII‑Wert des Zeichens holen
    unsigned long t = micros();// Startzeit für erstes Bit

    for (int i = 6; i >= 0; i--) {
        bool bit = (ascii >> i) & 1; // einzelnes Bit herausfinden
        digitalWrite(LED_PIN, bit ? HIGH : LOW);// LED je nach Bit setzen
        waitNextBit(t);// Bitdauer abwarten
    }
}

void SenderClass::send(String txt) {
    for (int i = 0; i < txt.length(); i++) {
        sendLetter(txt[i]);//Zeichen senden
    }

    digitalWrite(LED_PIN, HIGH);// zurück in Idle (LED an)
}
