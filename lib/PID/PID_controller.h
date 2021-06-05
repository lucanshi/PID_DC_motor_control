#ifndef __PID_CONTROLLER_H__
#define __PID_CONTROLLER_H__

class PID
{
private:
    float _T,_Kp,_Ki,_Kd,_err[2],_uSignal[2],_Ierr;
public:
    PID(float Kp, float Ki, float Kd, float T);
    ~PID();
    void setup(float T);
    void setKp(float Kp);
    void setKi(float Ki);
    void setKd(float Kd);
    float getKp();
    float getKi();
    float getKd();
    float controlSignal(float err);
};

#endif // __PID_CONTROLLER_H__