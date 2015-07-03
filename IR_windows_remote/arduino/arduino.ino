#include <IRremote.h>

int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(57600);
  irrecv.enableIRIn(); // Start the receiver
}

long  prevVolumeUp=0, prevVolumeDown=0, prevMute=0, prevUp=0, prevDown=0, prevLeft=0, prevRight=0; //last time the key was pressed 
long  prevEnter=0, prevTab=0, prevDesktop=0, prevBackspace=0, prevCloseWindow=0;
boolean altStatus=false;

void loop() {
  if (irrecv.decode(&results)) 
  {
    Serial.println(results.value, HEX);
    if(results.value==0x18C2||results.value==0x8C2) //Volume up button on dishtv remote
    {
     if(millis()-prevVolumeUp>50) //check if atleast 50 milli sec had passed since the previous command
     {  
      Serial.println("volume"); //identifier to convey that the following value will e related to to volume
      Serial.println(9);
      prevVolumeUp=millis();
     }
    }
    else if(results.value==0x1894||results.value==0x894) //Volume down button on dishtv remote
    {
     if(millis()-prevVolumeDown>50)
     {  
      Serial.println("volume");
      Serial.println(1);
      prevVolumeDown=millis();
     }
    }
    else if(results.value==0x18B9||results.value==0x8B9) //Mute on dishtv remote
    {
     if(millis()-prevMute>300)
     {  
      Serial.println("volume");
      Serial.println(0);
      prevMute=millis();
     }   
    }
    else if(results.value==0x1880||results.value==0x880) //Up key on dishtv remote
    {
     if(millis()-prevUp>100)
     {  
      Serial.println("navigate");
      Serial.println(0);
      prevUp=millis();
     }   
    }
    else if(results.value==0x1883||results.value==0x883) //Down key on dishtv remote
    {
     if(millis()-prevDown>100)
     {  
      Serial.println("navigate");
      Serial.println(1);
      prevDown=millis();
     }   
    }
    else if(results.value==0x1886||results.value==0x886) //Left key on dishtv remote
    {
     if(millis()-prevLeft>100)
     {  
      Serial.println("navigate");
      Serial.println(2);
      prevLeft=millis();
     }   
    }
    else if(results.value==0x1885||results.value==0x885) //Right key on dishtv remote
    {
     if(millis()-prevRight>100)
     {  
      Serial.println("navigate");
      Serial.println(3);
      prevRight=millis();
     }   
    }
    else if(results.value==0x189E||results.value==0x89E) //OK / Enter key on dishtv remote
    {
     if(millis()-prevRight>100)
     {  
      Serial.println("navigate");
      Serial.println(4);
      prevRight=millis();
     }   
    }
    else if(results.value==0x1898||results.value==0x898) //av/menu keyon dishtv remote for alt+tab emulation
    {                                         //send 5 to press alt, 6 to press and release tab, 7 to release tab
     if (altStatus==false)   //press tab if not already pressed
     {  
      Serial.println("navigate");
      Serial.println(5);
      altStatus=true;
     }
     if((millis()-prevTab>100)&&altStatus)  //hit tab
     {  
      Serial.println("navigate");
      Serial.println(6);
      prevTab=millis();
     } 
    }
    else if(results.value==0x18BC||results.value==0x8BC) //Guide key on dishtv remote to show desktop through win + d
    {
     if(millis()-prevDesktop>500)
     {  
      Serial.println("navigate");
      Serial.println(8);
      prevDesktop=millis();
     }   
    }
    else if(results.value==0x189B||results.value==0x89B) //Exit key on dishtv remote to emulate backspace, usefull to go back while navigating in windows explorer
    {
     if(millis()-prevBackspace>100)
     {  
      Serial.println("navigate");
      Serial.println(9);
      prevBackspace=millis();
     }   
    }
    else if(results.value==0x188A||results.value==0x88A) //red button on dish tv remote to close the current window using alt + F4
    {
     if(millis()-prevCloseWindow>500)
     {  
      Serial.println("navigate");
      Serial.println(10);
      prevCloseWindow=millis();
     }   
    }
    
    irrecv.resume(); // Receive the next value
  }
  if((millis()-prevTab > 700)&&altStatus)  //disingage alt if tab was not sent since 1000 milli sec
    {
      Serial.println("navigate");
      Serial.println(7);
      altStatus=false;
    }
}
