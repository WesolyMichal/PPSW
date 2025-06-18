#include "uart.h"
#include "string_op.h"
#include "timer_interrupts.h"
#include "command_decoder.h"

extern struct Token asToken[MAX_TOKEN_NR];
extern unsigned char ucTokenNr;

struct Watch { 
	unsigned char ucMinutes, ucSeconds; 
	unsigned char fSecondsValueChanged, fMinutesValueChanged; 
};

struct Watch sWatch;

void WatchUpdate(void){
	sWatch.ucSeconds = (sWatch.ucSeconds+1)%60;
	sWatch.fSecondsValueChanged = 1;
	if (sWatch.ucSeconds == 0){
		sWatch.ucMinutes += 1;
		sWatch.fMinutesValueChanged = 1;
	}	
};

char acMsg[TRANSMITER_SIZE];

int main(){
	
	char acReceivedMessage[RECIEVER_SIZE];
	
	Timer0Interrupts_Init(1000000, &WatchUpdate);
	UART_InitWithInt(9600);
	
	
	while(1){
		if (Transmiter_GetStatus() == FREE){
			
			if (sWatch.fSecondsValueChanged == 1){
				
				CopyString("sec ", acMsg);
				AppendUIntToString(sWatch.ucSeconds, acMsg);
				AppendString("\n", acMsg);
				Transmiter_SendString(acMsg);
				sWatch.fSecondsValueChanged = 0;
				
			} else if (sWatch.fMinutesValueChanged == 1) {
				
				CopyString("min ", acMsg);
				AppendUIntToString(sWatch.ucMinutes, acMsg);
				AppendString("\n", acMsg);
				Transmiter_SendString(acMsg);
				sWatch.fMinutesValueChanged = 0;
				
			} else if(eReciever_GetStatus() == READY){
				
				Reciever_GetStringCopy(acReceivedMessage);
				DecodeMsg(acReceivedMessage);
				
				if ((ucTokenNr != 0) && (asToken[0].eType == KEYWORD)) {
					
					switch (asToken[0].uValue.eKeyword){
					case CLC:
						
						if (asToken[1].eType == NUMBER){
							CopyString("clc ", acMsg);
							AppendUIntToString( ( asToken[1].uValue.uiValue * 2 ), acMsg);
							AppendString("\n", acMsg);
							Transmiter_SendString(acMsg);		
						}
						
					default:
						break;
					}
				}	
			}
		}	
	}
}	
