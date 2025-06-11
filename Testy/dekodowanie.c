#include "lancuchy.h"
#include "konwersje.h"
#include "dekodowanie.h"

#define NULL '\0'
#define MAX_TOKEN_NR 3
#define MAX_KEYWORD_STRING_LTH 10
#define MAX_KEYWORD_NR 3
#define DELIMITER_CHAR ' '

struct Token asToken[MAX_TOKEN_NR];

unsigned char ucTokenNr;

struct Keyword {
	enum KeywordCode eCode;
	char cString[MAX_KEYWORD_STRING_LTH + 1];
};
struct Keyword asKeywordList[MAX_KEYWORD_NR]={
	{RST,"reset"},
	{LD, "load" },
	{ST, "store"}
};

enum State {TOKEN, DELIMITER};
enum State eState = TOKEN;

unsigned char ucFindTokensInString(char *pcString) {

	enum State eState = DELIMITER;
	unsigned char ucCharCounter;
	unsigned char ucCurrentChar;
	ucTokenNr = 0;

	for(ucCharCounter = 0; ; ucCharCounter++) {
		ucCurrentChar = pcString[ucCharCounter];
		switch(eState) {
		case DELIMITER:
			if(NULL == ucCurrentChar) {
				return ucTokenNr;
			} else if(DELIMITER_CHAR == ucCurrentChar) {}
			else {
				eState = TOKEN;
				asToken[ucTokenNr].uValue.pcString = pcString + ucCharCounter;
				ucTokenNr++;
			}
			break;
		case TOKEN:
			if(MAX_TOKEN_NR <= ucTokenNr) {
				return ucTokenNr;
			}
			else if(NULL == ucCurrentChar) {
				return ucTokenNr;
			}
			else if(DELIMITER_CHAR == ucCurrentChar) {
				eState = DELIMITER;
			}
			else {
				eState = TOKEN;
			}
			break;
		}
	}
}

enum Result eStringToKeyword (char pcStr[],enum KeywordCode *peKeywordCode) {
	
	unsigned char ucKeywordCounter;
	
	for (ucKeywordCounter = 0; ucKeywordCounter < MAX_KEYWORD_NR; ucKeywordCounter++) {
		if (eCompareString(asKeywordList[ucKeywordCounter].cString, pcStr) == EQUAL) {
			*peKeywordCode = asKeywordList[ucKeywordCounter].eCode;
			return OK;
		}
	}
	return ERROR;
}

void DecodeTokens(void){

  unsigned char ucTokenCounter;
  enum KeywordCode eDecodedKeyword;
  unsigned int uiDecodedNumber;
  struct Token * psCurrentToken;
	
  for(ucTokenCounter = 0; ucTokenNr > ucTokenCounter; ucTokenCounter++) {
    psCurrentToken = &asToken[ucTokenCounter];
		if(OK == eStringToKeyword(psCurrentToken->uValue.pcString, &eDecodedKeyword)) {
			 
			 psCurrentToken->uValue.eKeyword = eDecodedKeyword;
			 psCurrentToken->eType = KEYWORD;
		}
		else if(OK == eHexStringToUInt(psCurrentToken->uValue.pcString, &uiDecodedNumber)) {
			 
			 psCurrentToken->uValue.uiValue = uiDecodedNumber;
			 psCurrentToken->eType = NUMBER;
		}
		else {
			 psCurrentToken->eType = STRING;
		}
  }
}


void DecodeMsg(char *pcString) {
	ucTokenNr = ucFindTokensInString(pcString);
	ReplaceCharactersInString(pcString, DELIMITER_CHAR, NULL);
	DecodeTokens();
}


