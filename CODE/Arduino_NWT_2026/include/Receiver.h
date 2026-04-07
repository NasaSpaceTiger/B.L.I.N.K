#ifndef RECEIVER_H
#define RECEIVER_H

#include <Arduino.h>
#include "Parameter.h"

class ReceiverClass {
public:
    void init();
    void calibrateThreshold();
    bool detectStartSignal();
    void sync();
    String read();
    void showText(String txt);

    bool ledIsOn();

private:
    int threshold = 8000;
    unsigned long nextSample = 0;
    unsigned long endCheckStart = 0;
    String receivedText = "";
};

extern ReceiverClass Receiver;

#endif
