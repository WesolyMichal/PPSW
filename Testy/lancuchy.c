#include "lancuchy.h"
#define NULL ('\0')

void CopyString(char pcSource[], char pcDestination[]){
	
	unsigned char ucCharCounter;
	
	for(ucCharCounter=0 ; !(NULL == pcSource[ucCharCounter]) ; ucCharCounter++) {
		pcDestination[ucCharCounter] = pcSource[ucCharCounter];
	}	
	pcDestination[ucCharCounter] = NULL;
}

int eCompareString(char pcStr1[], char pcStr2[]) {
    
	unsigned char ucCharCounter;
    
	for (ucCharCounter = 0; !(NULL==pcStr1[ucCharCounter]) || !(NULL==pcStr2[ucCharCounter]); ucCharCounter++) {
		if (!(pcStr1[ucCharCounter]==pcStr2[ucCharCounter])) {
			return DIFFERENT;
		}
	}
  return EQUAL;
}


void AppendString(char pcSourceStr[],char pcDestinationStr[]){
	
	unsigned char ucSourceCharCounter;
	
	for (ucSourceCharCounter=0; !(NULL==pcDestinationStr[ucSourceCharCounter]); ucSourceCharCounter++) {};
		
	CopyString(pcSourceStr, pcDestinationStr+ucSourceCharCounter);
}


void ReplaceCharactersInString(char pcString[],char cOldChar,char cNewChar) {
	
	unsigned char ucCharCounter;
	
	for (ucCharCounter=0; !(NULL==pcString[ucCharCounter]); ucCharCounter++) {
		if (pcString[ucCharCounter] == cOldChar) {
			pcString[ucCharCounter] = cNewChar;
		}	
	}	
}	
