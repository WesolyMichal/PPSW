#include "uart.h"

int main(){
	UART_InitWithInt(9600);
	
	while(1){
		if (Transmiter_GetStatus() == FREE){
			Transmiter_SendString("test123");
		}	
	}
}	
