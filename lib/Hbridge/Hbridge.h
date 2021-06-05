#ifndef __HBRIDGE_H__
#define __HBRIDGE_H__
#include <ESP32_PWM.h>

class Hbridge
{
private:
    float _deadband,_Max;
public:
    Hbridge(uint8_t pwm_cwpin ,uint8_t pwdm_ccwpin,float deadband, float Max);
    ~Hbridge();
    void apply(float signal);
};

#endif // __HBRIDGE_H__