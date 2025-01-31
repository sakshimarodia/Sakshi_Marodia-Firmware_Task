#include <functions.h>

void setup() {
    Serial.begin(2400); 
    EraseEEPROM();
}


void loop() {
    ReceiveDataFromPC(); 
    delay(2000);       
    SendDataToPC();    
    delay(5000);        
}
