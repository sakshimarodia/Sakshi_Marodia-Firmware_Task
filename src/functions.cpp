#include <functions.h>

/*Variable Definitions*/
unsigned long DataTransmissionStartTime, DataTransmissionCurrentTime, DataTransmissionLastUpdateTime;
volatile unsigned long BitCounter = 0;
float TotalDurationofTransmission, BitsperSecond;
uint8_t ui8ReceivedByte, ui8StoredByte;

void ReceiveDataFromPC() 
{
    Serial.println("\nSend Data from PC.....");

    DataTransmissionStartTime = millis();
    DataTransmissionLastUpdateTime = DataTransmissionStartTime;
    BitCounter = 0;

    for (int i = 0; i < DATA_SIZE; i++) 
    {
        while (!Serial.available());
        ui8ReceivedByte = Serial.read();

        if (EEPROM.read(i) != ui8ReceivedByte) 
        {
            EEPROM.write(i, ui8ReceivedByte);
        }

        BitCounter += 8;
        BitTransmissionSpeed("Data Transmission Speed from PC to EEPROM in bits per second: ");
    }

    Serial.println("\n***Data received from PC and stored in EEPROM successfully.***");
}


void SendDataToPC() 
{
    Serial.println("\nSending stored data from EEPROM back to PC...\n");

    DataTransmissionStartTime = millis();
    DataTransmissionLastUpdateTime = DataTransmissionStartTime;
    BitCounter = 0;

    char ReceivedText[DATA_SIZE + 1];  
    memset(ReceivedText, 0, sizeof(ReceivedText));  

    for (int i = 0; i < DATA_SIZE; i++) 
    {
        ui8StoredByte = EEPROM.read(i);
        Serial.write(ui8StoredByte);
        ReceivedText[i] = (char)ui8StoredByte;

        BitCounter += 8;
        BitTransmissionSpeed("Data Transmission Speed from EEPROM to PC in bits per second: ");
    }
    Serial.println("\n***Data transmitted back to PC successfully.***\n");
    Serial.println("\nBelow Text is received back in PC from EEPROM.\n");
    Serial.println(ReceivedText);
    
}


void BitTransmissionSpeed(const char *ptrtostring) 
{
    DataTransmissionCurrentTime = millis();
    
    if (DataTransmissionCurrentTime - DataTransmissionLastUpdateTime >= 1000) 
    { 
        TotalDurationofTransmission = (DataTransmissionCurrentTime - DataTransmissionLastUpdateTime) / 1000.0; //converting ms to seconds
        BitsperSecond = BitCounter / TotalDurationofTransmission; //calculating bits per second
        
        Serial.print("\n");
        Serial.print(ptrtostring);
        Serial.print(" ");
        Serial.print(BitsperSecond, 2);
        Serial.println(" bps\n");  

        DataTransmissionLastUpdateTime = DataTransmissionCurrentTime;
        BitCounter = 0; 
    }
}

void EraseEEPROM() 
{
    Serial.println("Please wait, EEPROM is getting erased.");
    for (int i = 0; i < DATA_SIZE; i++) 
    {
        EEPROM.write(i, 0x00);
    }
    Serial.println("EEPROM Erased."); //to avoid missing data
}
