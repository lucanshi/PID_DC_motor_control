#include <Encoder.h>
#include <Filter.h>

uint8_t _pin1,_pin2,_ppr;
volatile bool _cw;
volatile long _poss;
volatile uint64_t time0[2],_dt[2];
float b[]={0.333,0.333,0.333};
float a[]={1.0,};
Filter filter(b,a,3,1);
hw_timer_t*timer=NULL;

Encoder::Encoder(uint8_t pin1,uint8_t pin2, uint8_t ppr) 
{
    _pin1=pin1;
    _pin2=pin2;
    _ppr=ppr;
    _rpi=2*PI/(_ppr*4);
    _rpp=2*PI/_ppr;
}

void IRAM_ATTR isr1(){
    time0[1]=time0[0];
    time0[0]=timerReadMicros(timer);
    if (digitalRead(_pin1)==HIGH)
    {
        if (digitalRead(_pin2)==LOW)
        {
        _cw=false;
        _poss++;
        }
        else 
        {
        _cw=true;
        _poss--;
        }
    }
    else
    {
        if (digitalRead(_pin2)==HIGH)
        {
        _cw=false;
        _poss++;
        }
        else 
        {
        _cw=true;
        _poss--;
        }
    }
    _dt[1]=time0[0]-time0[1];
    if (_dt[1]>400)
    {
        _dt[0]=filter.Filt(_dt[1]);
    }
}
void IRAM_ATTR isr2(){
    if (digitalRead(_pin2)==HIGH)
    {
        if (digitalRead(_pin1)==LOW)
        {
        _cw=true;
        _poss--;
        }
        else 
        {
        _cw=false;
        _poss++;
        }
    }
    else
    {
        if (digitalRead(_pin1)==HIGH)
        {
        _cw=true;
        _poss--;
        }
        else 
        {
        _cw=false;
        _poss++;
        }
    }
}

Encoder::~Encoder() 
{
    
}

void Encoder::startread() 
{
    attachInterrupt(_pin1,isr1,CHANGE);
    attachInterrupt(_pin2,isr2,CHANGE);
    timer=timerBegin(0,80,true);
}

void Encoder::stopread() 
{
    detachInterrupt(_pin1);
    detachInterrupt(_pin2);
}

float Encoder::position() 
{
    _position=_rpi*_poss;
    return(_position);
}

float Encoder::velocity() 
{   
    _velocity=_rpp/(_dt[0]*0.000002);
    if (_cw)
    {
        _velocity=_velocity*(-1);
    }
    if(_velocity>5000)
    {
        _velocity=0;
    }
    return(_velocity);
}

bool Encoder::getCW() 
{
    return(_cw);
}