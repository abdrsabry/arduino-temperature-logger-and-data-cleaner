```python
import argparse
import pandas as pd
import matplotlib.pyplot as plt

def main():
 p = argparse.ArgumentParser(description="Clean and plot Arduino temperature logs (ms,temp_c).")
 p.add_argument("--in", dest="infile", default="sample_data.csv")
 p.add_argument("--out", dest="outfile", default="cleaned_data.csv")
 p.add_argument("--window", type=int, default=10, help="rolling window (samples)")
 args = p.parse_args()

 df = pd.read_csv(args.infile)
 if not {"ms","temp_c"}.issubset(df.columns):
     raise ValueError("CSV must have columns: ms,temp_c")

 df["temp_c_smooth"] = df["temp_c"].rolling(window=args.window, min_periods=1).mean()
 df.to_csv(args.outfile, index=False)

 plt.figure(figsize=(8,4))
 plt.plot(df["ms"]/1000.0, df["temp_c"], label="raw")
 plt.plot(df["ms"]/1000.0, df["temp_c_smooth"], label=f"rolling mean ({args.window})")
 plt.xlabel("time (s)")
 plt.ylabel("temperature (°C)")
 plt.title("Arduino Temperature Log")
 plt.legend()
 plt.tight_layout()
 plt.savefig("temp_plot.png", dpi=150)

if __name__ == "__main__":
 main()
