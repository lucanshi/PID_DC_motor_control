#ifndef __ENCODER_H__
#define __ENCODER_H__
#include <Arduino.h>

class Encoder
{
private:
    float _position,_velocity,_rpi,_rpp;
public:
    Encoder(uint8_t pin1,uint8_t pin2,uint8_t ppr);
    ~Encoder();
    void startread();
    void stopread();
    float position();
    float velocity();
    bool getCW();
};

#endif // __ENCODER_H__