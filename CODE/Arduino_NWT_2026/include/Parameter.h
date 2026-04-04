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

const int BUTTON_PIN = 8; //ldr
const int BUTTPN_PIN_START = 13;
const int BUTTPN_PIN_ToggleLamp = 12;

// Zeit für Synchronisation
//const int SYNC_ON_TIME = 5000;   // LED AN
const int SYNC_ON_TIME = 2000;   // LED AN
const int SYNC_OFF_TIME = 1001;  // LED AUS

// Zeit, wie lange LED AN sein muss, um Übertragung zu beenden
const int END_TIME = 4000;

#endif
