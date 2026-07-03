/*#ifndef SENDER_H
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

#endif*/
/*
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

#endif*/

#pragma once
#include <Arduino.h>

class Sender {
public:
    void begin();
    void sendChar(uint8_t value);
    void sendText(const char* txt);

private:
    void sendBit(bool bit);
    void sendStart();
    void sendStop();
};
