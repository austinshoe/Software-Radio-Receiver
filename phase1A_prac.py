import numpy as np
import matplotlib.pyplot as plt

# Phase 1A
# Learning matplotlib, Relearning Waves
# Also a review on Python

frequency = float(input())

duration = float(input())

amplitude = float(input())

phase = float(input())

x = np.linspace(0, duration, 1000)

y = amplitude * np.sin(frequency * (x - phase) * np.pi * 2)

plt.plot(x, y)
plt.xlabel("Time (seconds)")
plt.ylabel("Amplitude")
plt.title(str(frequency) + " Hz Sine Wave")
plt.grid()
plt.show()

f_s = float(input()) # sampling frequency
t_s = 1 / f_s # time between samples

x_val_s = np.arange(0, duration, t_s) # sample values
y_s = amplitude * np.sin(frequency * (x_val_s - phase) * np.pi * 2)
plt.plot(x_val_s, y_s)
plt.xlabel("Time (seconds)")
plt.ylabel("Amplitude")
plt.title(str(frequency) + " Hz Sine Wave Samples")
plt.grid()
plt.show()

