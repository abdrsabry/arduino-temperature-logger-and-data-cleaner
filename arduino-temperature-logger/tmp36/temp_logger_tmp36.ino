// Arduino Temperature Logger — TMP36 (analog)
// Wiring: TMP36 Vout -> A0, + -> 5V (or 3.3V), - -> GND

const int TMP_PIN = A0;
const float VREF = 5.0; // change to 3.3 if your board runs at 3.3V

void setup() {
  Serial.begin(9600);
  while(!Serial) {;}
  Serial.println("ms,temp_c");
}

void loop() {
  int raw = analogRead(TMP_PIN);
  float voltage = (raw * VREF) / 1023.0;
  float tempC = (voltage - 0.5) * 100.0; // TMP36 transfer function
  unsigned long ms = millis();
  Serial.print(ms);
  Serial.print(",");
  Serial.println(tempC, 2);
  delay(1000);
}
