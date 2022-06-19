#include "nRF24Lib.h"

// SPI iestatijumi 4MHz, Most Significant Byte First un CPOL 0, CPHA 0
SPISettings SPIrfsett(4000000, MSBFIRST, SPI_MODE0);

/*------------------------------------------------- CS_Select -----
|  Funkcija CS_Select
|
|  Pielietojums:  Iestata Chip Select pin uz zemo limeni
|
*-------------------------------------------------------------------*/
void nRF24Lib::CS_Select(void){
    digitalWrite(CSpin, LOW);
}

/*------------------------------------------------- CS_UnSelect -----
|  Funkcija CS_UnSelect
|
|  Pielietojums:  Iestata Chip Select pin uz augsto limeni
|
*-------------------------------------------------------------------*/
void nRF24Lib::CS_UnSelect(void){
    digitalWrite(CSpin, HIGH);
}

/*------------------------------------------------- CE_Enable -----
|  Funkcija CE_Enable
|
|  Pielietojums:  Iestata Chip Enable pin uz augsto limeni
|
*-------------------------------------------------------------------*/
void nRF24Lib::CE_Enable(void){
    digitalWrite(CSNpin, HIGH);
}

/*------------------------------------------------- CE_Disable -----
|  Funkcija CE_Disable
|
|  Pielietojums:  Iestata Chip Enable pin uz zemo limeni
|
*-------------------------------------------------------------------*/
void nRF24Lib::CE_Disable(void){
    digitalWrite(CSNpin, LOW);
}

/*------------------------------------------------- WriteRegister -----
|  Funkcija WriteRegister
|
|  Pielietojums:  Si funkcija lauj ierakstīt nRF24L01 registra datus.
|
|  Parametri:
|      uint8_t reg (IN) -- saja parametra norada registra adresi
|      uint8_t data (IN) -- saja parametra ievada velamo vertibu 
|                           ko iestatit registra
|
*-------------------------------------------------------------------*/
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

/*------------------------------------------------- WriteRegisterMulti -----
|  Funkcija WriteRegisterMulti
|
|  Pielietojums:  Si funkcija lauj ierakstīt nRF24L01 registra datu masivu.
|
|  Parametri:
|      uint8_t reg (IN) -- saja parametra norada registra adresi
|      uint8_t * data (IN) -- saja parametra ievada velamo vertibu masivu 
|                             ko ierakstit registra
|      int size (IN) -- Saja parametra janorada rakstamo datu masiva garumu
|
*-------------------------------------------------------------------*/
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

/*------------------------------------------------- ReadRegister -----
|  Funkcija ReadRegister
|
|  Pielietojums:  Si funkcija lauj nolasit nRF24L01 registra vertibu.
|
|  Atgriez: Si funkcija atgriez nolasama registra vertibu.
|
|  Parametri:
|      uint8_t reg (IN) -- saja parametra norada nolasama registra adresi
|
*-------------------------------------------------------------------*/
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

/*------------------------------------------------- ReadRegisterMulti -----
|  Funkcija ReadRegisterMulti
|
|  Pielietojums:  Si funkcija lauj nolasit nRF24L01 registra vertibas un ielasit to masiva.
|
|  Parametri:
|      uint8_t reg (IN) -- saja parametra norada nolasama registra adresi
|      uint8_t *data (OUT) -- saja parametra norada raditaju uz masivu kur tiks ielasiti dati no registra
|       int size (IN) -- saja parametra norada masiva (kur tiks ielasiti dati) lielumu
|
*-------------------------------------------------------------------*/
void nRF24Lib::ReadRegisterMulti(uint8_t reg, uint8_t *data, int size){

	SPI.beginTransaction(SPIrfsett);
    CS_Select();

	SPI.transfer(&reg, 1);
    *data = SPI.transfer(0);

	CS_UnSelect();
    SPI.endTransaction();
}

/*------------------------------------------------- SendCommand -----
|  Funkcija SendCommand
|
|  Pielietojums:  Si funkcija nosuta komandu uz nRF24L01 moduli
|
|  Parametri:
|      uint8_t cmd (IN) -- Nosutama komanda
|
*-------------------------------------------------------------------*/
void nRF24Lib::SendCommand(uint8_t cmd){
    SPI.beginTransaction(SPIrfsett);
    CS_Select();
    SPI.transfer(&cmd, 1);
    CS_UnSelect();
    SPI.endTransaction();
}

/*------------------------------------------------- Init -----
|  Funkcija Init
|
|  Pielietojums:  Funkcija sagatavo nRF24L01 bezvadu moduli darbībai. 
|  Vispirms konfigurācija tiek nodzēsta iestatot visas vērtības uz 0. 
|  Pēc tam tiek izslēgta Auto-Acknowledgment funkcija, izslēgtas visas 
|  datu saņemšanas līnijas, saņemšanas/sūtīšanas līniju platums tiek iestatīts uz 5 baitiem, 
|  Auto-Retransmit tiek iestatīts uz 250 mikrosekundēm, moduļa frekvence tiek iestatīta uz 
|  2400 MHz un ātrums uz 2Mbps. Funkcija neatgriež vērtību un nepieprasa parametrus.
|
*-------------------------------------------------------------------*/
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

/*------------------------------------------------- TX_Mode -----
|  Funkcija TX_Mode
|
|  Pielietojums:  Si funkcija iestata nRF24L01 bezvadu moduli sutisanas rezima
|
|  Parametri:
|      uint8_t *address (IN) -- Saja parametra ievada raditaju uz masivu kurs satur sanemeja adresi
|      uint8_t ch (IN) -- Saja parametra ievada kanalu uz kurieni sutit datus (Frekvence ir 2400MHz + ch)
|
*-------------------------------------------------------------------*/
void nRF24Lib::TX_Mode(uint8_t *address, uint8_t ch){
    CE_Disable();

    WriteRegister(RF_CH, ch);
    WriteRegisterMulti(TX_ADDR, address, 5);

    uint8_t cfg = ReadRegister(CONFIG);
    cfg = cfg | (1<<1);
    WriteRegister(CONFIG, cfg);

    CE_Enable();
}

/*------------------------------------------------- Transmit -----
|  Funkcija Transmit
|
|  Pielietojums:  Si funkcija nosuta datus izmantojot nRF24L01
|
|  Parametri:
|      uint8_t *dati (IN) -- Saja parametra ievada raditaju uz masivu kurs satur sutamos datus.
|      Sim masivam ir jabut 32 garam.
|
*-------------------------------------------------------------------*/
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

    if ((fifostatus&(1<<4)) 
    && (!(fifostatus&(1<<3)))){
            //cmdsend = FLUSH_TX;
            SendCommand(FLUSH_TX);

            return 1;
    }

return 0;
}

/*------------------------------------------------- RX_Mode -----
|  Funkcija RX_Mode
|
|  Pielietojums:  Si funkcija iestata nRF24L01 bezvadu moduli sanemsanas rezima
|
|  Parametri:
|      uint8_t *address (IN) -- Saja parametra ievada raditaju uz masivu kurs satur sutitaja adresi
|      uint8_t ch (IN) -- Saja parametra ievada kanalu uz ka gaidit sanemamos datus (Frekvence ir 2400MHz + ch)
|
*-------------------------------------------------------------------*/
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

/*------------------------------------------------- IsDataAvailable -----
|  Funkcija IsDataAvailable
|
|  Pielietojums:  Si funkcija iestata nRF24L01 bezvadu moduli sanemsanas rezima
|
|  Atgriez: Funkcija atgriez 1 vai 0 atkariba no ta vai dati ir pieejami sanemsanai
|
|  Parametri:
|      int pipenr (IN) -- Saja parametra ievada datu linijas numuru, kuru parbaudit uz sanemajamiem datiem.
|
*-------------------------------------------------------------------*/
uint8_t nRF24Lib::IsDataAvailable(int pipenr){

    uint8_t status = ReadRegister(STATUS);

    if((status&(1<<6))
    &&(status&(pipenr<<1))){
        WriteRegister(STATUS, (1<<6));
        return 1;
    }
    return 0;
}

/*------------------------------------------------- Transmit -----
|  Funkcija Transmit
|
|  Pielietojums:  Si funkcija sanem datus izmantojot nRF24L01
|
|  Parametri:
|      uint8_t *data (OUT) -- Saja parametra ievada raditaju uz masivu kur sanemt datus.
|      Sim masivam ir jabut 32 garam.
|
*-------------------------------------------------------------------*/
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