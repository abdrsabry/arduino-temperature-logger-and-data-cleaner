// Smart Environment Monitor (Simulation Mode)
// Logs ms,temp_c,humidity,light_pct and drives LEDs with PWM.
// No external sensors required. Ready to extend with DHT11 + LDR later.

// ---------- USER SETTINGS ----------
const unsigned long SAMPLE_MS = 1000; // sample period (ms)
const float ALPHA = 0.15f;            // EMA smoothing factor (0.05–0.3 good)

const int LED_GREEN = 9;   // PWM -> brighter when "light" is high
const int LED_RED   = 10;  // PWM -> brighter when "light" is low (inverse)

// ---------- State ----------
unsigned long lastSample = 0;
float tempEMA = NAN, humEMA = NAN, lightEMA = NAN;

// ---------- Helpers: simple signal generators ----------
float fakeTemp(unsigned long ms) {
  // base 24–26C with slow daily-like swing + small noise
  float t = 25.0 + 1.5 * sin( (ms / 60000.0) * TWO_PI );      // 1 cycle / minute
  t += (random(-30, 30) / 100.0);                             // ±0.30C noise
  return t;
}

float fakeHum(unsigned long ms) {
  // 45–65% with phase shift + noise
  float h = 55.0 + 10.0 * sin( (ms / 60000.0) * TWO_PI + 1.2 );
  h += (random(-50, 50) / 100.0);                             // ±0.50% noise
  // clamp to a sane range
  if (h < 30.0) h = 30.0;
  if (h > 85.0) h = 85.0;
  return h;
}

float fakeLightPct(unsigned long ms) {
  // 0–100% smoothly varying; add a little wobble
  float w = (sin( (ms / 30000.0) * TWO_PI ) * 0.5f + 0.5f) * 100.0f; // 0..100
  w += 3.0f * sin( (ms / 2000.0) * TWO_PI );                         // fast wobble
  if (w < 0) w = 0; if (w > 100) w = 100;
  return w;
}

float ema(float prev, float x) {
  if (isnan(prev)) return x;
  return ALPHA * x + (1.0f - ALPHA) * prev;
}

void setup() {
  randomSeed(analogRead(A0)); // seed RNG from floating pin
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
  while (!Serial) { ; } // for Leonardo/Native USB; harmless on Uno
  Serial.println("ms,temp_c,humidity,light_pct");
}

void loop() {
  unsigned long now = millis();
  if (now - lastSample < SAMPLE_MS) return;
  lastSample = now;

  // --- Simulated raw readings ---
  float tRaw = fakeTemp(now);
  float hRaw = fakeHum(now);
  float lRaw = fakeLightPct(now);

  // --- Smooth with EMA ---
  tempEMA  = ema(tempEMA,  tRaw);
  humEMA   = ema(humEMA,   hRaw);
  lightEMA = ema(lightEMA, lRaw);

  // --- LED output (PWM) ---
  // Green follows light; Red is inverse
  int g = map((int)round(lightEMA), 0, 100, 0, 255);
  int r = 255 - g;
  analogWrite(LED_GREEN, constrain(g, 0, 255));
  analogWrite(LED_RED,   constrain(r, 0, 255));

  // Heartbeat
  digitalWrite(LED_BUILTIN, (now / SAMPLE_MS) % 2);

  // --- CSV output ---
  Serial.print(now); Serial.print(",");
  Serial.print(tempEMA, 2); Serial.print(",");
  Serial.print(humEMA, 1);  Serial.print(",");
  Serial.println(lightEMA, 1);
}
