#include <LPC21xx.H>
#include "keyboard.h"

#define BUT0_bm (1 << 4)
#define BUT1_bm (1 << 6)
#define BUT2_bm (1 << 5)
#define BUT3_bm (1 << 7)

void KeyboardInit(){
	IO0DIR &= ~(BUT0_bm & BUT1_bm & BUT2_bm & BUT3_bm);
}

int eKeyboardState(){
	if (0 == (IO0PIN & BUT0_bm)){
		return BUTTON_0;
	}	else if (0 == (IO0PIN & BUT1_bm)){
		return BUTTON_1;
	} else if (0 == (IO0PIN & BUT2_bm)){
		return BUTTON_2;
	} else if (0 == (IO0PIN & BUT3_bm)){
		return BUTTON_3;
	}
	return RELEASED;
}
