import numpy as np
import matplotlib.pyplot as plt

# Phase 1A
# Learning Nyquist Boundaries, Aliasing

fs = 10000
duration = 0.005

frequencies = [1000, 3000, 4000, 4900, 5100, 6000, 7000, 9000]

for f in frequencies:
    t = np.arange(0, duration, 1/fs)
    x = np.sin(2 * np.pi * f * t)

    plt.figure()
    plt.stem(t, x)
    plt.title(f"{f} Hz signal sampled at {fs} Hz")
    plt.xlabel("Time (seconds)")
    plt.ylabel("Amplitude")
    plt.grid()

plt.show()