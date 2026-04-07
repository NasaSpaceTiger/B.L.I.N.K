#ifndef SENDER_H
#define SENDER_H

#include <Arduino.h>
#include "Parameter.h"
#include "Receiver.h"

class SenderClass {
public:
    void init();
    bool wantsToSend();
    void startSignal();
    void send(String txt);

private:
    void waitNextBit(unsigned long &t);
    void sendLetter(char c);
};

extern SenderClass Sender;

#endif

