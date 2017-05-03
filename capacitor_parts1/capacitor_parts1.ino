//Krishna Mooroogen
//Wednesday 11th June 2012
//Capacitance readout for liquid level sensor MINIclean

 //defining UTI output to Arduino input pin
int CREF = 180;  //defining the reference capacitor value not yet

void setup()
{
  Serial.begin(9600); //set serial communication 
  pinMode(5, INPUT); //set pin mode
  
}

//main body
void loop()
{ 
  float cap; 
  
  if(ReadUTI(5, &cap, CREF)) {
    Serial.print("Capacitance:");
    Serial.print(cap);
    Serial.print("\t"); //interface for outputting value
  } else {
  
    Serial.print("Not Found");
  }
  Serial.print("\n");
  delay(1000);
}

//function ReadUTI
 int ReadUTI(int in, float *cap,int CREF) 
{ 
  
  int startindex=0; 
  unsigned long width[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //define array for cycles, 4 periods in each so need at least 8 
  float tOff=0;
  float tref=0;
  float tx=0; //define periods 
  float time1=0;
  float time2=0;
  float time=0;   
  
  for(int i=0;i<16;i=i+2) {        
    
    while (digitalRead(5) == HIGH) {
         
         width[i]=micros(); //takes time at rising edge 
        }
  
    while  (digitalRead(5) == LOW){
        width[i+1]=micros(); //takes time at falling edge 
         }
  
}  
        //looping through high and low values
        for (int g=0; g<16; g++){
        
        Serial.print("width");
        Serial.print("\t");
        Serial.print(width[g]);
        Serial.print("\n");
      }
     
   
    { 
      int k=0;
      time1=width[k+1]-width[k];
      time2=width[k+2]-width[k+1];
      //time=time1+time2;   
    }  
    
   
     {   
        Serial.print("time high");
        Serial.print("\t");
        Serial.print(time1);
        Serial.print("\n");
        Serial.print("time low");
        Serial.print("\t");
        Serial.print(time2);
        Serial.print("\n");

  
   
Serial.end();
Serial.flush(); 
  } 

}

























