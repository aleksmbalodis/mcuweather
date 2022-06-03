#include <nRF24Lib.h>

 #define CSN 9
#define CS 10

nRF24Lib rxradio(CSN, CS);


uint8_t RxAddress[] = {0xEE,0xDD,0xCC,0xBB,0xAA};
uint8_t RxDati[32];

void setup(){
  Serial.begin(9600);
  SPI.begin();
  Serial.println("SPI BEGIN");
  rxradio.Init();
  rxradio.RX_Mode(RxAddress, 10);
  Serial.println("RX BEGIN");
}

void loop(){
  if (rxradio.IsDataAvailable(1) == 1)
	  {
		  rxradio.Receive(RxDati);
      
		  for(int i = 0; i < sizeof(RxDati); i++)
      {
        Serial.print(RxDati[i]);
        Serial.print(" ");
      }
      Serial.println("");
	  }

  delay(1000);
}