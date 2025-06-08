#define NULL ('\0')
#include "string_op.h"

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

////////////////////////////////////////////////////////

#define TETRAD_bm 0xF

void UIntToHexStr (unsigned int uiValue, char pcStr[]) {
    
	unsigned char ucNibbleCounter;
  unsigned char ucCurrentNibble;

  pcStr[0] = '0';
  pcStr[1] = 'x';

  for (ucNibbleCounter = 0; ucNibbleCounter < 8; ucNibbleCounter++) {
    
		ucCurrentNibble = (uiValue >> (ucNibbleCounter * 4)) & TETRAD_bm;
		
		if (ucCurrentNibble <= 9){
			
			pcStr[9 - ucNibbleCounter] = ucCurrentNibble + '0';
			
		}	else {
			
			pcStr[9 - ucNibbleCounter] = ucCurrentNibble + 'A' - 10;
			
		}	
  }
  pcStr[10] = NULL;
}	


int eHexStringToUInt(char pcStr[], unsigned int *puiValue){
	
	unsigned char ucDigitCounter;
	unsigned char ucHexDigit;
	
	if (!(pcStr[0] == '0') || !(pcStr[1] == 'x') || (pcStr[2] == NULL)) {
	    return ERROR;
	}
	
		*puiValue = 0;
	
	for (ucDigitCounter=2; !(pcStr[ucDigitCounter] == NULL); ucDigitCounter++) {
		
		ucHexDigit = pcStr[ucDigitCounter];
		*puiValue = (*puiValue << 4);
		
		if ((ucHexDigit >= '0') && (ucHexDigit <= '9')){
		
			*puiValue |= ( ucHexDigit - '0' );
		
		}	else if ((ucHexDigit >= 'A') && (ucHexDigit <= 'F')) {
		
			*puiValue |= ( ucHexDigit - ('A' - 10) );
		
		}	else {
			*puiValue=NULL;
			return ERROR;
		}
		
	}
	
	return OK;
}	

void AppendUIntToString (unsigned int uiValue, char pcDestinationStr[]){
	
	char ucDestEnd;
	
	for (ucDestEnd=0; !(pcDestinationStr[ucDestEnd] == NULL); ucDestEnd++) {};
		
	UIntToHexStr (uiValue, pcDestinationStr+ucDestEnd);
}	
