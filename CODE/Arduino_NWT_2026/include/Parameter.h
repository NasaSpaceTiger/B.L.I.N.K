/*#ifndef PARAMETER_H
#define PARAMETER_H

// Bitzeit in ms
const int STEP_TIME = 30;

const int LED_PIN = 9;
const int LDR_PIN = A0;

// Threshold-Offset beim Kalibrieren
const int THRESHOLD_OFFSET = 90; //90

const int BUTTON_PIN = 11; //ldr synchronisiren
const int BUTTPN_PIN_START = 10; //dann startet die übertragung

// Zeit, wie lange LED AN sein muss, um Übertragung zu beenden
const int END_TIME = 1000;

#endif*/
/*
#ifndef PARAMETER_H
#define PARAMETER_H

// Bitzeit in ms
const int STEP_TIME = 20;

const int LED_PIN = 11;
const int LDR_PIN = A0;

// Threshold-Offset beim Kalibrieren
const int THRESHOLD_OFFSET = 90;

const int BUTTON_PIN = 8; //ldr synchronisiren
const int BUTTPN_PIN_START = 13; //dann startet die übertragung

// Zeit, wie lange LED AN sein muss, um Übertragung zu beenden
const int END_TIME = 500;

#endif*/

#pragma once

#define LED_PIN 9
#define LDR_PIN A0

#define BTN_SEND 3
#define BTN_CALIB 2

#define BIT_TIME 100
#define START_TIME 100
#define STOP_TIME 100

#define THRESH_MARGIN 40

#define XOR_KEY 23   // 6-bit key (0–63)
