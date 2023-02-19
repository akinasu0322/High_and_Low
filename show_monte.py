import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import sys

args = sys.argv
N = int(args[1])
NMONTE = int(args[2])

# data:histdata
def show_hist(data):
    fig = plt.figure()
    ax1 = fig.add_subplot(111)
    n = len(data)
    x_axis = list(range(n))
    label = list(range(n))
    rects = ax1.bar(x_axis, data, tick_label=label, align="center", width=1.0, edgecolor="black", linewidth=0.5)
    ax1.set_title(f"montecarlo simuration(NMONTE={NMONTE})")
    ax1.bar_label(rects, padding=3)
    ax1.set_ylim(0,np.max(data)+NMONTE/50)
    ax1.set_ylabel("number of each score(times)")
    ax1.set_xlabel("score(times)")
    plt.savefig("monte_hist.png")

with open("montecarlo_result.csv", "r", encoding="SHIFT-JIS") as f:
    line = f.readline()
    raw = list(map(int, line.split(",")))
    line = f.readline()
    hist = list(map(int, line.split(",")))

result_fig = show_hist(hist)



    



