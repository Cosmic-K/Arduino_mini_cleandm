//version 1 original 
//Krishna Mooroogen
//liquid level sensor MINI clean
//1st June 2012

#include <stdio.h>
#include "pins_arduino.h"

#define UTI_PIN 5
#define UTI_cap_REF 180

void setup()
{
  Serial.begin(9600);
  pinMode(UTI_PIN, INPUT);
}

void loop()
{
  double cap;

   if(ReadUTI(UTI_PIN,&cap,UTI_cap_REF)) {
	
	Serial.print("Capacitance: ");
	Serial.print(cap);
	Serial.print("\t");
	
    }
    else {
	Serial.print("Not Found");
    }
    Serial.print("\n");
   delay(1000);
}

int ReadUTI(uint8_t pin, double * cap,int refcap)
{
    int state = HIGH;
    int i,startindex=-1;
    uint8_t bit = digitalPinToBitMask(pin);
    uint8_t port = digitalPinToPort(pin);
    uint8_t stateMask = (state ? bit : 0);
    unsigned long width[8] = {0,0,0,0,0,0,0,0,};
    double nOff=0,nAB=0,nCD=0;

    while ( (*portInputRegister(port) & bit) != stateMask)
	  ;

    for(i=0;i<8;i++) {
	while ( (*portInputRegister(port) & bit) == stateMask)
	    width[i]++;
	while ( (*portInputRegister(port) & bit) != stateMask)
	    width[i]++;
    }
    for(i=1;i<12;i++) {
	if(i<7) {
	  if(width[i]<width[i+2]&&width[i]<width[i+3]&&width[i+1]<width[i+2]&&width[i+1]<width[i+3]) {
	    startindex=i;
	    i=8;
	  }
	}
    }
    if(startindex!=-1) {
	nOff=width[startindex]+width[startindex+1];
	nAB=width[startindex+2];
	nCD=width[startindex+3];
	

	
	*cap=((nCD-nOff)/(nAB-nOff))*refcap;

	return 1;
    }
    else {
	return 0;
    }
}
 
