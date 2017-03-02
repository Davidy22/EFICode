#include <SPI.h>
#include "WiringDAQFunctions.h"



using namespace std;


bool ss1Writable = false;
bool ss2Writable = false;
bool ss3Writable = true;
bool ss4Writable = true;

int32_t spaceLeft[4] = {DENSITY, DENSITY, DENSITY, DENSITY}; //16MB
int storageIndex = 0;

// read instruction 0x13


SPISettings testSettings = SPISettings(13000000, MSBFIRST, SPI_MODE0);

//*****if the write was successful, but carried over to next chip do not send anything
//only return 1 if there is not more memory availibe to write to
//arduino compiler does not support exceptions

//not sure how to make it one continuous block of memory
//not sure when to return 2
//how will we know what we are reading
// if char or c string, etc




/*
  int memWrite(address, char[]);
  Writes c string char to memory address address. Returns 0 if successful.
  Returns 1 if attempting to write past the end of memory.
  Returns 2 if EEPROM fails to ack, potential hardware failure.
*/
int memWrite(char data[]) {
  int SS = whichEEPROM();
  if (SS == -1) {
    return 1;
  }
  digitalWrite(SS, LOW);
  shiftOut(MOSI, SCK, MSBFIRST, WRITE_ENABLE_BYTE);
  SPI.beginTransaction(testSettings);
  int lengthOfCString = sizeof(data);
  for (int i = 0; i < sizeof(data); i++) {
    shiftOut(MOSI, SCK, MSBFIRST, data[i]);
    //decement array
    if(spaceLeft[storageIndex] > 0){
      spaceLeft[storageIndex]--;
    }
    else if (spaceLeft[storageIndex] == 0){
      storageIndex++;
      full(SS);
      SS = whichEEPROM();
      if(SS ==-1){
        return 1;
      }
    }
  }
  //possible access through memory address
  shiftOut(MOSI, SCK, MSBFIRST, WRITE_DISABLE_BYTE);
  digitalWrite(SS, HIGH);
  return 0;

}
/*
  int memWriteInt(address, int);
  Writes 1 byte integer value int to memory address address.
  Returns 0 if successful. Returns 1 if attempting to write past the end of memory.
  Returns 2 if EEPROM fails to act, potential hardware failure.
*/
int memWriteInt(int data) {
  int SS = whichEEPROM();
  if (SS == -1) {
    return 1;
  }
  readyToWrite(SS);
  digitalWrite(SS, LOW);
  shiftOut(MOSI, SCK, MSBFIRST, WRITE_ENABLE_BYTE);
  digitalWrite(SS, HIGH);
  
  SPI.beginTransaction(testSettings); //
  byte bytedata[4];
  digitalWrite(SS, LOW);
  shiftOut(MOSI, SCK, MSBFIRST, 0x12);
  shiftOut(MOSI, SCK, MSBFIRST, 0x00000000);
  bytedata[0] = (byte) (data & 0xFF);
  bytedata[1] = (byte) ((data >> 8) & 0xFF);
  bytedata[2] = (byte) ((data >> 8) & 0xFF);
  bytedata[3] = (byte) ((data >> 8) & 0xFF);
  for (int i = 0; i < 4; i++) {
    shiftOut(MOSI, SCK, MSBFIRST, bytedata[i]);
    //decement array
    if(spaceLeft[storageIndex] > 0){
      spaceLeft[storageIndex]--;
    }
    else if (spaceLeft[storageIndex] == 0){
      storageIndex++;
      full(SS);
      SS = whichEEPROM();
      if(SS ==-1){
        return 1;
      }
    }
  }
  digitalWrite(SS, HIGH);
  //possible access through memory address
  digitalWrite(SS, LOW); //activate write disable
  shiftOut(MOSI, SCK, MSBFIRST, WRITE_DISABLE_BYTE);
  digitalWrite(SS, HIGH);
  return 0;
}


/*
  int memWriteLong(address, long);
  Writes 4 byte integer value long to memory address address.
  Returns 0 if successful. Returns 1 if attempting to write past the end of memory.
  Returns 2 if EEPROM fails to ack, potential hardware failure.
*/
int memWriteLong(long data) { // 4 bytes
  int SS = whichEEPROM();
  if (SS == -1) {
    return 1;
  }
  digitalWrite(SS, LOW);
  shiftOut(MOSI, SCK, MSBFIRST, WRITE_ENABLE_BYTE);
  SPI.beginTransaction(testSettings);
  byte bytedata[4];
  bytedata[0] = (byte) (data & 0xFF);
  bytedata[1] = (byte) ((data >> 8) & 0xFF);
  bytedata[2] = (byte) ((data >> 8) & 0xFF);
  bytedata[3] = (byte) ((data >> 8) & 0xFF);
  for (int i = 0; i < 4; i++) {
    shiftOut(MOSI, SCK, MSBFIRST, bytedata[i]);
    
    //decement array
    if(spaceLeft[storageIndex] > 0){
      spaceLeft[storageIndex]--;
    }
    else if (spaceLeft[storageIndex] == 0){
      storageIndex++;
      full(SS);
      SS = whichEEPROM();
      if(SS ==-1){
        return 1;
      }}}
  //possible access through memory address
  shiftOut(MOSI, SCK, MSBFIRST, WRITE_DISABLE_BYTE);
  digitalWrite(SS, HIGH);
  return 0;

}
/*
  int memRead(address, char[], length);
  Read length characters into character array char[].
  Returns 0 if successful. Returns 1 if attempting to read past the end of memory.
  Returns 2 if EEPROM fails to ack, potential hardware failure.
  Will not check that length is greater than allocated length of char[].
*/
int memRead(char arr[], int length, unsigned long address) {

  int SS = whichEEPROM();
  if (SS == -1) {
    return 1;
  }
  digitalWrite(SS, LOW);
  shiftOut(MOSI, SCK, MSBFIRST, 0x13);
  shiftOut(MOSI, SCK, MSBFIRST, address);
  
  SPI.beginTransaction(testSettings);
  for (int i = 0; i < length; i++) {
    arr[i] = shiftIn(MISO, SCK, MSBFIRST);
  }
  digitalWrite(SS, HIGH);
  return 0;
}
/*
  int memWriteInt(address, *int);
  Read 1 byte integer value into value at integer pointer int.
  Returns 0 if successful. Returns 1 if attempting to read past the end of memory.
  Returns 2 if EEPROM fails to ack, potential hardware failure.
*/
int memWriteInt(int* data) {
  byte intByte;

}

/*
  int memWriteLong(address, *long);
  Read 4 byte integer value into value at long pointer long.
  Returns 0 if successful. Returns 1 if attempting to read past the end of memory.
  Returns 2 if EEPROM fails to ack, potential hardware failure.
*/
int memWriteLong(long* data) {

}

int whichEEPROM() { //determines which eeprom is availible to write
  if (ss1Writable) { //returns -1 if there are no more available ones --> cause error leading to catch condition
    return SS1;
  }
  else if (ss2Writable) {
    return SS2;
  }
  else if (ss3Writable) {
    return SS3;
  }
  else if (ss4Writable) {
    return SS4;
  }
  else return -1;
}

void full(int fullSlavePin) {
  switch (fullSlavePin) {
    case SS1:
      ss1Writable = false;
      break;
    case SS2:
      ss2Writable = false;
      break;
    case SS3:
      ss3Writable = false;
      break;
    case SS4:
      ss4Writable = false;
      digitalWrite(WRITEPROTECT, HIGH);
      break;
    default:
      break;
  }
}


void readyToWrite(int SS) {
  digitalWrite(SS, LOW);
  shiftOut(MOSI, SCK, MSBFIRST, 0x05);
  byte statusReg = shiftIn(MISO, SCK, MSBFIRST);
  byte b = statusReg; // & B00000001;
  Serial.println(b);
  while (true){
      delay(20);
      b = shiftIn(MISO, SCK, MSBFIRST); //& B00000001;
      Serial.println(b);
  }
  digitalWrite(SS, HIGH);
}

