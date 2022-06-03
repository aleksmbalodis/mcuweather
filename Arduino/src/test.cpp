#include "DHT.h"

#define Delay 500 // Delay
#define Vin 5 // V 
#define Res 10000 //Ohm
#define DHTTYPE DHT11
#define DHTPIN 2

const int sensPin = A0;
int RawVal; // Analog value from the sensor
int LuxVal; //Lux value

DHT dht(DHTPIN, DHTTYPE);

int toLum(int raw){
  // Conversion rule
  float Vout = float(raw) * (Vin / float(1023));// Conversion analog to voltage
  float RLDR = (Res * (Vin - Vout))/Vout; // Conversion voltage to resistance
  int phys=500/(RLDR/1000); // Conversion resitance to lumen
  return phys;
}

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {

  RawVal = analogRead(sensPin);
  LuxVal=toLum(RawVal);

  float humidity = dht.readHumidity();
  float temp = dht.readTemperature();

  if (isnan(humidity) || isnan(temp)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  dht.computeHeatIndex(temp, humidity, false);

  Serial.print(F("Mitrums: "));
  Serial.print(humidity);
  Serial.print(F("%  Temperatura: "));
  Serial.print(temp);
  Serial.print(F("°C "));
  Serial.print("Sensora vertiba ");
  Serial.print(RawVal); // the analog reading
  Serial.print(" Spilgtums = ");
  Serial.print(LuxVal); // the analog reading
  Serial.println(" lum"); // the analog reading
  delay(Delay);
}
