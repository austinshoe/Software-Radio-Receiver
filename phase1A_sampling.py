import numpy as np
import matplotlib.pyplot as plt

f_s = 10000
f = 1000
a = 1
phi = 0
duration = 0.01

t = np.arange(0, duration, 1 / f_s) # discrete time samples from 0 to duration, with a step side of 1/f_s

y = np.sin(2 * np.pi * f * (t-phi))

plt.plot(t, y)
plt.xlabel("Time (seconds)")
plt.ylabel("Amplitude")
plt.title(str(f) + " Hz Sine Wave with Sampling")
plt.grid()
plt.show()

print("Sampling frequency:" + str(f_s))
print("Signal frequency:" + str(f))
print("Samples per second:" + str(f_s))
print("Samples per cycle:" + str(f_s / f))
print("Period:" + str(1 / f))
print("Amplitude:" + str(a))
print("Phase:" + str(phi))