#include "konwersje.h"

#define NULL '\0'
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

enum Result eHexStringToUInt(char pcStr[],unsigned int *puiValue)
{
    unsigned char ucCharacterCounter;
    unsigned char ucCurrentCharacter;

    *puiValue = 0;
    if((pcStr[0] != '0') || (pcStr[1] != 'x') || (pcStr[2] == NULL))
    {
        return ERROR;
    }
    for(ucCharacterCounter = 2; pcStr[ucCharacterCounter] !=NULL ; ucCharacterCounter++)
    {
        ucCurrentCharacter = pcStr[ucCharacterCounter];
        if(ucCurrentCharacter == NULL)
        {
            return OK;
        }
        else if(ucCharacterCounter == 6)
        {
            return ERROR;
        }
        *puiValue = *puiValue << 4;
        if((ucCurrentCharacter <= '9') && (ucCurrentCharacter >= '0'))
        {
            *puiValue = (*puiValue) | (ucCurrentCharacter - '0');
        }
        else if((ucCurrentCharacter <= 'F') && (ucCurrentCharacter >= 'A'))
        {
            *puiValue = (*puiValue) | (ucCurrentCharacter - 'A' + 10);
        }
        else
        {
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


