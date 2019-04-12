#ifndef _PUMP_H_
#define _PUMP_H_
#include "BasicStepperDriver.h"
#include "defines.h"
BasicStepperDriver stepper(TOTAL_STEPS, DIR_PIN, STEP_PIN,ENABLE_PIN);
void pump_init(int microstep, int accel, short enableHL);
    //BasicStepperDriver stepper(TOTAL_STEPS, DIR_PIN, STEP_PIN,ENABLE_PIN);
void pump_init(int microstep, int accel, short enableLH, int speed) {
    stepper.begin(speed,microstep);
    stepper.setEnableActiveState(enableLH);
    stepper.setSpeedProfile(stepper.LINEAR_SPEED, accel, accel);
    stepper.disable();
}

#endif