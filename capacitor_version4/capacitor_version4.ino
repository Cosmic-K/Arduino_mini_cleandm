/*Krishna Mooroogen
Wednesday 11th June 2012
Capacitance readout for liquid level sensor MINIclean
board timer till reset after 70mins
Control of the UTI chip, applying the three signal technique after measuring the time signals 
*/


void setup()
{
  Serial.begin(9600); //set serial communication 
  pinMode(5, INPUT); //set digital pin mode as an input 
  
}


//main body
void loop()
{ 
  float cap; //definine capacitence for later
  
  
  if(ReadUTI(5, &cap)) { //if this function to be defined below 
    Serial.print("Capacitance:");
    Serial.print(cap);
    Serial.print("\t"); //interface for outputting value

}
  
  else {
    
    Serial.print("Not Found");
  
}
    Serial.print("\n");
    delay(1000);//delay between reads 
   
   
    Serial.flush();//clears buffer
    Serial.end();//ends serial read 
   
}

//define function ReadUTI
    int ReadUTI( int in, float *cap) 
{ 
    int b=0; //define array intergers 
    int j=0;
    unsigned long width[18] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //define array for 'time stamps' need 34 as we need 16 periods, as i=i+2 
    unsigned long timep[8]={0,0,0,0,0,0,0,0,};//array for storing periods 
    float toff=0;
    float tref=0;
    float tx=0; //define periods 
    float time1=0;
    float time2=0;
    float time=0;  
  
  
    for(int i=0;i<17;i=i+2) { //for these iterations moving in twos, so that in each turn two slots are filled. 
    
       
    
    while (digitalRead(5) == LOW){
         
         width[i]=micros(); //takes time at rising edge (will continuley take time stamps while high or low, will overwrite with the last value making it the rising or fallign edge) time program has been running at that point. 
        }
  
    while  (digitalRead(5) == HIGH){
        width[i+1]=micros(); //takes time at falling edge, first reading will be unusable from this method 
         }
  
}  
     
     
     
        for (int g=0; g<17; g++){ //prints out array width to check the 'time stamps' 
        
        Serial.print("width");
        Serial.print("\t");
        Serial.print(width[g]);
        Serial.print("\n");
       }
     
   
    
       for( int k=0; k<16; k+=2){
      
       timep[j]=width[k+2]-width[k];//calculates the time periods, time the board has been running-previous time. 
       
        Serial.print("time period");
        Serial.print("\t");
        Serial.print(timep[j]);
        Serial.print("\n");
        j++;
 }
    
   
    for(b=1;b<8;b++) {//something here not quite right....
	 
   
    if ((0.95*timep[b+1])<=timep[b]<=(1.05*timep[b+1])&&timep[b]<timep[b+2]&&timep[b]<timep[b+3]&&timep[b+1]<timep[b+2]&&timep[b+1]<timep[b+3]){//picking the offset periods 
     
      toff=timep[b]+timep[b+1];
      tref=timep[b+2];
      tx=timep[b+3];
   
      *cap=((tx-toff)/(tref-toff))*180; //UTI 3 signal calculation 	  
      
      }
      
      Serial.print("Tx:");
      Serial.print(tx);
      Serial.print("\t");
      Serial.print("\n");
      Serial.print("Toff:");
      Serial.print(toff);
      Serial.print("\t");
      Serial.print("\n");
      Serial.print("Tref:");
      Serial.print(tref);
      Serial.print("\t");
      Serial.print("\n"); 
    }

 }
   



 




















