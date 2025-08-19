Smart Environment Monitor, **Simulation Mode**
Logs ms,temp_c,humidity,light_pct as CSV at 1 Hz. Uses EMA smoothing and PWM LEDs (D9 green, D10 red) to visualize “light.”
Hardware that was used: Arduino Uno + 2 LEDs + 2×220Ω resistors.
Planned upgrade: Plug in DHT11 (temp/humidity) and LDR (light) to switch from simulated signals to real sensors without changing the logging pipeline.
