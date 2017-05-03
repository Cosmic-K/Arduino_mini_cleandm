/*Krishna Mooroogen
Wednesday 11th June 2012
Capacitance readout for liquid level sensor MINIclean
board timer till reset after 70mins
Control of the UTI chip, applying the three signal technique after measuring the time signals 
prints intemidiate steps for debugging, outputs average capacitance after 10 loops
*/


void setup()
{
  Serial.begin(9600); //set serial communication 
  pinMode(8, INPUT); //set digital pin mode as an inputmight have to change this 
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);//mode select high
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
 
}


//main body
void loop()
{ 
    float cap; //definine variables for later
    unsigned long capac[10]={0,0,0,0,0,0,0,0,0,0};
    float sum=0;
    int n=0;
    float capacitance=0;
    float y=0;
    
    
    for (int m=0; m<10; m++){ //loop ten times for an average capacitance 
  
    if(ReadUTI(5, &cap)) { //fucntion defined below 
    capac[n]=cap;
    Serial.print("Capacitance: ");//iterate and store in array
    Serial.println(capac[n]); //display for debugging 
    Serial.println();
    delay(500); //wait periods to stop clogging 
     
    n++;
}
  
    else {
    
    Serial.print("Not Found");
  
}
  }
   
   
  for(int a=0; a<10; a++){
   
   y=(sum+=capac[a]);
   }
   
  //print out the average capacitance 
  
   capacitance=(y/10);
   Serial.print("Average Capacitance ");
   Serial.println(capacitance);    
   
 
   
   
   
   //delay(100);//delay between reads 
   
   Serial.flush();//clears buffer
   Serial.end();//ends serial read 
   
}

//define function ReadUTI
    int ReadUTI( int in, float *cap) 
{ 
    int b=0; //define array intergers 
    int j=0;
    unsigned long width[34] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //define array for 'time stamps' need 34 as we need 16 periods, as i=i+2 
    unsigned long timep[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};//array for storing periods 
    float toff=0;
    float tref=0;
    float tx=0; //define periods 
    float time1=0;
    float time2=0;
    float time=0;  
  
  
    for(int i=0;i<33;i=i+2) { //for these iterations moving in twos, so that in each turn two slots are filled. 
    
       
    
    while (digitalRead(8) == LOW){
         
         width[i]=micros(); //takes time at rising edge (will continuley take time stamps while high or low, will overwrite with the last value making it the rising or fallign edge) time program has been running at that point. 
        }
  
    while  (digitalRead(8) == HIGH){
        width[i+1]=micros(); //takes time at falling edge, first reading will be unusable from this method 
         }
  
}  
     
     
     
        for (int g=0; g<33; g++){ //prints out array width to check the 'time stamps' 
        
        Serial.print("width ");
        Serial.println(width[g]);
        
       }
     
   
    
       for( int k=0; k<32; k+=2){
      
       timep[j]=width[k+2]-width[k];//calculates the time periods, time the board has been running-previous time. 
       
        Serial.print("time period ");
        Serial.println(timep[j]);
        j++;
 }
    

    for(b=0;b<8;b++) {//something here not quite right....
	 
   
    if ((0.95*timep[b+1])<=timep[b]<=(1.05*timep[b+1])&&timep[b]<timep[b+2]&&timep[b]<timep[b+3]&&timep[b+1]<timep[b+2]&&timep[b+1]<timep[b+3]){//picking the offset periods 
     
      toff=timep[b]+timep[b+1];
      tref=timep[b+2];
      tx=timep[b+3];
   
      *cap=((tx-toff)/(tref-toff))*2.2; //UTI 3 signal calculation 	  
      
      }
       
    }
    
      Serial.print("Tx: ");
      Serial.println(tx);
      Serial.print("Toff: ");
      Serial.println(toff);
      Serial.print("Tref: ");
      Serial.println(tref);
     
 }
   



 




















