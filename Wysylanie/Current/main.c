#include "uart.h"
#include "string_op.h"

unsigned int uiLicznik = 0;
char acLiczba[18] = "liczba ";

int main(){
	UART_InitWithInt(9600);
	
	while(1){
		if (Transmiter_GetStatus() == FREE){
			UIntToHexStr (uiLicznik, acLiczba + 7);
			Transmiter_SendString(acLiczba);
			uiLicznik++;
		}	
	}
}	
