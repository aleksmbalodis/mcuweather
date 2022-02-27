#include <nRF24Lib.h>

 #define CSN 10
 #define CS 9

uint8_t dati[5] = {5,3,1,1,0};
nRF24Lib radio(CSN, CS);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.nRF24_Init();
  radio.nRF24_ENTXMode();
}

void loop() {
  // put your main code here, to run repeatedly:
  radio.nRF24_WriteTXData(dati, sizeof(dati));
  radio.FlushTX();
}