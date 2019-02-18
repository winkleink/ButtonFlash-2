#include <SPI.h>
#include <RF24.h>

// ce,csn pins
RF24 radio(9,10);

void setup(void)
{
    // init serial monitor
    Serial.begin(57600);
    Serial.println("This is the RX, so should see the received data");
    // init radio for reading
    radio.begin();
    radio.enableDynamicPayloads();
    radio.setAutoAck(0);
    radio.setRetries(2,2);
    radio.setDataRate(RF24_250KBPS);
    radio.setPALevel(RF24_PA_MAX);
    radio.setChannel(76);
    radio.openReadingPipe(1,0xF0F0F0F0E1LL);
    radio.startListening();
}

void loop(void)
{

  while(radio.available()){
//    read the 3 characters;
    char count[3]="";
    radio.read(&count, sizeof(count));

    Serial.print("I received :");
    Serial.println(count);
    
  }


}
