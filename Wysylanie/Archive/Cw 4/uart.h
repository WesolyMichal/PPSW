#define RECIEVER_SIZE 12

void UART_InitWithInt(unsigned int uiBaudRate);

enum eRecieverStatus {EMPTY, READY, OVERFLOW};
void Reciever_PutCharacterToBuffer(char cCharacter);
enum eRecieverStatus eReciever_GetStatus(void);
void Reciever_GetStringCopy(char * ucDestination);

enum eTransmiterStatus {FREE, BUSY};

void Transmiter_SendString(char cString[]);
enum eTransmiterStatus Transmiter_GetStatus(void);
