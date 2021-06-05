#include <Hbridge.h>
#define FREQ 50

PWM pwm_cw,pwm_ccw;

Hbridge::Hbridge(uint8_t pwm_cwpin,uint8_t pwdm_ccwpin,float deadband, float Max) 
{
    _deadband=deadband;
    _Max=Max;
    pwm_cw.setup(pwm_cwpin,1,FREQ);
    pwm_ccw.setup(pwdm_ccwpin,2,FREQ);
}

Hbridge::~Hbridge() 
{
    
}

void Hbridge::apply(float uSignal) 
{
    if (uSignal>=0)
    {
        pwm_cw.setDuty(0);
        pwm_ccw.setDuty(uSignal);
    }
    else
    {
        pwm_ccw.setDuty(0);
        pwm_cw.setDuty(uSignal*-1);
    }
}
