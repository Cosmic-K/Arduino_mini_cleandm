/*
 Web Server
Krishna Mooroogen
21st June 2012 
web server for capacitance liquid level sensor 
MINIclean 
Supervisor Dr James Nikkel 
controller to be able to talk via ethernet to a master program
*/

  #include <SPI.h>
  #include <Ethernet.h>
  
  // Enter a MAC address and IP address for your controller below.
  // The IP address will be dependent on your local network:
  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  IPAddress ip(192,168,1, 177);

  // Initialize the Ethernet server library
  // with the IP address and port you want to use 
  // (port 80 is default for HTTP):
  EthernetServer server(80);

  

void setup() 
{
 
    pinMode (2, OUTPUT); //set pins 2-6 as outputs, 6 is on and off pin 
    pinMode (3, OUTPUT);
    pinMode (4, OUTPUT);
    pinMode (5, OUTPUT);
    pinMode (6, OUTPUT);
    pinMode (7, INPUT);    //input signal
    char ret_string[100];
 
  // Open serial communications and wait for port to open:
  
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  int Low=0;
  int High=0;
  
  if (strncmp(ret_string,'setmodeLow', 10) == 0)
  {
    mode_select==Low;
  }

  else if(strncmp(ret_string,'setmodeHigh', 11) == 0)
  {
    mode_select==High;
  }
  else 
  {
    mode_select==High
  }


}

  void loop() 
  {
  // listen for incoming clients
  
  char ret_string[100];
  int x;
  
  EthernetClient client = server.available();
  
  if (client) 
  {
    x=0;
    
  boolean currentLineIsBlank = true;
    while (client.connected()) 
    {
      if (client.available()) 
      {
        char c = client.read();
        
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) 
        { 
          ret_string[x]="\0";
          client.print();
        }
        
        else 
        {
          ret_string[x]=c;
        }
      }
    }
    
    if(strncmp(ret_string,'GetCap', 6) == 0)
    {
    read_cap;
    client.print(*capacitance);
    }
    else 
    {
      client.print("error");
     }
    
   }
    
    client.println("disonnected");
    client.stop();
}


    
  
  
  int mode_select(int Low, int High)//rubiish for now
  {
    if(mode_select==Low)
    {
       digitalWrite(2,LOW);
       digitalWrite(3,LOW);
       digitalWrite(4,LOW);
       digitalWrite(5,HIGH);
    }
    
    else(mode_select==High); {
    
       digitalWrite(2,LOW);
       digitalWrite(3,HIGH);
       digitalWrite(4,LOW);
       digitalWrite(4,LOW);
   
    }
  }
  
  
  int ReadUTI( int in, float *cap) 
{
    
    int b=0; //define array intergers 
    int j=0;
    unsigned long width[34] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //define array for 'time stamps' need 34 as we need 16 periods, as i=i+2 
    unsigned long timep[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//array for storing periods 
    float toff=0;
    float tref=0;
    float tx=0; //define periods 
    float time1=0;
    float time2=0;
    float time=0;  
  
  
    for(int i=0;i<33;i=i+2) //for these iterations moving in twos, so that in each turn two slots are filled. 
    { 
    
       
    
    while (digitalRead(5) == LOW)
    {
         
         width[i]=micros(); //takes time at rising edge (will continuley take time stamps while high or low, will overwrite with the last value making it the rising or fallign edge) time program has been running at that point. 
        }
  
    while  (digitalRead(5) == HIGH)
    {
        width[i+1]=micros(); //takes time at falling edge, first reading will be unusable from this method 
         }
  
   }  
       
     
     digitalWrite(6,LOW);
     
      for( int k=0; k<32; k+=2)
       {
      
       timep[j]=width[k+2]-width[k];//calculates the time periods, time the board has been running-previous time. 
       j++;
      }
    

       for(b=0;b<8;b++) {
	 
   
       if ((0.95*timep[b+1])<=timep[b]<=(1.05*timep[b+1])&&timep[b]<timep[b+2]&&timep[b]<timep[b+3]&&timep[b+1]<timep[b+2]&&timep[b+1]<timep[b+3]){//picking the offset periods 
     
      toff=timep[b]+timep[b+1];
      tref=timep[b+2];
      tx=timep[b+3];
   
      *cap=((tx-toff)/(tref-toff))*100; //UTI 3 signal calculation 	  
      
      }
     }
   }

 
 float read_cap()
{    
    digitalWrite(6,HIGH);
    delay(2000);
    
    float cap; //definine variables for later
    unsigned long capac[10]={0,0,0,0,0,0,0,0,0,0};
    int sum=0;
    int n=0;
    int &capacitance=0;
    int y=0;
    
    
    for (int m=0; m<10; m++)  //loop ten times for an average capacitance 
    {                  
  
    if(ReadUTI(5, &cap)) //fucntion defined below
    {  
    capac[n]=cap;
    n++;
    delay(500); //wait periods to stop clogging 
     
   
  }
  
}
   
   for(int a=0; a<10; a++){
     y=(sum+=capac[a]);
   }
   
   &capacitance=(y/10);
}  
 
  
    
    
    
    
   
