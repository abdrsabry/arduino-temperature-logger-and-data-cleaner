# Python Data Cleaner for Lab Reports
Reads a CSV with columns `ms,temp_c`, applies a rolling mean, and outputs:
- `cleaned_data.csv`
- `temp_plot.png` (raw vs smoothed)

## Quick start (local)
```bash
pip install pandas matplotlib
python data_cleaner.py --in sample_data.csv --out cleaned_data.csv --window 10
