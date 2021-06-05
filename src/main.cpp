#include <Encoder.h>
#include <PID_controller.h>
#include <Hbridge.h>
#include <MessageUtilities.h>

const uint8_t sensorpin1 = 14,sensorpin2 = 27,pwm_cwpin = 32, pwm_ccwpin = 33; 
volatile float ref,lecture,error,uSignal;
volatile bool Int,mode;
hw_timer_t*timerint=NULL;
Encoder quadencoder(sensorpin1,sensorpin2,8);
PID pid(2,0.4,0.01,0.01);
Hbridge hbridge(pwm_cwpin,pwm_ccwpin,1,3.5);

void IRAM_ATTR onTime(){
  Int=true;
}

void setup() {
  Serial.begin(115200);
  timerint=timerBegin(1,80,true);
  timerAttachInterrupt(timerint,onTime,true);
  timerAlarmWrite(timerint,10000,true);
  timerAlarmEnable(timerint);
  quadencoder.startread();
}

void loop() {
  if (Int)
  {
    Int=false;
    if (!mode)
    {
      lecture = quadencoder.position();
    }
    else
    {
      lecture = quadencoder.velocity();
    }
    error = ref-lecture;  
    uSignal = pid.controlSignal(error);
    hbridge.apply(uSignal);
    Serial.printf("%.3f,%.3f,%.3f,%.3f,%u,%.3f\n",lecture,error,uSignal,ref,quadencoder.getCW(),quadencoder.position());
  }
  if (Serial.available())
  {
    char *m;
    volatile float read[5];
    String message = Serial.readStringUntil('\n');
    volatile uint8_t messsz=message.length()+1;
    char mssg[messsz];
    message.toCharArray(mssg,messsz);
    m=mssg;
    parseString(m,",",read);
    if (read[0]==1)
    {
      mode=true;
    }
    else mode=false;;
    ref=read[1];
    pid.setKp(read[2]);
    pid.setKi(read[3]);
    pid.setKd(read[4]);
  }
}