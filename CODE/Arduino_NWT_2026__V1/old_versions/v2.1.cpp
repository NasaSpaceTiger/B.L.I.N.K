//sender
#include <Arduino.h>

String text = "HALLO DAS IST EIN TEST";

int ledPin = 11;
int stepTime = 40; // ms pro Schritt 

String code[27] = {
  "00001",  // A
  "00010",  // B
  "00011",  // C
  "00100",  // D
  "00101",  // E
  "00110",  // F
  "00111",  // G
  "01000",  // H
  "01001",  // I
  "01010",  // J
  "01011",  // K
  "01100",  // L
  "01101",  // M
  "01110",  // N
  "01111",  // O
  "10000",  // P
  "10001",  // Q
  "10010",  // R
  "10011",  // S
  "10100",  // T
  "10101",  // U
  "10110",  // V
  "10111",  // W
  "11000",  // X
  "11001",  // Y
  "11010",  // Z
  "11111"   // Leerzeichen
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
  while (true){
    digitalWrite(ledPin, HIGH);
  }
}

// empfänger
/*#include <Arduino.h>

int ldrPin = A0;          
int threshold = 700;      
int stepTime = 40;      

bool synchronizedOnce = false;
bool seenOn = false;

unsigned long nextSample = 0;
unsigned long endCheckStart = 0;

String receivedText = "";

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

    if (!seenOn) {
      if (on) {
        seenOn = true;
        Serial.println("LED wurde AN erkannt. Warte jetzt auf AUS...");
      }
      return;
    }

    if (!on) {
      Serial.println("LED ist AUS. Prüfe ob sie 3 Sekunden AUS bleibt...");

      unsigned long start = millis();

      while (!ledIsOn()) {
        if (millis() - start >= 3000) {

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

  String pattern = readPattern();
  char letter = decodePattern(pattern);

  receivedText += letter;

  if (ledIsOn()) {
    if (endCheckStart == 0) endCheckStart = millis();

    if (millis() - endCheckStart > 4000) {  // 4 Sekunden AN = fertig
      Serial.println("\n--- Übertragung abgeschlossen ---");
      Serial.print("Gesamter Text: ");
      Serial.println(receivedText);
      while (true); // Stoppen
    }
  } else {
    endCheckStart = 0;
  }
}*/