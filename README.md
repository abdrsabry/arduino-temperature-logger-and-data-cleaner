# Arduino Temperature Logger & Data Cleaner

Arduino temperature logger (TMP36/DS18B20) that streams **ms,temp_c** to CSV + a tiny Python cleaner to smooth and plot.  
**Flow:** hardware to data to analysis to documentation.

## Projects
1. **Arduino Temperature Logger** – log `(ms,temp_c)` over Serial at 9600 baud.
2. **Python Data Cleaner** – smooth and plot CSV, export `cleaned_data.csv` and `temp_plot.png`.

> This repo is intentionally small and beginner‑friendly. Replace the sample data with your own once you run the Arduino sketch.
