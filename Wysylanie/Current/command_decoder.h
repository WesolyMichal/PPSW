#define MAX_TOKEN_NR 2

enum KeywordCode {CLC};

union TokenValue {
	enum KeywordCode eKeyword; 
	unsigned int uiValue; 
	char* pcString;
};

enum TokenType {KEYWORD, NUMBER, STRING};

struct Token {
	enum TokenType eType; 
	union TokenValue uValue;
};

void DecodeMsg(char *pcString);
