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
}
