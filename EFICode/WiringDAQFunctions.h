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
#define WRITE_ENABLE_BYTE 0x06
#define WRITE_DISABLE_BYTE 0x04

#define DENSITY 16000000

#define MAXSPEED 108000000  //108 MHz



int memWrite(char data[]);
int memWriteInt(int data);
int memWriteLong(long data);
int memRead(char arr[],int length, unsigned long address);
int memWriteInt(int* data); 
int memWriteLong(long* data);
int whichEEPROM();
void full(int fullSlavePin);
void readyToWrite(int SS);

//page number for table of commands is 67 in spec

#endif
