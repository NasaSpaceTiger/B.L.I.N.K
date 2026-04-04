//sender
#include <Arduino.h>

String text = "Hallo Andi";

#include <Arduino.h>
#include "sender.h"

void setup() {
  Sender.init();
  Sender.Sync();
}

void loop() {
  Sender.send(text);
}



// beide leds an, wenn einer sendden will led aus und dann 3ms warten

/*
//empfänger
#include <Arduino.h>
#include "receiver.h"

void setup() {
  Receiver.init();
  Receiver.sync();
}

void loop() {
  String Message = Receiver.read();

  if (Message != "") {
    Receiver.showText(Message);
    while (true);
  }
}*/