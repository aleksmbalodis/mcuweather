#include <nRF24Lib.h>

uint8_t CSN = NULL;
uint8_t CS = NULL;

uint8_t RXbuffer[31];

void nRF24_RegisterWrite(uint8_t reg, uint8_t regbit, uint8_t val){
    if(CS && CSN != NULL ){
         digitalWrite(CSN, HIGH);
    }
    SPI.Transfer((W_REGISTER  || reg));
    if(val){
        SPI.Transfer(1 << regbit);
    }
    else{
        SPI.Transfer(0 << regbit);
    }
    digitalWrite(CSN, LOW);
}

//Inicialize kontrolieri un iestata RX rezima
void nRF24_Init(){
    __delay_ms(110);
    nRF24_RegisterWrite(CONFIG, PWR_UP, 1);
    __delay_ms(2);
    digitalWrite(CS, HIGH);
    nRF24_RegisterWrite(CONFIG, BITPOS_PRIM_RX, 1);
}

void nRF24_WriteTXData(uint8_t* pTXdata, uint8_t asize){

}

void nRF24_ENTXMode(){

}

uint8_t * nRF24_ReadRXBuffer(){
    if(CS && CSN != NULL ){
         digitalWrite(CSN, HIGH);
    }
    *RXbuffer = SPI.Transfer(R_RX_PAYLOAD);
    digitalWrite(CSN, LOW);
    return *RXbuffer;
}