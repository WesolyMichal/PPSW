#include <LPC210X.H>
#include "uart.h"

/************ UART ************/
// U0LCR Line Control Register
#define mDIVISOR_LATCH_ACCES_BIT                   0x00000080
#define m8BIT_UART_WORD_LENGTH                     0x00000003

// UxIER Interrupt Enable Register
#define mRX_DATA_AVALIABLE_INTERRUPT_ENABLE        0x00000001
#define mTHRE_INTERRUPT_ENABLE                     0x00000002

// UxIIR Pending Interrupt Identification Register
#define mINTERRUPT_PENDING_IDETIFICATION_BITFIELD  0x0000000F
#define mTHRE_INTERRUPT_PENDING                    0x00000002
#define mRX_DATA_AVALIABLE_INTERRUPT_PENDING       0x00000004

/************ Interrupts **********/
// VIC (Vector Interrupt Controller) channels
#define VIC_UART0_CHANNEL_NR  6
#define VIC_UART1_CHANNEL_NR  7

// VICVectCntlx Vector Control Registers
#define mIRQ_SLOT_ENABLE                           0x00000020

void Reciever_PutCharacterToBuffer(char cCharacter);

#include "string_op.h"
#define TERMINATOR '\r'
#define NULL '\0'
#define TRANSMITER_SIZE 18

struct TransmiterBuffer{
	char cData[TRANSMITER_SIZE];
	enum eTransmiterStatus eStatus;
	unsigned char fLastCharacter;
	unsigned char ucCharCtr;
};

struct TransmiterBuffer sTransmiterBuffer;

char Transmiter_GetCharacterFromBuffer(void){
	if (sTransmiterBuffer.fLastCharacter == 1) {
		return NULL;
	} else if (sTransmiterBuffer.cData[sTransmiterBuffer.ucCharCtr] == NULL){
		sTransmiterBuffer.fLastCharacter = 1;
		return TERMINATOR;
	}	else {
		sTransmiterBuffer.ucCharCtr++;
		return sTransmiterBuffer.cData[sTransmiterBuffer.ucCharCtr];
	}	
}

void Transmiter_SendString(char cString[]){
	CopyString(cString, sTransmiterBuffer.cData);
	U0THR = sTransmiterBuffer.cData[0];
	sTransmiterBuffer.fLastCharacter = 0;
	sTransmiterBuffer.ucCharCtr = 0;
	sTransmiterBuffer.eStatus = BUSY;
	while (sTransmiterBuffer.eStatus == BUSY){}
}	

enum eTransmiterStatus Transmiter_GetStatus(void){
	return sTransmiterBuffer.eStatus;
}	

unsigned char ucCharCounter = 0;

__irq void UART0_Interrupt (void) {
   // jesli przerwanie z odbiornika (Rx)
   
   unsigned int uiCopyOfU0IIR=U0IIR; // odczyt U0IIR powoduje jego kasowanie wiec lepiej pracowac na kopii

   if      ((uiCopyOfU0IIR & mINTERRUPT_PENDING_IDETIFICATION_BITFIELD) == mRX_DATA_AVALIABLE_INTERRUPT_PENDING) // odebrano znak
   {
		 Reciever_PutCharacterToBuffer(U0RBR); 
   } 
   
   if ((uiCopyOfU0IIR & mINTERRUPT_PENDING_IDETIFICATION_BITFIELD) == mTHRE_INTERRUPT_PENDING)              // wyslano znak - nadajnik pusty 
   {
		 switch(Transmiter_GetStatus())
		 case BUSY:
			 if (sTransmiterBuffer.fLastCharacter == 1){
				 sTransmiterBuffer.eStatus = FREE;
			 } else {
				 sTransmiterBuffer.eStatus = BUSY;
			 U0THR = Transmiter_GetCharacterFromBuffer();
			 break;
		 case FREE:
			 break;
		 }
   }

   VICVectAddr = 0; // Acknowledge Interrupt
}

////////////////////////////////////////////
void UART_InitWithInt(unsigned int uiBaudRate){

   // UART0
   PINSEL0 = PINSEL0 | (0x01 << 2) ;                            // ustawic pina na odbiornik uart0
	 PINSEL0 = PINSEL0 | (0x01 << 0);															// ustawic pina na nadajnik uart0
	 U0LCR  |= m8BIT_UART_WORD_LENGTH | mDIVISOR_LATCH_ACCES_BIT; // dlugosc slowa, DLAB = 1
   U0DLL   = ((15000000)/16)/uiBaudRate;                        // predkosc transmisji
   U0LCR  &= (~mDIVISOR_LATCH_ACCES_BIT);                       // DLAB = 0
   U0IER  |= mRX_DATA_AVALIABLE_INTERRUPT_ENABLE;               // ENABLE THE RECEIVE DATA AVAILABLE INTERRUPT
	 U0IER  |= mTHRE_INTERRUPT_ENABLE;														// ENABLE TRANSMITTER DATA AVAILABLE INTERRUPT

   // INT
   VICVectAddr2  = (unsigned long) UART0_Interrupt;             // set interrupt service routine address
   VICVectCntl2  = mIRQ_SLOT_ENABLE | VIC_UART0_CHANNEL_NR;     // use it for UART 0 Interrupt
   VICIntEnable |= (0x1 << VIC_UART0_CHANNEL_NR);               // Enable UART 0 Interrupt Channel
}

////////////////////////////////////////////

struct RecieverBuffer{ 
	char cData[RECIEVER_SIZE];
	unsigned char ucCharCtr;
	enum eRecieverStatus eStatus;
};

struct RecieverBuffer sRecieverBuffer;

void Reciever_PutCharacterToBuffer(char cCharacter){
	if (sRecieverBuffer.eStatus == EMPTY){
		if (sRecieverBuffer.ucCharCtr == RECIEVER_SIZE){
			sRecieverBuffer.cData[sRecieverBuffer.ucCharCtr-1] = NULL;
			sRecieverBuffer.eStatus = OVERFLOW;
		}	else if (cCharacter == TERMINATOR){
			sRecieverBuffer.cData[sRecieverBuffer.ucCharCtr] = NULL;
			sRecieverBuffer.eStatus = READY;
		}	else {
			sRecieverBuffer.cData[sRecieverBuffer.ucCharCtr] = cCharacter;
			sRecieverBuffer.ucCharCtr++;
		}
	}	
}	

enum eRecieverStatus eReciever_GetStatus(void){
	return sRecieverBuffer.eStatus;
}	

void Reciever_GetStringCopy(char * ucDestination){
	CopyString(sRecieverBuffer.cData, ucDestination);
	sRecieverBuffer.eStatus = EMPTY;
	sRecieverBuffer.ucCharCtr = 0;
}


