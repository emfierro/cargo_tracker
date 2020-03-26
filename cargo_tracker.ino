#include <EEPROM.h>

#define EEPROM_size 1024
#define maxNumberCount 5

int PIR_sensor=5;
char phoneNumberBuffer[11];
byte cntPoint=(EEPROM_size-(maxNumberCount*12))-1;
byte dataLength,EE_temp;
bool isHigh=false;
uint32_t tempTime,timer;
char txSMS[]="text to send via sms";

#define clrSR delay(20);while(Serial.available()){delay(4);Serial.read();}
void setup() {

  pinMode(11,0);
  pinMode(12,1);
  pinMode(PIR_sensor,0);
  digitalWrite(12,0);
  digitalWrite(11,1);
  digitalWrite(PIR_sensor,1);
   
  delay(200);
  
  Serial.begin(9600);


  
  uploadLog_handler();
  dataLength=0;
  EEPROM.write(cntPoint,0);



  
/*for(byte i=0;i<maxNumberCount;i++){
     
  }*/

} 

bool findOK(){
    timer=millis()+2500;
    while(timer>millis()){
        if(Serial.read()=='O'){
            while(timer>millis()&&(!Serial.available())){}
             if(Serial.read()=='K'){return true;}
          }
      
      }
      return false;
    
  }
void connfigureM590(){

    while(true){Serial.println("AT"); if(findOK()){break;}} 
    while(true){Serial.println("AT+CMGF=1"); if(findOK()){break;}}  
    clrSR;
    for(byte i=0;i<5;i++){
      Serial.println("AT+CSCS=GSM"); 
      if(findOK()){break;}
      }
  }


void sendSMS(){
  for(byte L=0;L<maxNumberCount;L++){
     
      if(EEPROM.read( EEPROM_size-((L+1)*12) )=='+'){
          getPhoneByIndex(L);
          Serial.print("AT+CMGS=");
          Serial.write(phoneNumberBuffer,11);
          Serial.write('\r');
          Serial.print(txSMS);
          Serial.write(26); 
          findOK();
          
        }
    }
  
  }

void getPhoneByIndex(byte indx){
    for(byte i=0;i<11;i++){
       phoneNumberBuffer[i]=EEPROM.read((EEPROM_size - ((1+indx)*12))+1+i);
      }
  
  }


void saveChng(){
  
        if(dataLength>((EEPROM_size-(maxNumberCount*12))-3)){while(true){}}; 
        tempTime=millis()/1000;
        dataLength++;
        EEPROM.write(dataLength*2,((tempTime>>8)|0xff));
        EEPROM.write((dataLength*2)+1,((tempTime)|0xff));
        EEPROM.write(cntPoint,dataLength);
        delay(1300);
  }


  void sensorLog_handler(){
     if(digitalRead(PIR_sensor)){
    if(!isHigh){
         isHigh=true;
        saveChng();
      }
    }else{  
      if(isHigh){
         isHigh=false;
        saveChng();
      }
      
      }
    
    }
void loop() {
sensorLog_handler();
 

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

  

void uploadLog_handler(){
     
    if(!digitalRead(11)){
        Serial.println("waiting for\"+\" to upload data");
        while(Serial.read()!='+'){delay(10);}
        byte count=EEPROM.read(cntPoint);
        uint16_t sBegin,sEnd;
            Serial.println();
            Serial.println("begin - end; (difference)");
            Serial.println("=======");
        for(byte i=0;i<count;i++){
            sBegin= EEPROM.read(i*2);
            sBegin<<=8;
            sBegin+=EEPROM.read((i*2)+1);
            i++;
            sEnd= EEPROM.read((i*2));
            sEnd<<=8;
            sEnd+=EEPROM.read((i*2)+1);
            Serial.print (String(sBegin,DEC)+ " - " + String(sEnd,DEC));
            Serial.print ("; (");
            Serial.print (String((sEnd-sBegin),DEC));
            Serial.println (")");
          }
        
            Serial.println("=======");
            while(true){};
      }
  
  }
