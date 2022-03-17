#include <nRF24Lib.h>

 #define CSN 10
 #define CS 9

nRF24Lib txradio(CSN, CS);

SPISettings settingsspi(8000000, MSBFIRST, SPI_MODE0);

uint8_t TxAddress[] = {0xEE,0xDD,0xCC,0xBB,0xAA};
uint8_t TxDati[] = "Strada komunikacija!\n";

void setup(){
  Serial.begin(9600);
  pinMode(CSN, OUTPUT);
  pinMode(CS, OUTPUT);
  SPI.begin();
  SPI.beginTransaction(settingsspi);
  Serial.println("SPI BEGIN");
  txradio.Init();
  Serial.println("nRF24 INIT");
  txradio.TX_Mode(TxAddress, 10);
  Serial.println("nRF24 Enter TX Mode");
}

void loop(){
  if(txradio.Transmit(TxDati) == 1){
    Serial.println("OK");
  }
  delay(1000);

}