# Arduino Temperature Logger

Two sensor options (start with TMP36, it needs no libraries).

## Option 1 — TMP36 (analog, simplest)
- TMP36 **Vout → A0**
- TMP36 **+ → 5V** (or 3.3V)
- TMP36 **– → GND**

Formula: **tempC = (voltage − 0.5) × 100**  
Serial at **9600 baud** prints:
ms,temp_c
1000,24.81
2000,24.94

## Option 2 — DS18B20 (digital, 1-Wire)
- **DQ → D2** with **4.7k pull-up** to Vcc
- **VDD → 5V (or 3.3V)**, **GND → GND**
(Requires OneWire + DallasTemperature libraries.)

## How to Run
1. Connect the sensor (start with TMP36).
2. Upload the code from `tmp36/temp_logger_tmp36.ino` to your Arduino.
3. Open the Serial Monitor at 9600 baud.
4. Copy the output to a CSV file (or pipe it directly if using Arduino IDE Serial Plotter).
