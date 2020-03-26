#include <EEPROM.h>

#define EEPROM_size=1024
#define maxNumberCount=5;


char phoneNumberBuffer[11];


void setup() {

  pinMode(11,0);
  pinMode(12,1);
  digitalWrite(12,0);
  digitalWrite(11,1);
   
  delay(200);
  
  Serial.begin(9600);
  uploadLog_handler();
/*for(byte i=0;i<maxNumberCount;i++){
     
  }*/

} 

void uploadLog_handler(){
    if(!digitalRead(11)){
        Serial.println("waiting for\"+\" to upload data");
        while(Serial.read()!='+'){delay(10);}
        
      }
  
  }

void loop() {
  

}
bool readPhoneNumber(byte indx){
    memset(phoneNumberBuffer,'0',11);
    if(EEPROM.read(EEPROM_size-(indx*12))=='+'){
        for(byte i=0;i<11;i++){
            phoneNumberBuffer[i]=EEPROM.read( (EEPROM_size-(indx*12))+1+i );
            return true;
          }
      }else{
            return false;
        }
  }
