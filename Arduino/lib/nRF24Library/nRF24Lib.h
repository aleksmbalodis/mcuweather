#include <Arduino.h>
#include <SPI.h>

/* Registri*/
#define CONFIG      0x00
#define EN_AA       0x01
#define EN_RXADDR   0x02
#define SETUP_AW    0x03
#define SETUP_RETR  0x04
#define RF_CH       0x05
#define RF_SETUP    0x06
#define STATUS      0x07
#define OBSERVE_TX  0x08
#define CD          0x09
#define RX_ADDR_P0  0x0A
#define RX_ADDR_P1  0x0B
#define RX_ADDR_P2  0x0C
#define RX_ADDR_P3  0x0D
#define RX_ADDR_P4  0x0E
#define RX_ADDR_P5  0x0F
#define TX_ADDR     0x10
#define RX_PW_P0    0x11
#define RX_PW_P1    0x12
#define RX_PW_P2    0x13
#define RX_PW_P3    0x14
#define RX_PW_P4    0x15
#define RX_PW_P5    0x16
#define FIFO_STATUS 0x17
#define DYNPD	    0x1C
#define FEATURE	    0x1D

/* Komandas */
#define R_REGISTER    0x00
#define W_REGISTER    0x20
#define REGISTER_MASK 0x1F
#define ACTIVATE      0x50
#define R_RX_PL_WID   0x60
#define R_RX_PAYLOAD  0x61
#define W_TX_PAYLOAD  0xA0
#define W_ACK_PAYLOAD 0xA8
#define FLUSH_TX      0xE1
#define FLUSH_RX      0xE2
#define REUSE_TX_PL   0xE3
#define NOP           0xFF

class nRF24Lib{

    public:
        
    uint8_t CSNpin;
    uint8_t CSpin;

/*------------------------------------------------- nRF24Lib -----
|  Konstruktors nRF24Lib
|
|  Pielietojums: Izmanto, lai iestatitu CSN un CS pin, kas tiks izmantots biblioteka velak.
|
|  Parametri:
|      uint8_t CSN (IN) -- Saja parametra ievada Arduino Chip Select Not kontakta numuru
|      uint8_t CS (IN) -- Saja parametra ievada Arduino Chip Select kontakta numuru
|
*-------------------------------------------------------------------*/
    nRF24Lib(uint8_t CSN, uint8_t CS){
            CSNpin = CSN;
            CSpin = CS;
            pinMode(CSN, OUTPUT);
            pinMode(CS, OUTPUT);
        };

// Seit ir aprakstitas visas bibliotekas funkcijas
// un funkciju parametri

    void CS_Select(void);

    void CS_UnSelect(void);

    void CE_Enable(void);

    void CE_Disable(void);

    void WriteRegister(uint8_t reg, uint8_t data);

    void WriteRegisterMulti(uint8_t reg, uint8_t * data, int size);

    uint8_t ReadRegister(uint8_t reg);

    void ReadRegisterMulti(uint8_t reg, uint8_t * data, int size);

    void SendCommand(uint8_t cmd);

    void Init(void);

    void TX_Mode(uint8_t *address, uint8_t ch);

    uint8_t Transmit(uint8_t *dati);

    void RX_Mode(uint8_t *address, uint8_t ch);

    uint8_t IsDataAvailable(int pipenr);

    void Receive(uint8_t *data);
};