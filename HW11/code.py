print("Hello World!")

import time
from ulab import numpy as np # to get access to ulab numpy functions
dt = 1.0/10000.0 # 10kHz
t = np.arange(0.0, ((1/10000)*1024), dt) # 10s
# a constant plus 100Hz and 1000Hz
s = 4.0 * np.sin(2 * np.pi * 100 * t) + 0.25 * np.sin(2 * np.pi * 1000 * t) + 3.0 * np.sin(2 * np.pi * 500 * t)

Fs = 10000 # sample rate
Ts = 1.0/Fs; # sampling interval
ts = np.arange(0,t[-1],Ts) # time vector
y = s # the data to make the fft from
n = len(y) # length of the signal
k = np.arange(n)
T = n/Fs
frq = k/T # two sides frequency range
frq = frq[range(int(n/2))] # one side frequency range
Y = np.fft.fft(y)
Y = Y[0]/n # fft computing and normalization
#Y = Y[range(int(n/2))]
#
print(Y)

for i in range(len(Y)):
    print("("+str(Y[i+1])+",)")
    time.sleep(0.01)
# Want to know all the functions available in numpy? In REPL type np. and press Tab.
