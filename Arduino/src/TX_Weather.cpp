#include <nRF24Lib.h>

 #define CSN 9
#define CS 10

nRF24Lib txradio(CSN, CS);


uint8_t TxAddress[] = {0xEE,0xDD,0xCC,0xBB,0xAA};
uint8_t TxDati[32] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32 };


void setup(){
  
  Serial.begin(9600);
  SPI.begin();
  Serial.println("SPI BEGIN");
  txradio.Init();
  txradio.TX_Mode(TxAddress, 10);
  Serial.println("TX BEGIN");
}

void loop(){
  if(txradio.Transmit(TxDati) == 1){
    Serial.println("OK");
  }
  delay(100);

}