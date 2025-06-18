#include <LPC21xx.H>
#include "servo.h"

#include "led.h"
#include "timer_interrupts.h"

#define DETECTOR_bm (1<<10)

void DetectorInit(void) {
	IO0DIR &= ~(DETECTOR_bm);
}	

enum DetectorState {ACTIVE, INACTIVE};

enum DetectorState eReadDetector(void){
	if (0 == (IO0PIN & DETECTOR_bm)) {
		return ACTIVE;
	}	
	return INACTIVE;
}

enum ServoState {CALLIB, IDLE, IN_PROGRESS};

struct Servo
{
	enum ServoState eState; 
	unsigned int uiCurrentPosition; 
	unsigned int uiDesiredPosition;
}; 

struct Servo sServo;

void Automat(void) {

	switch(sServo.eState){
	case CALLIB:
		if (eReadDetector() == ACTIVE) {
			sServo.eState = IDLE;
			sServo.uiCurrentPosition = 0;
			sServo.uiDesiredPosition = 0;
		}	else {
			LedStepLeft();
			sServo.eState = CALLIB;
		}	
		break;
	case IN_PROGRESS:
		if (sServo.uiDesiredPosition == sServo.uiCurrentPosition){
			sServo.uiCurrentPosition %= 48;
			sServo.uiDesiredPosition %= 48;
			sServo.eState = IDLE;
		} else if (sServo.uiDesiredPosition >= 48){
			LedStepRight();
			sServo.uiCurrentPosition++;
			sServo.eState = IN_PROGRESS;
		} else if (sServo.uiCurrentPosition < sServo.uiDesiredPosition) {
			LedStepRight();
			sServo.uiCurrentPosition = (sServo.uiCurrentPosition+1)%48;
			sServo.eState = IN_PROGRESS;
		} else if (sServo.uiCurrentPosition > sServo.uiDesiredPosition) {
			LedStepLeft();
			sServo.uiCurrentPosition = (sServo.uiCurrentPosition-1)%48;
			sServo.eState = IN_PROGRESS;
		}	
		break;
	case IDLE:
		if (sServo.uiCurrentPosition != sServo.uiDesiredPosition) {
			sServo.eState = IN_PROGRESS;
		}	else {
			sServo.eState = IDLE;
		}	
		break;
	}
	
}	

void ServoInit(unsigned int uiServoFrequency){
	Timer0Interrupts_Init((1000000/uiServoFrequency), &Automat);
	LedInit();
	DetectorInit();
}

void ServoCallib(void){
	sServo.eState = CALLIB;
}	

void ServoGoTo(unsigned int uiPosition){
	sServo.uiDesiredPosition = uiPosition;
}	

void ServoTurn90(void) {
	sServo.uiDesiredPosition += 12;
}	
