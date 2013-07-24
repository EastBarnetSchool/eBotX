#include "Arduino.h"

#ifndef EbotX_H
#define EbotX_H

class Motor { 
public:
    Motor(char motor);
    ~Motor();
    void forward(int speed);
    void reverse(int speed);
    void stop();
    void resetDistance();
    int checker();
    int distance();
private:
    char _motor;
};

class LED { 
public:
    LED(int led);
    ~LED();
    void on();
    void off();
    void blink();
    void blink(int delay_seconds);
private:
    int LED_pin;
};

class DistanceSensor { 
public:
    DistanceSensor();
    ~DistanceSensor();
    long read();
private:
    long duration;
    long distance;
};

class MicroSwitch { 
public:
    MicroSwitch();
    ~MicroSwitch();
    boolean read();
private:
    long value;
};


#endif









