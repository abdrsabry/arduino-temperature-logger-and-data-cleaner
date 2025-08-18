# Python Data Cleaner for Lab Reports
This script is designed for cleaning and smoothing temperature logger data collected with Arduino, but works with any CSV file that has time and temperature columns. Reads a CSV with columns `ms,temp_c`, applies a rolling mean, and outputs:
- `cleaned_data.csv`
- `temp_plot.png` (raw vs smoothed)

## Quick start (local)

pip install pandas matplotlib
python data_cleaner.py --in sample_data.csv --out cleaned_data.csv --window 10

> The rolling mean smooths noisy sensor readings.  
> You can adjust the window size with `--window`.

