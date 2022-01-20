//Standarta bibliotekas 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Arduino bibliotekas
#include <Arduino.h>
#include <SPI.h>

//Biti
#define	BIT0	(1 << 0)
#define	BIT1	(1 << 1)
#define	BIT2	(1 << 2)
#define	BIT3	(1 << 3)
#define	BIT4	(1 << 4)
#define	BIT5	(1 << 5)
#define	BIT6	(1 << 6)
#define	BIT7	(1 << 7)

//Registru adreses
#define CONFIG 0x00
#define EN_AA 0x01
#define EN_RXADDR 0x02
#define SETUP_AR 0x03
#define SETUP_RETR 0x04
#define RF_CH 0x05
#define RF_SETUP 0x06
#define STATUS 0x07
#define OBSERVE_TX 0x08
#define RPD 0x09
#define RX_ADDR_P0 0x0A
#define RX_ADDR_P1 0x0B
#define RX_ADDR_P2 0x0C
#define RX_ADDR_P3 0x0D
#define RX_ADDR_P4 0x0E
#define RX_ADDR_P5 0x0F
#define TX_ADDR 0x10
#define RX_PW_P0 0x11
#define RX_PW_P1 0x12
#define RX_PW_P2 0x13
#define RX_PW_P3 0x14
#define RX_PW_P4 0x15
#define RX_PW_P5 0x16
#define FIFO_STATUS 0x17
#define DYNPD 0x1C
#define FEATURE 0x1D

// Registru biti
#define MASK_RX_DR  BIT6
#define MASK_TX_DS  BIT5
#define MASK_MAX_RT BIT4
#define EN_CRC      BIT3
#define CRCO        BIT2
#define PWR_UP      BIT1
#define PRIM_RX     BIT0
#define ENAA_P5     BIT5
#define ENAA_P4     BIT4
#define ENAA_P3     BIT3
#define ENAA_P2     BIT2
#define ENAA_P1     BIT1
#define ENAA_P0     BIT0
#define ERX_P5      BIT5
#define ERX_P4      BIT4
#define ERX_P3      BIT3
#define ERX_P2      BIT2
#define ERX_P1      BIT1
#define ERX_P0      BIT0
#define DYNPL_P5	 BIT5
#define DYNPL_P4	 BIT4
#define DYNPL_P3	 BIT3
#define DYNPL_P2	 BIT2
#define DYNPL_P1	 BIT1
#define DYNPL_P0	 BIT0
#define AW          BIT0
#define ARD         BIT4
#define ARC         BIT0
#define PLL_LOCK    BIT4
#define CONT_WAVE   BIT7
#define RF_DR       BIT3
#define RF_DR_LOW   BIT5
#define RF_DR_HIGH  BIT3
#define RF_PWR      BIT1
#define LNA_HCURR   BIT0
#define RX_DR       BIT6
#define TX_DS       BIT5
#define MAX_RT      BIT4
#define RX_P_NO     BIT1
#define TX_FULL     BIT0
#define PLOS_CNT    BIT4
#define ARC_CNT     BIT0
#define TX_REUSE    BIT6
#define FIFO_FULL   BIT5
#define TX_EMPTY    BIT4
#define RX_FULL     BIT1
#define RX_EMPTY    BIT0
#define EN_DPL      BIT2
#define EN_ACK_PAY  BIT1
#define EN_DYN_ACK  BIT0

// Bitu pozicijas
#define BITPOS_MASK_RX_DR  6
#define BITPOS_MASK_TX_DS  5
#define BITPOS_MASK_MAX_RT 4
#define BITPOS_EN_CRC      3
#define BITPOS_CRCO        2
#define BITPOS_PWR_UP      1
#define BITPOS_PRIM_RX     0
#define BITPOS_ENAA_P5     5
#define BITPOS_ENAA_P4     4
#define BITPOS_ENAA_P3     3
#define BITPOS_ENAA_P2     2
#define BITPOS_ENAA_P1     1
#define BITPOS_ENAA_P0     0
#define BITPOS_ERX_P5      5
#define BITPOS_ERX_P4      4
#define BITPOS_ERX_P3      3
#define BITPOS_ERX_P2      2
#define BITPOS_ERX_P1      1
#define BITPOS_ERX_P0      0
#define BITPOS_DYNPL_P5	 5
#define BITPOS_DYNPL_P4	 4
#define BITPOS_DYNPL_P3	 3
#define BITPOS_DYNPL_P2	 2
#define BITPOS_DYNPL_P1	 1
#define BITPOS_DYNPL_P0	 0
#define BITPOS_AW          0
#define BITPOS_ARD         4
#define BITPOS_ARC         0
#define BITPOS_PLL_LOCK    4
#define BITPOS_CONT_WAVE   7
#define BITPOS_RF_DR       3
#define BITPOS_RF_DR_LOW   5
#define BITPOS_RF_DR_HIGH  3
#define BITPOS_RF_PWR      1
#define BITPOS_LNA_HCURR   0
#define BITPOS_RX_DR       6
#define BITPOS_TX_DS       5
#define BITPOS_MAX_RT      4
#define BITPOS_RX_P_NO     1
#define BITPOS_TX_FULL     0
#define BITPOS_PLOS_CNT    4
#define BITPOS_ARC_CNT     0
#define BITPOS_TX_REUSE    6
#define BITPOS_FIFO_FULL   5
#define BITPOS_TX_EMPTY    4
#define BITPOS_RX_FULL     1
#define BITPOS_RX_EMPTY    0
#define BITPOS_EN_DPL      2
#define BITPOS_EN_ACK_PAY  1
#define BITPOS_EN_DYN_ACK  0

//Instrukcijas
#define R_REGISTER    0x00
#define W_REGISTER    0x20
#define REGISTER_MASK 0x1F
#define R_RX_PAYLOAD  0x61
#define W_TX_PAYLOAD  0xA0
#define FLUSH_TX      0xE1
#define FLUSH_RX      0xE2
#define REUSE_TX_PL   0xE3
#define R_RX_PL_WID   0x60
#define W_ACK_PAYLOAD 0xA8
#define W_TX_PAYLOAD_NOACK 0xB0
#define ACTIVATE		0x50
#define NOP           0xFF

void nRF24_RegisterWrite(uint8_t reg, uint8_t regbit, uint8_t val);
void nRF24_Init();
void nRF24_WriteTXData(uint8_t* pTXdata, uint8_t asize);
void nRF24_ENTXMode();
uint8_t * nRF24_ReadRXBuffer();