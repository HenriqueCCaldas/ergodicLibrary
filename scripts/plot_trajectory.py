import pandas as pd
import matplotlib.pyplot as plt
import os

data_dir = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "data")

# Iterate over all subfolders in data/
for map_name in os.listdir(data_dir):
    map_dir = os.path.join(data_dir, map_name)
    if not os.path.isdir(map_dir):
        continue

    trajectory_path = os.path.join(map_dir, "trajectory.csv")
    if not os.path.exists(trajectory_path):
        continue

    df = pd.read_csv(trajectory_path)
    coord_cols = [c for c in df.columns if c != "n"]
    dim = len(coord_cols)

    if dim >= 2:
        # 2D+ map: phase space (x0 vs x1) alongside each coordinate over time
        fig, axes = plt.subplots(1, 2, figsize=(12, 5))
        fig.suptitle(f"Orbit - {map_name}", fontsize=14)

        axes[0].plot(df["x0"], df["x1"], lw=0.6, marker=".", markersize=2, alpha=0.7)
        axes[0].scatter(df["x0"].iloc[0], df["x1"].iloc[0], color="red", zorder=3, label="x0")
        axes[0].set_title("Phase Space")
        axes[0].set_xlabel("x0")
        axes[0].set_ylabel("x1")
        axes[0].legend()

        for col in coord_cols:
            axes[1].plot(df["n"], df[col], lw=0.8, label=col)
        axes[1].set_title("Coordinates vs Iteration")
        axes[1].set_xlabel("n")
        axes[1].set_ylabel("value")
        axes[1].legend()
    else:
        # 1D map: just the single coordinate over time
        fig, ax = plt.subplots(figsize=(7, 5))
        fig.suptitle(f"Orbit - {map_name}", fontsize=14)
        ax.plot(df["n"], df["x0"], lw=0.8)
        ax.set_xlabel("n")
        ax.set_ylabel("x0")

    plt.tight_layout()
    out_path = os.path.join(map_dir, "trajectory_plot.png")
    plt.savefig(out_path, dpi=150)
    plt.close()
    print(f"Saved to {out_path}")
