//sender
/*#include <Arduino.h>

String text = "HALLO";

int ledPin = 11;
int stepTime = 100; // ms pro Schritt 

String code[27] = {
  "00001","00010","00011","00100","00101","00110","00111","01000","01001",
  "01010","01011","01100","01101","01110","01111","10000","10001","10010",
  "10011","10100","10101","10110","10111","11000","11001","11010",
  "11111"  // Leerzeichen
};

void sendLetter(char c) {
  int index;

  if (c == ' ') index = 26;
  else if (c >= 'A' && c <= 'Z') index = c - 'A';
  else return;

  String pattern = code[index];

  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPin, pattern[i] == '1' ? HIGH : LOW);
    delay(stepTime); //Pause zwischen Werten
  }

}

void setup() {
  pinMode(ledPin, OUTPUT);

  // Synchronisation:
  digitalWrite(ledPin, HIGH);
  delay(10000);
  digitalWrite(ledPin, LOW);
  delay(3000);

}

void loop() {
  for (int i = 0; i < text.length(); i++) {
    sendLetter(text[i]);
  }

  // Stoppt nach dem Senden
  while (true);
}*/

// empfänger
#include <Arduino.h>

int ldrPin = A0;          
int threshold = 600;      
int stepTime = 100;      

bool synchronizedOnce = false;
bool seenOn = false;

unsigned long nextSample = 0;

String code[27] = {
  "00001","00010","00011","00100","00101","00110","00111","01000","01001",
  "01010","01011","01100","01101","01110","01111","10000","10001","10010",
  "10011","10100","10101","10110","10111","11000","11001","11010",
  "11111"
};

char decodePattern(String pattern) {
  for (int i = 0; i < 27; i++) {
    if (pattern == code[i]) {
      if (i == 26) return ' ';
      return 'A' + i;
    }
  }
  return '?';
}

bool ledIsOn() {
  int value = analogRead(ldrPin);
  return value > threshold;
}

bool readBit() {
  while (millis() < nextSample);
  bool on = ledIsOn();
  nextSample += stepTime;
  return on;
}

String readPattern() {
  String pattern = "";
  for (int i = 0; i < 5; i++) {
    bool bit = readBit();
    pattern += (bit ? "1" : "0");

    Serial.print("  Bit ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(bit ? "HIGH" : "LOW");
  }
  return pattern;
}

void setup() {
  Serial.begin(9600);
  Serial.println("Empfänger gestartet.");
  Serial.println("Starte einmalige Synchronisation...");
}

void loop() {

  if (!synchronizedOnce) {

    bool on = ledIsOn();

    // 1. LED muss einmal AN gewesen sein
    if (!seenOn) {
      if (on) {
        seenOn = true;
        Serial.println("LED wurde AN erkannt. Warte jetzt auf AUS...");
      }
      return;
    }

    // 2. Jetzt auf AUS warten
    if (!on) {
      Serial.println("LED ist AUS. Prüfe ob sie 3 Sekunden AUS bleibt...");

      unsigned long start = millis();

      while (!ledIsOn()) {
        if (millis() - start >= 3000) {

          //in der Bitmitte lesen
          nextSample = millis() + (stepTime / 2);

          Serial.println("Synchronisiert! Starte Datenempfang...");
          synchronizedOnce = true;
          break;
        }
      }

      if (!synchronizedOnce) {
        Serial.println("LED wurde wieder AN → Synchronisation neu starten...");
        seenOn = false;
      }
    }

    return;
  }

  Serial.println("Lese 5-Bit-Muster...");
  String pattern = readPattern();
  char letter = decodePattern(pattern);

  Serial.print("Empfangenes Muster: ");
  Serial.print(pattern);
  Serial.print(" → ");
  Serial.println(letter);
}