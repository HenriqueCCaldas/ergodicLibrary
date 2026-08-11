import os
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

# Doubling map phase space animation. Phase space [0,1) wraps under mod 1,
# so it is topologically a circle: x -> angle = 2*pi*x. A small arc of
# points is iterated under T(x) = 2x mod 1 and plotted each step. The arc's
# width doubles every iteration until it wraps the whole circle and folds
# back on itself -- that doubling *is* the Lyapunov exponent:
# width_n ~ width_0 * exp(n * ln 2).

N_POINTS = 150
N_COLORS = 3    # points are bucketed into this many colors, not one per point
WIDTH0 = 0.005   # initial cluster width -- wide enough to read as a visible arc, not a dot
X0 = 0.2         # cluster center (matches x0 used elsewhere in the project)
N_FILL_FRAMES = int(np.ceil(np.log2(1.0 / WIDTH0))) + 1  # iterations to wrap the whole circle
N_TAIL_FRAMES = 60  # extra frames of pure mixing after the circle is filled
N_FRAMES = N_FILL_FRAMES + N_TAIL_FRAMES

# Points are laid out in order along the initial arc (not randomly) and keep a
# fixed, per-point color from a small palette, bucketed by position along the
# arc. Since T is applied elementwise, each block's color still marks "where
# did this piece of the original arc end up" -- just coarser than one hue per
# point.
x = X0 + np.linspace(0.0, WIDTH0, N_POINTS)
palette = plt.cm.hsv(np.linspace(0.0, 1.0, N_COLORS, endpoint=False))
colors = palette[np.arange(N_POINTS) * N_COLORS // N_POINTS]

fig, ax = plt.subplots(figsize=(6, 6))
ax.set_xlim(-1.15, 1.15)
ax.set_ylim(-1.15, 1.15)
ax.set_aspect("equal")
ax.axis("off")

theta_circle = np.linspace(0, 2 * np.pi, 400)
ax.plot(np.cos(theta_circle), np.sin(theta_circle), color="lightgray", lw=1, zorder=1)

ax.scatter([1.0], [0.0], marker="+", s=25, color="gray", alpha=0.6, linewidths=1, zorder=3)
ax.annotate("x = 0", xy=(1.0, 0.0), xytext=(1.05, 0.0), fontsize=7, color="gray", alpha=0.7)

theta0 = 2 * np.pi * x
scat = ax.scatter(np.cos(theta0), np.sin(theta0), s=14, c=colors, edgecolors="none", zorder=2)
title = ax.set_title("")


def update(frame):
    global x
    if frame > 0:
        x = np.mod(2.0 * x, 1.0)
    theta = 2 * np.pi * x
    scat.set_offsets(np.column_stack([np.cos(theta), np.sin(theta)]))
    width = x.max() - x.min()
    title.set_text(
        "Doubling / Bit-shifting Map at iteration " f"n = {frame}\n"
        #"cluster width $\\approx$ {width:.2e}\n"
        "T(x) = 2x mod 1  " r"$\Rightarrow \; \lambda = \ln 2$"
        
    )
    return scat, title


anim = animation.FuncAnimation(fig, update, frames=N_FRAMES, interval=400, blit=False)

out_dir = "../data/doublingMap"
os.makedirs(out_dir, exist_ok=True)
out_path = os.path.join(out_dir, "phase_space_animation.gif")
anim.save(out_path, writer=animation.PillowWriter(fps=4))
plt.close()
print(f"Saved to {out_path}")
