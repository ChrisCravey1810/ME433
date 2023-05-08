import matplotlib.pyplot as plt
import numpy as np
import csv

t = [] # column 0
data1 = [] # column 1
data2 = [] # column 2

rolling_avg = True #if 1, only plot data

with open('sigD.csv') as f:
    # open the csv file
    reader = csv.reader(f)
    for row in reader:
        # read the rows 1 one by one
        t.append(float(row[0])) # leftmost column
        data1.append(float(row[1])) # second column
        #data2.append(float(row[2])) # third column
    

    
n = len(data1) # length of the signal
k = np.arange(n)
Fs = n/t[-1] # sample rate
print("sample rate: ",Fs)
T = n/Fs
frq = k/T # two sides frequency range
frq = frq[range(int(n/2))] # one side frequency range
Y = np.fft.fft(data1)/n # fft computing and normalization
Y = Y[range(int(n/2))]




if rolling_avg == True:
    
    X = 25 # Number of points to rolling average over
    averages = np.zeros(n)  #Array to store averaged data
    
    
    for i in range(n):
        if i >= X:
            avg = np.sum(data1[i-X:i])/X  #Calculate average
            averages[i] = avg     #Store average. Note, first X entries are 0
    
    fig, (ax1, ax2) = plt.subplots(2, 1)
    ax1.title.set_text(str("Signal V. Time with " + str(X) + " rolling average"))
    ax1.plot(t,data1,'black')
    ax1.plot(t,averages, 'r')
    ax1.set_xlabel('Time')
    ax1.set_ylabel('Amplitude')
    ax2.loglog(frq,abs(Y),'black') # plotting the fft
    ax2.set_xlabel('Freq (Hz)')
    ax2.set_ylabel('|Y(freq)|')
    plt.show()
    


    
    
    
