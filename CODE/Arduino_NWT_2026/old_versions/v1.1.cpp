// funktioniert ok

#include <Arduino.h>

String text = "PP";

int ledPin = 11;
int stepTime = 1000; // ms pro Schritt 

//Array 27 Einträgen mit Typ String
String code[27] = {
  "00001", // A
  "00010", // B
  "00011", // C
  "00100", // D
  "00101", // E
  "00110", // F
  "00111", // G
  "01000", // H
  "01001", // I
  "01010", // J
  "01011", // K
  "01100", // L
  "01101", // M
  "01110", // N
  "01111", // O
  "10000", // P
  "10001", // Q
  "10010", // R
  "10011", // S
  "10100", // T
  "10101", // U
  "10110", // V
  "10111", // W
  "11000", // X
  "11001", // Y
  "11010", // Z
  "11111"  // Leerzeichen
};

void sendLetter(char c) {
  int index;

  if (c == ' ') {
    index = 26; // Leerzeichen
  } else if (c >= 'A' && c <= 'Z') {
    index = c - 'A';
  } else {
    return;
  }

  String pattern = code[index];

  for (int i = 0; i < 5; i++) {
    if (pattern[i] == '1') {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }
    delay(stepTime); //wie lange ein Zustand gehalten wird
  }

  delay(stepTime); // Pause zwischen Buchstaben
}

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < text.length(); i++) {
    sendLetter(text[i]);
  }
  Serial.println("fertig gesendet");

}

