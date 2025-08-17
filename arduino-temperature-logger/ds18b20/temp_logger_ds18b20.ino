// Arduino Temperature Logger — DS18B20 (1-Wire)
// Libraries: OneWire, DallasTemperature (install via Library Manager)

#include <OneWire.h>
#include <DallasTemperature.h>

const int ONE_WIRE_BUS = 2; // D2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  sensors.begin();
  Serial.println("ms,temp_c");
}

void loop() {
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  unsigned long ms = millis();
  Serial.print(ms);
  Serial.print(",");
  Serial.println(tempC, 2);
  delay(1000);
}
