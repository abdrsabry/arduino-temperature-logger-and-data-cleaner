#include <DHT.h>

// ---------- USER SETTINGS ----------
#define DHTPIN 7          // DHT data pin
#define DHTTYPE DHT11     // change to DHT22 if you have it
const int LDR_PIN = A0;   // LDR divider output
const int LED_PIN = 9;    // optional: status LED

// Light auto-calibration
int lightMin = 1023, lightMax = 0;

// Simple smoothing (exponential moving average)
float tempEMA = NAN, humEMA = NAN, lightEMA = NAN;
const float ALPHA = 0.15f; // 0..1 (higher = snappier)
const unsigned long SAMPLE_MS = 1000;

DHT dht(DHTPIN, DHTTYPE);
unsigned long lastSample = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(LDR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("ms,temp_c,humidity,light_pct");
}

void loop() {
  unsigned long now = millis();
  if (now - lastSample < SAMPLE_MS) return;
  lastSample = now;

  // --- DHT read
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) { delay(50); h = dht.readHumidity(); t = dht.readTemperature(); }

  // --- LDR read (0..1023)
  int lraw = analogRead(LDR_PIN);

  // track min/max for auto range
  if (lraw < lightMin) lightMin = lraw;
  if (lraw > lightMax) lightMax = lraw;

  int lcon = constrain(lraw, lightMin, lightMax);
  float lightPct = 0.0f;
  if (lightMax > lightMin) {
    lightPct = map(lcon, lightMin, lightMax, 0, 100); // 0 = darkest seen, 100 = brightest seen
  }

  // smooth
  if (isnan(tempEMA)) { tempEMA = t; humEMA = h; lightEMA = lightPct; }
  else {
    tempEMA  = ALPHA * t        + (1 - ALPHA) * tempEMA;
    humEMA   = ALPHA * h        + (1 - ALPHA) * humEMA;
    lightEMA = ALPHA * lightPct + (1 - ALPHA) * lightEMA;
  }

  // optional LED: on if dark
  digitalWrite(LED_PIN, (lightEMA < 30) ? HIGH : LOW);

  // CSV output
  Serial.print(now); Serial.print(',');
  Serial.print(isnan(tempEMA) ? 0 : tempEMA, 1); Serial.print(',');
  Serial.print(isnan(humEMA) ? 0 : humEMA, 1);  Serial.print(',');
  Serial.println(isnan(lightEMA) ? 0 : lightEMA, 0);
}
