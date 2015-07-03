#include <IRremote.h>

int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(57600);
  irrecv.enableIRIn(); // Start the receiver
}

long prevVolumeUp=0, prevVolumeDown=0, prevMute=0;
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
    else if(results.value==0x18B9|results.value==0x8B9) //Mute on dishtv remote
    {
     if(millis()-prevMute>300)
     {  
      Serial.println("volume");
      Serial.println(0);
      prevMute=millis();
     }   
    }
    irrecv.resume(); // Receive the next value
  }
}
