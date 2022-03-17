#include <nRF24Lib.h>

 #define CSN 10
 #define CS 9

nRF24Lib rxradio(CSN, CS);

SPISettings settingsspi(8000000, MSBFIRST, SPI_MODE0);

uint8_t RxAddress[] = {0xEE,0xDD,0xCC,0xBB,0xAA};
uint8_t RxDati[32];

void setup(){
  Serial.begin(9600);
  pinMode(CSN, OUTPUT);
  pinMode(CS, OUTPUT);
  SPI.begin();
  SPI.beginTransaction(settingsspi);
  Serial.println("SPI BEGIN");
  rxradio.Init();
  Serial.println("nRF24 Init");
  rxradio.RX_Mode(RxAddress, 10);
  Serial.println("nRF24 RX MODE");
}

void loop(){
  if(rxradio.IsDataAvailable(1) == 1){
        rxradio.Receive(RxDati);
        for(uint8_t i = 0; i<33; i++){
        Serial.print(RxDati[i]);
        }
  }
}