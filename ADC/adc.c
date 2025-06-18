#include <LPC21xx.H>
#include "adc.h"

#define ADC_RES 1023

#define VIC_ADC_CHANNEL_NR 18

#define mIRQ_SLOT_ENABLE 0x00000020

unsigned int uiADCData;

__irq void ADC_IRQ(){
	
	uiADCData = ADDR;
	uiADCData = (uiADCData >> 6) & 0x3FF; //wydobycie danych
	
	ADCR &= ~(1<<24); //stop conversion
	
	VICVectAddr = 0; // Acknowledge Interrupt
}

void ADC_Init(){
	
	PINSEL1 &= ~(3<<22);
	PINSEL1 |= (1<<22); // pin analogowy P0.27
	ADCR = (1<<0) | (1<<21); //wybieramy pin Ain0
        // interrupts
	VICIntEnable |= (0x1 << VIC_ADC_CHANNEL_NR);
	VICVectCntl3  = mIRQ_SLOT_ENABLE | VIC_ADC_CHANNEL_NR; //przerwanie ADC
	VICVectAddr3  =(unsigned long)ADC_IRQ;
	
	ADC_Start();

}

void ADC_Start(){
	
	ADCR |= (1<<24); // start konwersji
}

unsigned int ADC_GetValue() {
	unsigned int uiPosition;
	
	uiPosition = 47-uiADCData*47/1023;
	
	return uiPosition;
}
