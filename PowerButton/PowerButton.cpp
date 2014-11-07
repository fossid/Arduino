#include "Arduino.h"
#include "PowerButton.h"

void (*PowerButtonSwitch::user_onPowerOnEvent)(void);
void (*PowerButtonSwitch::user_onPowerOffEvent)(void);
int PowerButtonSwitch::inputPin;
int PowerButtonSwitch::status;

PowerButtonSwitch::PowerButtonSwitch() {
  user_onPowerOnEvent  = NULL;
  user_onPowerOffEvent = NULL;
}

void PowerButtonSwitch::setupPowerButton(int inp,int outp, int interrupt) {
  inputPin  = inp;
  outputPin = outp;
    
  pinMode(inputPin, INPUT);
  pinMode(outputPin,  OUTPUT);
  
  digitalWrite(outputPin, 1);
  attachInterrupt(interrupt, PowerEvent, CHANGE);

  user_onPowerOnEvent  = NULL;
  user_onPowerOffEvent = NULL;
  
  status = digitalRead(inputPin);
}

int PowerButtonSwitch::getSwitchStatus() {
  return status;
}

int PowerButtonSwitch::onPowerOn(void (*func)()) {
  user_onPowerOnEvent = func;
}

int PowerButtonSwitch::onPowerOff(void (*func)()) {
  user_onPowerOffEvent = func;
}

void PowerButtonSwitch::PowerEvent() {
  delayMicroseconds(50);
  int local_status = digitalRead(inputPin);
  if (local_status != status) {
    status = local_status;
    Serial.println(status);
    if (status == POWER_ON) {
      if(!user_onPowerOnEvent){
        return;
      } else {
        user_onPowerOnEvent();
      }  
    } else if (status == POWER_OFF) {
      if(!user_onPowerOffEvent){
        return;
      } else {
        user_onPowerOffEvent();
      }    
    }
  }
}