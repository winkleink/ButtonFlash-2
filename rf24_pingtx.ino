#include <SPI.h>
#include "RF24.h"

/*
radio 7 (miso) to uno/nano d12 (pin 18), mega2560 d50, promicro 14, promini 12
radio 6 (mosi) to uno/nano d11 (pin 17), mega2560 d51, promicro 16, promini 11
radio 5 (sck)  to uno/nano d13 (pin 19), mega2560 d52, promicro 15, promini 13
radio 4 (csn)  to uno/nano d10 (pin 16), mega2560 d48, promicro 10, promini 10
radio 3 (ce)   to uno/nano d9  (pin 15), mega2560 d49, promicro  9, promini  9
radio 2 (3.3v) to uno 3.3v
radio 1 (gnd)  to uno gnd
*/

// ce,csn pins
RF24 radio(9,10);

// init counter
//unsigned long count = 0;
int count = 48; // count is used for the characters
int pause =20;

void setup(void)
{
    // init serial monitor
    Serial.begin(57600);
    Serial.println("This is the TX, so sending the data");
    // init radio for writing
    radio.begin();
    radio.enableDynamicPayloads();
    radio.setAutoAck(0);
    radio.setRetries(2,2);
    radio.setDataRate(RF24_250KBPS);
    radio.setPALevel(RF24_PA_MAX);
    radio.setChannel(76);
    radio.openWritingPipe(0xF0F0F0F0E1LL);
}

void loop(void)
{
Serial.println("entered the loop");
Serial.println(count);    
    // 3 bytes is maximum payload
    char txBuffer[3]= "";
     
    // set the 3 character for the payload
 
      for (int x=0; x<3; x++){
      char var = count;
      txBuffer[x] = var;
//      Serial.println(count);
      }
      
      //add 1 to count to change the character and check if  reached Z
      count++;
      if (count > 90){
        count = 48;
      }

    for (int x=0; x<3; x++){
      Serial.print(txBuffer[x]);
    }
    Serial.println("");
    
    // transmit
    radio.write(&txBuffer, strlen(txBuffer));
    digitalWrite(2,HIGH);
    delay(pause);
    digitalWrite(2,LOW);
    delay(pause);
}
