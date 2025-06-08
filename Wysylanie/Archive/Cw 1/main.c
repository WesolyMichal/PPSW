#include <LPC21xx.H>
#include "uart.h"

int main(){
	UART_InitWithInt(9600);
	U0THR = 0;
	
	while(1){}
}	
