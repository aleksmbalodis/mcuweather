#include <nRF24Lib.h>

uint8_t CSN = NULL;
uint8_t CS = NULL;

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

void nRF24_Init(){
    __delay_ms(110);
    nRF24_RegisterWrite(CONFIG, PWR_UP, 1);
    __delay_ms(2);
}