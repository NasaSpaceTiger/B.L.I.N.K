//sender
#include <Arduino.h>

String text = "Hallo Andi";

int ledPin = 11;
int stepTime = 15; // ms pro Schritt 

// ASCII-Zeichen senden
void waitNextBit(unsigned long &t) {
  t += stepTime * 1000;
  while (micros() < t);
}

void sendLetter(char c) {
  byte ascii = c;
  unsigned long t = micros();

  for (int i = 6; i >= 0; i--) {

    bool bit = (ascii >> i) & 1;
    digitalWrite(ledPin, bit ? HIGH : LOW); // auf led setzen den aktuellen bit

    waitNextBit(t);
  }
}


void setup() {
  pinMode(ledPin, OUTPUT);

  // Synchronisation:
  digitalWrite(ledPin, HIGH);
  delay(7000);
  digitalWrite(ledPin, LOW);
  delay(1000);
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
int threshold = 8700; //über taster am besten noch anpasbar machen  
int stepTime = 15;

bool synchronizedOnce = false;

unsigned long nextSample = 0;
unsigned long endCheckStart = 0;

String receivedText = "";


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

//bits lesn
char readAsciiChar() {
  byte value = 0;

  for (int i = 0; i < 7; i++) {
    bool bit = readBit();
    value = (value << 1) | (bit ? 1 : 0);
  }

  return (char)value;
}

void setup() {
  digitalWrite(8, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Empfänger gestartet.");
  Serial.println("Starte einmalige Synchronisation...");

  bool seenOn = false;

  while (!synchronizedOnce) {

    if(digitalRead(8) == LOW){
      threshold = (analogRead(ldrPin) - 60);
      Serial.println("Value neu gesetzt");
    }

    bool on = ledIsOn();

    if (!seenOn) {
      if (on) {
        seenOn = true;
        Serial.println("LED wurde AN erkannt. Warte jetzt auf AUS...");
      }
      continue;
    }

    if (!on) {
      Serial.println("LED ist AUS. Prüfe ob sie 1 Sekunde AUS bleibt...");

      unsigned long start = millis();

      while (!ledIsOn()) {
        if (millis() - start >= 998) {

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
  }
}

void loop() {

  char letter = readAsciiChar();
  receivedText += letter;

  // vertig?
  if (ledIsOn()) {
    if (endCheckStart == 0) endCheckStart = millis();

    if (millis() - endCheckStart > 5000) {  // wenn 5 s an dann fertig
      Serial.println("\n--- Übertragung abgeschlossen ---");
      Serial.print("Gesamter Text: ");
      Serial.println(receivedText);
      while (true); // Stoppen
    }
  } else {
    endCheckStart = 0;
  }
}*/