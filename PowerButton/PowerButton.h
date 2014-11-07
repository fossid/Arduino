#ifndef PowerButton_h
#define PowerButton_h

#include "Arduino.h"

#define POWER_ON  1
#define POWER_OFF 0

class PowerButtonSwitch {
	public:
    PowerButtonSwitch();
    void setupPowerButton(int,int, int);
    int getSwitchStatus();
    int onPowerOn(void (*)());
    int onPowerOff(void (*)());
    
	private:
    int outputPin;
    
    static int inputPin;
    static int status;
    static void PowerEvent();
    static void (*user_onPowerOnEvent)();
    static void (*user_onPowerOffEvent)();
};

#endif