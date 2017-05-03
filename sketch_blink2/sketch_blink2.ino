 #include <stdio.h>
#include "pins_arduino.h"

#define UTI_PIN 5
#define UTI_CAPACITOR_REF ***

void setup()
{
  Serial.begin(9600);
  pinMode(UTI_PIN, INPUT);
}

void loop()
{
  double cap1,cap2;

   if(ReadUTI(UTI_PIN,&cap1,&cap2,UTI_CAPACITOR_REF)) {
	Serial.print("Capacitance 1: ");
	Serial.print(cap1);
	Serial.print("\t");
	Serial.print("Capacitance 2: ");
	Serial.print(cap2);
	Serial.print("\t");
	
    }
    else {
	Serial.print("Not Found");
    }
    Serial.print("\n");
   delay(2000);
}

int ReadUTI(uint8_t pin, double * cap1,double * cap2,int refCap)
{
    int state = HIGH;
    int i,startindex=-1;
    uint8_t bit = digitalPinToBitMask(pin);
    uint8_t port = digitalPinToPort(pin);
    uint8_t stateMask = (state ? bit : 0);
    unsigned long width[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
    double nOff=0,nAB=0,nCD=0,nBC=0,nDF=0;

    while ( (*portInputRegister(port) & bit) != stateMask)
	  ;

    for(i=0;i<12;i++) {
	while ( (*portInputRegister(port) & bit) == stateMask)
	    width[i]++;
	while ( (*portInputRegister(port) & bit) != stateMask)
	    width[i]++;
    }
    for(i=1;i<12;i++) {
	if(i<7) {
	  if(width[i]<width[i+2]&&width[i]<width[i+3]&&width[i]<width[i+4]&&width[i]<width[i+5]&&width[i+1]<width[i+2]&&width[i+1]<width[i+3]&&width[i+1]<width[i+4]&&width[i+1]<width[i+5]) {
	    startindex=i;
	    i=12;
	  }
	}
    }
    if(startindex!=-1) {
	nOff=width[startindex]+width[startindex+1];
	nAB=width[startindex+2];
	nCD=width[startindex+3];
	nBC=width[startindex+4];
	nDF=width[startindex+5];

	*res1=((nBC-nOff)/(nAB-nOff))*refRes;
	*res2=((nCD-nOff)/(nAB-nOff))*refRes;
	*res3=((nDF-nOff)/(nAB-nOff))*refRes;

	return 1;
    }
    else {
	return 0;
    }
}
 



