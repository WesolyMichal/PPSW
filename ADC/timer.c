#include <LPC21xx.H>
#include "timer.h"

#define T0_ENABLE (1<<0)
#define T0_RESET (1<<1)
#define T0_MR0_INTERRUPT (1<<0)
#define T0_MR0_RESET (1<<1)
#define T0_MR0_IR (1<<0)

void InitTimer0(void){
	T0TCR |= T0_ENABLE;
}	

void WaitOnTimer0(unsigned int uiTime) {
	// 60MHz Clock, Timer Incrementation every 4 ticks ~ 15MHz
	T0TCR |= T0_RESET;
	T0TCR &= ~(T0_RESET);
	while (T0TC < (uiTime*15)) {}
}	

void InitTimer0Match0(unsigned int iDelayTime) {
	T0MCR |= T0_MR0_INTERRUPT | T0_MR0_RESET;
	T0MR0 = iDelayTime * 15;
	T0TCR |= T0_RESET;
	T0TCR &= ~(T0_RESET);
}	

void WaitOnTimer0Match0(void) {
	while ( (T0IR & T0_MR0_IR) == 0 ) {}
	T0IR |= T0_MR0_IR;
}	
