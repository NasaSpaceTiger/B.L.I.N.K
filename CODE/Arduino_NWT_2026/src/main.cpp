#include <Arduino.h>
#include "sender.h"
#include "receiver.h"
#include "Parameter.h"

String text = "Hallo Andi. test";

void setup() {
  Sender.init();
  Receiver.init();

  // LED dauerhaft AN = Idle
  digitalWrite(LED_PIN, HIGH);

  // Threshold setzen
  Serial.println("Threshold setzen: Taste drücken...");
  while (digitalRead(BUTTON_PIN) == HIGH); //-> nicht machen bis button an ist (low = an)
  Receiver.calibrateThreshold();

  Serial.println("Bereit. LED ist AN.");
}

void loop() {

  // 1. ICH WILL SENDEN (Start-Taste gedrückt)
  if (digitalRead(BUTTPN_PIN_START) == LOW) {

    Serial.println("Ich will senden...");

    // LED 1 Sekunde AUS = Sync-Signal
    digitalWrite(LED_PIN, LOW);
    delay(1000);

    // Jetzt senden
    Sender.send(text);

    // Nach dem Senden wieder Idle
    digitalWrite(LED_PIN, HIGH);
    return;
  }


  // 2. DER ANDERE WILL SENDEN (LED 1 Sekunde AUS)
  if (!Receiver.ledIsOn()) {

    unsigned long t = millis();
    while (!Receiver.ledIsOn()) {

      // Wenn LED 1 Sekunde AUS bleibt → anderer sendet
      if (millis() - t > 1000) {

        Serial.println("Der andere sendet → ich empfange...");

        // Sync starten
        Receiver.sync();

        // Nachricht empfangen
        String msg = Receiver.read();

        if (msg != "") {
          Receiver.showText(msg);
        }

        // Zurück in Idle
        digitalWrite(LED_PIN, HIGH);
        return;
      }
    }
  }


  // ---------------------------------------------------
  // 3. Idle-Zustand
  // ---------------------------------------------------
  digitalWrite(LED_PIN, HIGH);
}
