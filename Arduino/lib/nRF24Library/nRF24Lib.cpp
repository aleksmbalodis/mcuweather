#include "nRF24Lib.h"

void nRF24Lib::nRF24_RegisterWrite(uint8_t reg, uint8_t regbit, uint8_t val){
    digitalWrite(CSNpin, HIGH);
    SPI.transfer((W_REGISTER  || reg));
    if(val){
        SPI.transfer(1 << regbit);
    }
    else{
        SPI.transfer(0 << regbit);
    }
    digitalWrite(CSNpin, LOW);
}

//Inicialize kontrolieri un iestata RX rezima
void nRF24Lib::nRF24_Init(){
    _delay_ms(110);
    nRF24_RegisterWrite(CONFIG, PWR_UP, 1);
    _delay_ms(2);
    digitalWrite(CSpin, HIGH);
    nRF24_RegisterWrite(CONFIG, BITPOS_PRIM_RX, 1);
}

void nRF24Lib::nRF24_WriteTXData(uint8_t* pTXdata, uint8_t asize){
         digitalWrite(CSNpin, HIGH);
    SPI.transfer(W_TX_PAYLOAD);
    for(int i = 0; i <= asize; i++){
        SPI.transfer(pTXdata[i]);
    }
    digitalWrite(CSNpin, LOW);
}

//Iestata TX rezima
void nRF24Lib::nRF24_ENTXMode(){
    nRF24_RegisterWrite(CONFIG, BITPOS_PRIM_RX, 0);
}

void nRF24Lib::FlushTX(){
    SPI.transfer(FLUSH_TX);
}

uint8_t nRF24Lib::nRF24_ReadRXBuffer(){
    digitalWrite(CSNpin, HIGH);
    * RXbuffer = SPI.transfer(R_RX_PAYLOAD);
    digitalWrite(CSNpin, LOW);
    return *RXbuffer;
}