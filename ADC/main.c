#include "adc.h"
#include "servo.h"

char cADC_VAL[7];

int main(void) {
	ADC_Init();
	ServoInit(60);
	
	while (1) {
		ServoGoTo(ADC_GetValue());
		ADC_Start();
	}
}

