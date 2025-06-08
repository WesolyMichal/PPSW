void CopyString(char pcSource[], char pcDestination[]);
typedef enum { DIFFERENT, EQUAL } CompResult;
int eCompareString(char pcStr1[], char pcStr2[]);
void ReplaceCharactersInString(char pcString[],char cOldChar,char cNewChar);

void UIntToHexStr (unsigned int uiValue, char pcStr[]);
enum Result {OK, ERROR};
int eHexStringToUInt(char pcStr[], unsigned int *puiValue);
void AppendUIntToString (unsigned int uiValue, char pcDestinationStr[]);
