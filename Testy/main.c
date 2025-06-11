#include "string.h"
#include "stdio.h"

#include "lancuchy.h"
#include "konwersje.h"
#include "dekodowanie.h"

#define MAX_TOKEN_NR 3 

void TestOf_CopyString(void){
	char cOriginalStr[] = "Test kopiowania";
  char cCopiedstr[25];

  printf("CopyString\n\n ");
  printf("Test 1 - ");
  // Sprawdzenie czy funkcja poprawnie kopiuje
  CopyString(cOriginalStr, cCopiedstr);
  if (strcmp(cOriginalStr, cCopiedstr) == 0) {
		printf("OK\n\n");
	} else {
		printf("Error\n\n");
	}
}	

void TestOf_eCompareString(void) {
  char cStringNormal[] = "Testowy string 0x01";
  char cStringShorter[] = "Testowy string";
  char cStringLonger[] = "Testowy string 0x01 dlugi";
  char cDifferentString[] = "Testawy string 0x01";
  

  printf("eCompareString\n\n ");
  printf("Test 1 - ");
  // Sprawdzenie czy funkcja poprawnie dziala przy tej samej dlugosci lancuchow
  if (eCompareString(cStringNormal, cStringNormal) == EQUAL) printf("OK\n"); else printf("Error\n");
    
  printf("Test 2 - ");
  // Sprawdzenie czy funkcja poprawnie dziala przy jednym dluzszym lancuchu
  if (eCompareString(cStringNormal, cStringLonger) == DIFFERENT) printf("OK\n"); else printf("Error\n");
    
  printf("Test 3 - ");
  // Sprawdzenie czy funkcja poprawnie dziala przy jednym krotszym lancuchu
  if (eCompareString(cStringNormal, cStringShorter) == DIFFERENT) printf("OK\n"); else printf("Error\n");
    
  printf("Test 4 - ");
  // Sprawdzenie czy funkcja poprawnie dziala przy bledzie w postaci innego znaku
  if (strcmp(cStringNormal, cDifferentString) != 0 && eCompareString(cStringNormal, cDifferentString) == DIFFERENT)
  printf("OK\n\n"); else printf("Error\n\n");
}

void TestOf_AppendString(void) {
  char cDestinationStr1[] = "test ";
  char cDestinationStr2[] = "";
  char cDestinationStr3[] = "test";
  char cSourceStr1[] = "dzialania";
  char cSourceStr2[] = "";
  char cSourceStr3[] = "dzialania";
  

  printf("AppendString\n\n ");
  printf("Test 1 - ");
  // Sprawdzenie czy funkcja poprawnie dodaje niepusty lancuch do niepustego lancucha
  AppendString(cSourceStr1, cDestinationStr1);
  if (strcmp(cDestinationStr1, "test dzialania") == 0){
		printf("OK\n");
	} else { 
		printf("Error\n");
	}
  printf("Test 2 - ");
  // Sprawdzenie czy funkcja poprawnie dodaje pusty lancuch do niepustego lancucha
  AppendString(cSourceStr2,cDestinationStr3);
  if (strcmp(cDestinationStr3, "test") == 0) {
		printf("OK\n"); 
	} else { 
		printf("Error\n");
	}
  printf("Test 3 - ");
  // Sprawdzenie czy funkcja poprawnie dodaje niepusty lancuch do pustego lancucha
  AppendString(cSourceStr3, cDestinationStr2);
  if (strcmp(cDestinationStr2, "dzialania") == 0) {
		printf("OK\n\n");
	} else { 
		printf("Error\n\n");
	}
}

void TestOf_ReplaceCharactersInString(void) {
  char cOldChar = 't';
  char cNewChar = 'l';
  char cNewString[] = "test stringu";

  printf("ReplaceCharactersInString\n\n ");
  printf("Test 1 - ");
  // Sprawdzenie czy funkcja poprawnie zamienia znak w lancuchu
  ReplaceCharactersInString(cNewString, cOldChar, cNewChar);
  if (strcmp(cNewString, "lesl slringu") == 0){
		printf("OK\n\n"); 
	} else {
		printf("Error\n\n");
	}
}

void TestOf_UIntToHexStr(void) {
  char cString[15];

  printf("UIntToHexStr\n\n ");
  printf("Test 1 - ");
  // Sprawdzenie czy funkcja poprawnie zamienia liczby 2479 (0x09AF) na lanuch znakowy, sprawdzenie koncowych przedzialow
  UIntToHexStr(0x09AF,cString);
  if (strcmp(cString, "0x000009AF") == 0) {
		printf("OK\n\n"); 
	} else {
		printf("Error\n\n");
	}
}

void TestOf_eHexStringToUInt(void) {
  char cWrongFormat1[] = "test";
  char cWrongFormat2[] = "0x";
  char cWrongFormat3[] = "0x12345";
  char cGoodFormat[] = "0xFDE8";
  unsigned int uiResult;

  printf("eHexStringToUInt\n\n ");
  printf("Test 1 - ");
  // Sprawdzenie czy funkcja poprawnie dziala dla niepoprawnych danych wejsciowych
  if (eHexStringToUInt(cWrongFormat1,&uiResult) == ERROR) {
		printf("OK\n"); 
	} else {
		printf("Error\n");
	}
    
  printf("Test 2 - ");
  // Sprawdzenie czy funkcja poprawnie dziala dla zbyt krotkiego lancucha wejsciowego
  if (eHexStringToUInt(cWrongFormat2,&uiResult) == ERROR) {
		printf("OK\n"); 
	} else {
		printf("Error\n");
	}

  printf("Test 3 - ");
  // Sprawdzenie czy funkcja poprawnie dziala dla zbyt dlugiego lanucha wejsciowego
  if (eHexStringToUInt(cWrongFormat3,&uiResult) == ERROR) {
		printf("OK\n"); 
	} else {
		printf("Error\n");
	}
 
  printf("Test 4 - ");
  // Sprawdzenie czy funkcja poprawnie konwertuje liczby na lanuch znakowy
  if ((eHexStringToUInt(cGoodFormat,&uiResult) == OK) && uiResult == 65000) {
		printf("OK\n\n"); 
	} else {
		printf("Error\n\n");
	}
}

void TestOf_AppendUIntToString(void) {
  char cDestinationStr1[15] = "Test";
  char cDestinationStr2[15] = "";
  unsigned int uiValue = 1;

  printf("AppendUIntToString\n\n ");
  printf("Test 1 - ");
  // Sprawdzenie czy funkcja poprawnie dodaje liczby do konca niepustego lancucha znakowego
  AppendUIntToString(uiValue, cDestinationStr1);
  if (strcmp(cDestinationStr1, "Test0x00000001") == 0) {
		printf("OK\n"); 
	} else {
		printf("Error\n");
	}
  
  printf("Test 2 - ");
  // Sprawdzenie czy funkcja poprawnie dodaje liczby do konca pustego lancucha znakowego
  AppendUIntToString(uiValue, cDestinationStr2);
  if (strcmp(cDestinationStr2, "0x00000001") == 0) {
		printf("OK\n\n"); 
	} else {
		printf("Error\n\n");
	}
}

extern struct Token asToken[MAX_TOKEN_NR];
extern unsigned char ucTokenNr;

void TestOf_ucFindTokensInString(void) {
	
  char cString1[] = "test of this";
  char cString2[] = "     ";
  char cString3[] = " test of this";
  char cString4[] = "test  of this";
  
  printf("ucFindTokensInString\n\n ");
  printf("Test 1 - ");
  // Sprawdzenie czy funkcja poprawnie zlicza i wyszukuje delimitery
  ucTokenNr = ucFindTokensInString(cString1);
  if (ucTokenNr == 3 && (asToken[0].uValue.pcString == &cString1[0]) && (asToken[1].uValue.pcString == &cString1[5]) && (asToken[2].uValue.pcString == &cString1[8])) {
		printf("OK\n"); 
	} else {
		printf("Error\n");
	}
  
  printf("Test 2 - ");
  // Sprawdzenie czy funkcja dziala poprawnie dla lancucha znakowego skladajacego sie z samych delimiterow
  ucTokenNr = ucFindTokensInString(cString2);
  if (ucTokenNr == 0) {
		printf("OK\n"); 
	} else {
		printf("Error\n");
	}  
    
  printf("Test 3 - ");
  // Sprawdzenie czy funkcja dziala poprawnie dla delimiterem przed lancuchem znakowym
  ucTokenNr = ucFindTokensInString(cString3);
  if (ucTokenNr == 3 && (asToken[0].uValue.pcString == &cString3[1]) && (asToken[1].uValue.pcString == &cString3[6]) && (asToken[2].uValue.pcString == &cString3[9])) {
		printf("OK\n"); 
	} else {
		printf("Error\n");
	}  
  printf("Test 4 - ");
  // Sprawdzenie czy funkcja dziala poprawnie dla dwoch delimiterow miedzy dwoma tokenami
  ucTokenNr = ucFindTokensInString(cString4);
  if (ucTokenNr == 3 && (asToken[0].uValue.pcString == &cString4[0]) && (asToken[1].uValue.pcString == &cString4[6]) && (asToken[2].uValue.pcString == &cString4[9])) {
		printf("OK\n\n"); 
	} else {
		printf("Error\n\n");
	}
}

void TestOf_eStringToKeyword(void) {
  char cString1[] = "load";
  char cString2[] = "loooaddd";
  enum KeywordCode eTest;

  printf("eStringToKeyword\n\n ");
  printf("Test 1 - ");
  // Sprawdzenie czy funkcja poprawnie zamienia slowa kluczowe na odpowiadajaca im wartosc enum
  if ((eStringToKeyword(cString1,&eTest) == OK) && eTest == LD) {
		printf("OK\n"); 
	} else {
		printf("Error\n");
	}
    
  printf("Test 2 - ");
  // Sprawdzenie czy funkcja dziala poprawnie przy slowie innym niz slowo kluczowe
  if (eStringToKeyword(cString2,&eTest) == ERROR) {
		printf("OK\n\n"); 
	} else {
		printf("Error\n\n");
	}
}

void TestOf_DecodeTokens(void) {
  char cString[] = "test reset 0x10";
  ucTokenNr = ucFindTokensInString(cString);
  ReplaceCharactersInString(cString, ' ', '\0');
  DecodeTokens();
  
  printf("DecodeTokens\n\n");
  printf("Test 1 - ");
  // Sprawdzenie czy funkcja dziala poprawnie dla wejsciowego lancucha znakowego
  if ((asToken[0].eType == STRING) && (asToken[0].uValue.pcString == cString)) {
		printf("OK\n"); 
	} else {
		printf("Error\n");
	}
    
  printf("Test 2 - ");
  // Sprawdzenie czy funkcja dziala poprawnie dla wejsciowego slowa kluczowego
  if ((asToken[1].eType == KEYWORD) && (asToken[1].uValue.eKeyword == RST)) {
		printf("OK\n"); 
	} else {
		printf("Error\n");
	}
    
  printf("Test 3 - ");
  // Sprawdzenie czy funkcja dziala poprawnie dla wejsciowej liczby
  if ((asToken[2].eType == NUMBER) && (asToken[2].uValue.uiValue == 0x10)) {
		printf("OK\n\n"); 
	} else {
		printf("Error\n\n");
	}
}

void TestOf_DecodeMsg(void) {
  char cStr[] = "test reset 0x10";

  printf("DecodeMsg\n\n ");
  printf("Test 1 - ");
  // Sprawdzenie czy funkcja dziala poprawnie dla wejsciowego lancucha znakowego (pelnej wiadomosci)
  DecodeMsg(cStr);
  if ((ucTokenNr == 3) && (asToken[0].eType == STRING) && (&cStr[0] == asToken[0].uValue.pcString) && (asToken[1].eType == KEYWORD) && (asToken[1].uValue.eKeyword == RST) && (asToken[2].eType == NUMBER) && (asToken[2].uValue.uiValue == 0x10)) {
		printf("OK\n"); 
	} else {
		printf("Error\n");
	}
}


int main(void){
	TestOf_CopyString();
	TestOf_eCompareString();
	TestOf_AppendString();
	TestOf_ReplaceCharactersInString();
	TestOf_UIntToHexStr();
	TestOf_eHexStringToUInt();
	TestOf_AppendUIntToString();
	TestOf_ucFindTokensInString();
	TestOf_eStringToKeyword();
	TestOf_DecodeTokens();
	TestOf_DecodeMsg();
	return 0;
}	
