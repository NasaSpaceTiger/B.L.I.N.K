#ifndef PARAMETER_H
#define PARAMETER_H

// Bitzeit in ms
const int STEP_TIME = 10;

const int LED_PIN = 11;
const int LDR_PIN = A0;

// Threshold-Offset beim Kalibrieren
const int THRESHOLD_OFFSET = 60;

const int BUTTON_PIN = 8; //ldr synchronisiren
const int BUTTPN_PIN_START = 13; //dann startet die übertragung

// Zeit, wie lange LED AN sein muss, um Übertragung zu beenden
const int END_TIME = 3000;

#endif
