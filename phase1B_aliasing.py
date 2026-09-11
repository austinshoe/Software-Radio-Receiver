import numpy as np
import matplotlib.pyplot as plt

fs = 10000
duration = 0.005

frequencies = [4000, 6000]

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

# We see that the plots look the same, with just a phase shift as a distinguishing feature. 