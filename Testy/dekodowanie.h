enum TokenType {KEYWORD, NUMBER, STRING};

enum KeywordCode {LD, ST, RST};

union TokenValue {
	enum KeywordCode eKeyword; 
	unsigned int uiValue; 
	char* pcString;
};

struct Token {
	enum TokenType eType; 
	union TokenValue uValue;
};

unsigned char ucFindTokensInString(char *pcString);
enum Result eStringToKeyword (char pcStr[],enum KeywordCode *peKeywordCode);
void DecodeTokens(void);
void DecodeMsg(char *pcString);
