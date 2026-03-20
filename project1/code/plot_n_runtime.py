import csv
from collections import defaultdict

import matplotlib.pyplot as plt

def load_data():
    grouped = defaultdict(list)
    with open("benchmark_results.csv", "r",encoding="utf-8") as file:
        reader = csv.DictReader(file)
        for row in reader:
            n = int(row["N"])
            algorithm = row["Algorithm"]
            run_time = float(row["Duration (sec)"])
            grouped[algorithm].append((n, run_time))

    for algorithm in grouped:
        grouped[algorithm].sort(key=lambda x: x[0])

    return grouped


def plot_n_run_time(grouped):
    plt.figure(figsize=(9, 5.5), dpi=120)

    for algorithm, points in grouped.items():
        x = [p[0] for p in points]
        y = [p[1] for p in points]
        plt.plot(x, y, marker="o", linewidth=2, label=algorithm)

    plt.xlabel("N")
    plt.ylabel("run_time (sec per call)")
    plt.title("N-run_time of Four Search Algorithms")
    plt.grid(True, alpha=0.3)
    plt.legend()
    plt.yscale("log")

    plt.tight_layout()
    plt.savefig("n_run_time_plot.png")
    plt.show()


if __name__ == "__main__":
    data = load_data()
    plot_n_run_time(data)
