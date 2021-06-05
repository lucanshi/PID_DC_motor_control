#include <PID_controller.h>

PID::PID(float Kp, float Ki, float Kd, float T) 
{
    _T=T;
    _Kp=Kp;
    _Ki=Ki;
    _Kd=Kd;
}

PID::~PID() 
{
    
}

void PID::setup(float T) 
{
    _T=T;
}

void PID::setKp(float Kp) 
{
    _Kp=Kp;
}

void PID::setKi(float Ki) 
{
    _Ki=Ki;
}

void PID::setKd(float Kd) 
{
    _Kd=Kd;
}

float PID::getKp() 
{
    return(_Kp);
}

float PID::getKi() 
{
    return(_Ki);
}

float PID::getKd() 
{
    return(_Kd);
}

float PID::controlSignal(float err) 
{
    _err[1]=_err[0];
    _err[0]= err;
    _Ierr += _err[0]*_T;
    _uSignal[1] = _uSignal[0];
    _uSignal[0] = _Kp*_err[0]+_Ki*_Ierr+_Kd*(_err[0]-_err[1]/_T);
    return(_uSignal[0]);
}
