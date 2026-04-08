#include "receiver.h"

ReceiverClass Receiver;

bool ReceiverClass::ledIsOn() {
    return analogRead(LDR_PIN) > threshold;
}

void ReceiverClass::init() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    Serial.begin(9600);
}

void ReceiverClass::calibrateThreshold() {
    Serial.println("Threshold setzen: Taste drücken...");
    while (digitalRead(BUTTON_PIN) == HIGH);
    threshold = analogRead(LDR_PIN) - THRESHOLD_OFFSET;
    Serial.print("Threshold: ");
    Serial.println(threshold);
    delay(500);
}

bool ReceiverClass::detectStartSignal() {
    if (ledIsOn()) return false;

    unsigned long t = millis();
    while (!ledIsOn()) {
        if (millis() - t > 998) {
            return true; // Startsignal erkannt
        }
    }
    return false;
}

void ReceiverClass::sync() {
    nextSample = millis() + (STEP_TIME / 2);
}

String ReceiverClass::read() {
    receivedText = "";
    endCheckStart = 0;

    byte current = 0; //hier werden bits eines Zeichens gesammelt
    int count = 0; //wie viele bits in current drinnen sind (wenn =7, dann ein zeichen)

    while (true) {
        while (millis() < nextSample);
        nextSample += STEP_TIME; //festlegen bis wann der durchlauf geht

        bool bit = ledIsOn();//aktuelllen bit lesen(true/false)

        current = (current << 1) | (bit ? 1 : 0);// bisherigen Wert um 1 Bit nach links schieben und das neue Bit anhängen
        count++;//hochsetzen um +1


        if (count == 7) { //komplettes Zeichen erkennen
            receivedText += (char)current; //in Zeichen umwandeln
            current = 0;//variablen zurücksetzen für nächstes zeichen
            count = 0;//variablen zurücksetzen für nächstes zeichen
        }

        //rausgehen wenn led END_TIME lan an ist
        if (ledIsOn()) {
            if (endCheckStart == 0) endCheckStart = millis();
            if (millis() - endCheckStart > END_TIME) {
                return receivedText; 
            }
        } else {
            endCheckStart = 0;
        }
    }
}


void ReceiverClass::showText(String txt) {
    Serial.println(txt);
}
