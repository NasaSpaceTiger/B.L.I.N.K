#ifndef PARAMETER_H
#define PARAMETER_H

// Gemeinsame Parameter für Sender & Empfänger

// Bitzeit in Millisekunden
const int STEP_TIME = 15;

// Sender-Pin
const int LED_PIN = 11;

// Empfänger-Pin
const int LDR_PIN = A0;

// Threshold-Offset beim Kalibrieren
const int THRESHOLD_OFFSET = 60;

const int BUTTON_PIN = 8; //ldr synchronisiren
const int BUTTPN_PIN_START = 13; //dann startet die übertragung

// Zeit, wie lange LED AN sein muss, um Übertragung zu beenden
const int END_TIME = 4000;

#endif
