#ifndef __FILTER_H__
#define __FILTER_H__
#include <Arduino.h>
class Filter{
public:
    Filter(float b[],float a[],uint8_t NumB,uint8_t NumA);
    ~Filter();
    float Filt(float X);
private:
    uint8_t _NumB;
    uint8_t _NumA;
    float *_b;
    float *_a;
    float _Xx[5];
    float _Yy[5];
};
#endif // __FILTER_H__