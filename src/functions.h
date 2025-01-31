
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <Arduino.h>
#include <EEPROM.h>

#define DATA_SIZE 1012  

void ReceiveDataFromPC(); 
void SendDataToPC();       
void BitTransferSpeed(const char *PtrtoString);  
void EraseEEPROM() ; 

#endif

