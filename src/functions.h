/* Header file to keep the main file readable*/
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <Arduino.h>
#include <EEPROM.h>

#define DATA_SIZE 1012  // more than 1000 characters

void ReceiveDataFromPC();  //function to receive data from PC
void SendDataToPC();       //function to send data back to PC
void BitTransferSpeed(const char *PtrtoString);  //Calculating the transmission speed of bits
void EraseEEPROM() ; //Clearing EEPROM before uploading the data

#endif

