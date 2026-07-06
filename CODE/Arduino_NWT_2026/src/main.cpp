/*
#include <Arduino.h>
#include "sender.h"
#include "receiver.h"
#include "Parameter.h"

String text = "Hallo Pichlers!!!";

void setup() {
    Sender.init();
    Receiver.init();

    digitalWrite(LED_PIN, HIGH); // Idle

    Receiver.calibrateThreshold();
}

void loop() {
    //Serial.println( analogRead(LDR_PIN));

    // 1. Ich will senden
    if (Sender.wantsToSend()) {
        Sender.startSignal();
        Sender.send(text);
        return;
    }

    // 2. Der andere will senden
    if (Receiver.detectStartSignal()) {
        Receiver.sync();
        String msg = Receiver.read();
        Receiver.showText(msg);
        digitalWrite(LED_PIN, HIGH);
        return;
    }

    //3. Text ändern
    if (Serial.available()) {
        text = Serial.readStringUntil('\n');   // ganze Zeile einlesen
        text.trim();                           // Zeilenumbruch entfernen
        Serial.print("Neuer Text gesetzt: ");
        Serial.println(text);
    }


    // 4. Idle
    digitalWrite(LED_PIN, HIGH);
}*/




//ein sender ein empfänger
//sender
/*#include <Arduino.h>

String text = "Hallo Andi. test";

#include <Arduino.h>
#include "sender.h"

void setup() {
  Sender.init();
  while(digitalRead(BUTTPN_PIN_START) == HIGH){ //aus
    if(digitalRead(BUTTPN_PIN_ToggleLamp) == LOW){ //an
      digitalWrite(LED_PIN, HIGH); //an
      delay(3000);
    }
    digitalWrite(LED_PIN, LOW); //aus
  }
  Sender.Sync();
}

void loop() {
  Sender.send(text);
}*/

/*#include <Arduino.h>
#include "sender.h"
#include "receiver.h"
#include "parameter.h"

Sender sender;
Receiver receiver;

void setup() {
    Serial.begin(9600);

    pinMode(BTN_SEND, INPUT_PULLUP);
    pinMode(BTN_CALIB, INPUT_PULLUP);

    sender.begin();
    receiver.begin();

    Serial.println("Kalibrierung: Button drücken...");
    while (digitalRead(BTN_CALIB)) {}
    receiver.calibrate();
    Serial.println("Kalibriert!");
}

void loop() {
    if (!digitalRead(BTN_SEND)) {
        sender.sendText("HALLO");
        delay(500);
    }

    if (receiver.detectStart()) {
        int c = receiver.readChar();
        Serial.print("Empfangen: ");
        Serial.println((char)(c + 32));
    }
}*/






#include <Arduino.h>

const int LED_PIN = 8;
const int BUTTON_PIN = 2;
const int SENSOR_PIN = A0;

const int THRESHOLD = 500;
const unsigned int BIT_TIME = 50; // ms

String message = "Hello world";

bool receiving = false;


void sendByte(byte data)
{
  // Startbit
  digitalWrite(LED_PIN, HIGH);
  delay(BIT_TIME);

  // 8 Datenbits
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(LED_PIN, bitRead(data, i));
    delay(BIT_TIME);
  }

  // Stopbit
  digitalWrite(LED_PIN, LOW);
  delay(BIT_TIME);

  // kleine Pause
  delay(BIT_TIME);
}

void sendMessage(String text)
{
  // Synchronisation
  for (int i = 0; i < 10; i++)
  {
    sendByte(0x55);
  }

  // Startmarker
  sendByte('<');

  for (unsigned int i = 0; i < text.length(); i++)
  {
    sendByte(text[i]);
  }

  // Endmarker
  sendByte('>');
}

byte receiveByte()
{
  // auf Startbit warten
  while (analogRead(SENSOR_PIN) < THRESHOLD)
  {

    // gleichzeitig Taster prüfen
    if (digitalRead(BUTTON_PIN) == LOW)
    {
        Serial.print("Sende Nachricht: ");
        Serial.println(message);
        sendMessage(message);
    }
    //Text ändern
    if (Serial.available()) {
        message = Serial.readStringUntil('\n');   // Zeile einlesen
        message.trim();                           // Zeilenumbruch entfernen
        Serial.print("Textänderung bestätigt:");
        Serial.println(message);
    }
  }

  // Mitte erstes Datenbit
  delay(BIT_TIME + BIT_TIME / 2);

  byte value = 0;

  for (int i = 0; i < 8; i++)
  {
    int sensor = analogRead(SENSOR_PIN);

    if (sensor > THRESHOLD)
    {
      bitSet(value, i);
    }

    delay(BIT_TIME);
  }

  // Stopbit überspringen
  delay(BIT_TIME);

  return value;
}

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  digitalWrite(LED_PIN, LOW);

  Serial.begin(9600);

  delay(10);
}

void loop()
{
  //Serial.println(analogRead(SENSOR_PIN));
  
  byte c = receiveByte();

  // Synchronisationsbytes ignorieren
  if (c == 0x55)
  {
    return;
  }

  if (c == '<')
  {
    receiving = true;
    Serial.println();
    Serial.print("Empfangen:  ");
    return;
  }

  if (c == '>')
  {
    receiving = false;
    Serial.println();
    Serial.println("--- Ende ---");
    return;
  }

  if (receiving)
  {
    Serial.print((char)c);
  }

}