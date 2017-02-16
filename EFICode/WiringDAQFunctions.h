#ifndef EEPROM_FUNCTIONS
#define EEPROM_FUNCTIONS

#define MOSI 51
#define MISO 50
#define SCK 52
#define SS1 43
#define SS2 42
#define SS3 41
#define SS4 40
#define WRITEPROTECT 49

#define DENSITY 16000000

#define MAXSPEED 50000000  //50 MHz


bool ss1Writable = true;
bool ss2Writable = true;
bool ss3Writable = true;
bool ss4Writable = true;

int32_t spaceLeft[4] = {DENSITY, DENSITY, DENSITY, DENSITY}; //16MB
int storageIndex = 0;


SPISettings testSettings = SPISettings(13000000, MSBFIRST, SPI_MODE0);


int memWrite(char data[]);
int memWriteInt(int data);
int memWriteLong(long data);
int memRead(char arr[],int length);
int memWriteInt(int* data); 
int memWriteLong(long* data);
int whichEEPROM();
void full(int fullSlavePin);

//page number for table of commands is 67 in spec

#endif