#include <Filter.h>
#include <Arduino.h>

Filter::Filter(float b[],float a[],uint8_t NumB,uint8_t NumA) 
{
    _NumB=NumB;
    _NumA=NumA;
    _b=b;
    _a=a;
}

Filter::~Filter() 
{
    
}

float Filter::Filt(float X) 
{
    float Y0=0;
    for (uint8_t i = _NumB-1; i > 0; i--)
    {
        _Xx[i]=_Xx[i-1];
        Y0 += _Xx[i]*_b[i];
    }
    _Xx[0]=X;
    Y0 += _Xx[0]*_b[0];
    for (uint8_t i = _NumA-1; i > 0; i--)
    {
        _Yy[i]=_Yy[i-1];
        Y0-=_Yy[i]*_a[i];
    }
    _Yy[0]=Y0;
    return(_Yy[0]);
}