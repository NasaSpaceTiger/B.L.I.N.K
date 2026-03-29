#ifndef SENDER_H
#define SENDER_H

#include <Arduino.h>
#include "Parameter.h"

class SenderClass {
  public:
    void init();
    void send(String txt);
    void Sync();

  private:
    void waitNextBit(unsigned long &t);
    void sendLetter(char c);
};

extern SenderClass Sender;

#endif
