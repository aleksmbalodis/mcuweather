#include <nRF24Lib.h>
#include <DHT.h>

#define CSN 10
#define CS 9
#define Delay 500 // Delay
#define Vin 5 // V 
#define Res 10000 //Ohm
#define DHTTYPE DHT22
#define DHTPIN 2

nRF24Lib txradio(CSN, CS);
DHT dht(DHTPIN, DHTTYPE);

const int sensPin = A0;
int RawVal; // Analog value from the sensor
int LuxVal; //Lux value
uint8_t TxAddress[] = {0xEE,0xDD,0xCC,0xBB,0xAA};
uint8_t TxDati[32] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32 };

int toLum(int raw){
  // Conversion rule
  float Vout = float(raw) * (Vin / float(1023));// Conversion analog to voltage
  float RLDR = (Res * (Vin - Vout))/Vout; // Conversion voltage to resistance
  int phys=500/(RLDR/1000); // Conversion resitance to lumen
  return phys;
}

void setup(){
  //pinMode(9, OUTPUT);
  //pinMode(10, OUTPUT);
  Serial.begin(9600);
  dht.begin();
  SPI.begin();
  txradio.Init();
  txradio.TX_Mode(TxAddress, 10);
}

void loop(){
  RawVal = analogRead(sensPin);
  LuxVal = toLum(RawVal);

  float humidity = dht.readHumidity();
  float temp = dht.readTemperature();
  
  TxDati[1] = (int)temp;
  TxDati[2] = (int)humidity;
  TxDati[3] = LuxVal;

  if(txradio.Transmit(TxDati) == 1){
    Serial.println("OKKKKK");
  }

  Serial.print("Temp: ");
  Serial.print(TxDati[1]);
  Serial.print(" Humidity: ");
  Serial.print(TxDati[2]);
  Serial.print(" Lux: ");
  Serial.println(TxDati[3]);

  delay(1000);

}