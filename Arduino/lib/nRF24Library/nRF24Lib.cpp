#include "nRF24Lib.h"

SPISettings SPIrfsett(4000000, MSBFIRST, SPI_MODE0);

void nRF24Lib::CS_Select(void){
    digitalWrite(CSpin, LOW);
}

void nRF24Lib::CS_UnSelect(void){
    digitalWrite(CSpin, HIGH);
}

void nRF24Lib::CE_Enable(void){
    digitalWrite(CSNpin, HIGH);
}

void nRF24Lib::CE_Disable(void){
    digitalWrite(CSNpin, LOW);
}

//Parbaudits
void nRF24Lib::WriteRegister(uint8_t reg, uint8_t data){
    uint8_t buf[2];
    buf[1] = reg|1<<5;
    buf[2] = data;

    SPI.beginTransaction(SPIrfsett);
    CS_Select();

    SPI.transfer(buf[1]);
    SPI.transfer(buf[2]);

    CS_UnSelect();
    SPI.endTransaction();

}

void nRF24Lib::WriteRegisterMulti(uint8_t reg, uint8_t * data, int size){
    uint8_t buf[2];
    buf[1] = reg|1<<5;

    SPI.beginTransaction(SPIrfsett);
    CS_Select();

    SPI.transfer(buf[1]);
    for(int i = 0; i < size; i++)
    {
        SPI.transfer(data[i]);
    }

    CS_UnSelect();
    SPI.endTransaction();

}

//Parbaudits
uint8_t nRF24Lib::ReadRegister(uint8_t reg){
    uint8_t dati;

    SPI.beginTransaction(SPIrfsett);
    CS_Select();

    SPI.transfer(reg);
    dati = SPI.transfer(0);

    CS_UnSelect();
    SPI.endTransaction();

          //Serial.println(dati);
    return dati;
}

void nRF24Lib::ReadRegisterMulti(uint8_t reg, uint8_t *data, int size){

	SPI.beginTransaction(SPIrfsett);
    CS_Select();

	SPI.transfer(&reg, 1);
    *data = SPI.transfer(0);

	CS_UnSelect();
    SPI.endTransaction();
}

void nRF24Lib::SendCommand(uint8_t cmd){
    SPI.beginTransaction(SPIrfsett);
    CS_Select();
    SPI.transfer(&cmd, 1);
    CS_UnSelect();
    SPI.endTransaction();
}

void nRF24Lib::Init(void){
    CE_Disable();

    WriteRegister(CONFIG, 0);

    WriteRegister(EN_AA, 0);

    WriteRegister(EN_RXADDR, 0);

    WriteRegister(SETUP_AW, 0x03);

    WriteRegister(SETUP_RETR, 0);

    WriteRegister(RF_CH, 0);

    WriteRegister(RF_SETUP, 0x0E);

    CE_Enable();
}

void nRF24Lib::TX_Mode(uint8_t *address, uint8_t ch){
    CE_Disable();

    WriteRegister(RF_CH, ch);
    WriteRegisterMulti(TX_ADDR, address, 5);

    uint8_t cfg = ReadRegister(CONFIG);
    cfg = cfg | (1<<1);
    WriteRegister(CONFIG, cfg);

    CE_Enable();
}

uint8_t nRF24Lib::Transmit(uint8_t *dati){
    //uint8_t cmdsend = 0;

    SPI.beginTransaction(SPIrfsett);

    CS_Select();
    //cmdsend = W_TX_PAYLOAD;
    SPI.transfer(W_TX_PAYLOAD);
    for(int i = 0; i < 32; i++)
    {
     SPI.transfer(dati[i]);
    }

    CS_UnSelect();
    SPI.endTransaction();

    delay(1);

    uint8_t fifostatus;
    fifostatus = ReadRegister(FIFO_STATUS);

    if ((fifostatus&(1<<4)) && (!(fifostatus&(1<<3)))){
            //cmdsend = FLUSH_TX;
            SendCommand(FLUSH_TX);

            return 1;
    }

return 0;
}

void nRF24Lib::RX_Mode(uint8_t *address, uint8_t ch){
    CE_Disable();

    WriteRegister(RF_CH, ch);

    uint8_t enrxaddr = ReadRegister(EN_RXADDR);
    enrxaddr = enrxaddr | (1<<1);
    WriteRegister(EN_RXADDR, enrxaddr);

    WriteRegisterMulti(RX_ADDR_P1, address, 5);

    WriteRegister(RX_PW_P1, 32);

    uint8_t cfg = ReadRegister(CONFIG);
    cfg = cfg | (1<<1) | (1<<0);
    WriteRegister(CONFIG, cfg);

    CE_Enable();
}

uint8_t nRF24Lib::IsDataAvailable(int pipenr){

    uint8_t status = ReadRegister(STATUS);

    if((status&(1<<6))&&(status&(pipenr<<1))){
        WriteRegister(STATUS, (1<<6));
        return 1;
    }
    return 0;
}

void nRF24Lib::Receive(uint8_t *data){
    //uint8_t cmdsend = 0;

    SPI.beginTransaction(SPIrfsett);
    CS_Select();
    //cmdsend = R_RX_PAYLOAD;
    SPI.transfer(R_RX_PAYLOAD);

    for(int i = 0; i < 32; i++)
    {
        data[i] = SPI.transfer(0);
    }
    CS_UnSelect();
    SPI.endTransaction();

    delay(1);

    //cmdsend = FLUSH_RX;
    SendCommand(FLUSH_RX);

}