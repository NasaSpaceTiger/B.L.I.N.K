#ifndef RECEIVER_H
#define RECEIVER_H

#include <Arduino.h>
#include "Parameter.h"

class ReceiverClass {
  public:
    void init();
    void sync();
    String read();
    void showText(String txt);

  private:
    int threshold = 8700;

    bool synchronizedOnce = false;
    unsigned long nextSample = 0;
    unsigned long endCheckStart = 0;

    String receivedText = "";

    bool ledIsOn();
    bool readBit();
    char readAsciiChar();
};

extern ReceiverClass Receiver;

#endif
