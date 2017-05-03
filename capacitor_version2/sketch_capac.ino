 //Krishna Mooroogen
 //Wednesday 6th June 2012
 //Capacitance readout for liquid level sensor MINIclean

#include "stdio.h"
#include "pins_arduino.h"

int UTI_PIN = 5; //defining UTI output to Arduino input pin
int CREF = 180;  //defining the reference capacitor value not yet

void setup()
{
  Serial.begin(9600); //set serial communication 
  pinMode(UTI_PIN, INPUT); //set pin mode
}


void loop()
{ 
  float cap; 
  

   if(ReadUTI(UTI_PIN, &cap, CREF)) {
	Serial.print("Capacitance:");
	Serial.print(cap,DEC);
	Serial.print("\t"); //interface for outputting value
	
}
    else {
	Serial.print("Not Found");
    }
    Serial.print("\n");
   delay(1000);
}


int ReadUTI(uint8_t pin, float *cap,int CREF) 
{ 
   int state = HIGH; 
   int i;
   int startindex=0; 
   uint8_t bit = digitalPinToBitMask(pin); 
   uint8_t port = digitalPinToPort(pin); 
   uint8_t stateMask = (state ? bit : 0); 
   unsigned long width[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //define array for cycles, 4 periods in each so need at least 8 
   float tOff=0;
   float tref=0;
   float tx=0; //define periods 
   long firsthigh=0;
   long firstlow=0;
   double time1=0;
   double time2=0;
   double time=0;   
   //while ( (*portInputRegister(port) & bit) != stateMask); 
   
   for(i=0;i<16;i=i+2) { 
     while ( (*portInputRegister(port) & bit) == stateMask) { //take time when signal is high
        firsthigh=micros();
      }    
        
     while ( (*portInputRegister(port) & bit) != stateMask) { // time when low
        firstlow=micros();
     }
        
        Serial.print("first high");
        Serial.print("\t");
        Serial.print(firsthigh);
        Serial.print("\n");
        Serial.print("first low");
        Serial.print("\t");
        Serial.print(firstlow);
        Serial.print("\n");
        
     time1=firstlow-firsthigh;
     time2=firsthigh-firstlow;
     time=time1+time2;   
     width[i]=firsthigh; 
     width[i+1]=firstlow;   
       
        Serial.print("time high");
        Serial.print("\t");
        Serial.print(time1);
        Serial.print("\n");
        Serial.print("time low");
        Serial.print("\t");
        Serial.print(time2);
        Serial.print("\n");
 } 

  
   for(int j=-1;j<8;j++) { //cylce, obtaining and assigning the time periods, we know that the toffset is made up of the two lowest values 
      { 
       if(width[j]==width[j+1]&&width[j]<width[j+2]&&width[j]<width[j+3]&&width[j+1]<width[j+2]&&width[j+1]<width[j+3]) { 
         startindex=j; 
         j=8;
       } 
     } 
   } 
   if(startindex!=-1) { 
    
    tOff=width[startindex]+width[startindex+1]; //defined periods
    tref=width[startindex+2]; 
    tx=width[startindex+3]; 
      
     
     *cap=((tx-tOff)/(tref-tOff))*CREF; //UTI 3 signal calculation 
     
     if (*cap=((tx-tOff)/(tref-tOff))*CREF){
     
       Serial.print("Tx:");
       Serial.print(tx);
        Serial.print("\t");
       Serial.print("\n");
       Serial.print("Toff:");
       Serial.print(tOff);
       Serial.print("\t");
       Serial.print("\n");
       Serial.print("Tref:");
       Serial.print(tref);
       Serial.print("\t");
       Serial.print("\n");
     }
     return 1; 
   } 
   else { 
     return 0; 
       
 } 

}
