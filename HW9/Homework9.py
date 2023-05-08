import matplotlib.pyplot as plt
import numpy as np
import csv

t = [] # column 0
data1 = [] # column 1
data2 = [] # column 2


simple_plot = False 
rolling_avg = False 
IIR = False
FIR = True

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




if simple_plot == True:
    fig, (ax1, ax2) = plt.subplots(2, 1)
    ax1.plot(t,data1,'black')
    ax1.set_xlabel('Time')
    ax1.set_ylabel('Amplitude')
    ax2.loglog(frq,abs(Y),'black') # plotting the fft
    ax2.set_xlabel('Freq (Hz)')
    ax2.set_ylabel('|Y(freq)|')
    plt.show()
    





if rolling_avg == True:
    
    X = 100 # Number of points to rolling average over
    averages = np.zeros(n)  #Array to store averaged data
    
    
    for i in range(n):
        if i >= X:
            avg = np.sum(data1[i-X:i])/X  #Calculate average
            averages[i] = avg     #Store average. Note, first X entries are 0
    
    n_avg = len(averages) # length of the signal
    k_avg = np.arange(n)
    Fs = n/t[-1] # sample rate
    print("sample rate: ",Fs)
    T_avg = n_avg/Fs
    frq_avg = k_avg/T_avg # two sides frequency range
    frq_avg = frq_avg[range(int(n_avg/2))] # one side frequency range
    Y_avg = np.fft.fft(averages)/n_avg # fft computing and normalization
    Y_avg = Y_avg[range(int(n/2))]
    
    
    
    
    fig, (ax1, ax2) = plt.subplots(2, 1)
    ax1.title.set_text(str("Signal V. Time with " + str(X) + " rolling average"))
    ax1.plot(t,data1,'black')
    ax1.plot(t,averages, 'r')
    ax1.set_xlabel('Time')
    ax1.set_ylabel('Amplitude')
    ax2.loglog(frq,abs(Y),'black') # plotting the fft
    ax2.set_xlabel('Freq (Hz)')
    ax2.set_ylabel('|Y(freq)|')
    ax2.loglog(frq_avg, abs(Y_avg), 'r')
    plt.show()
    
    
    
    
if IIR == True:
    filt = []
    
    A = 0.95   #How much do you trust old data
    B = 0.05   #How much do you trust new data
    
    
    for i in range(n):
        if len(filt) == 0:
            filt.append(0)
        else:
            filt.append((filt[-1]*A) + (data1[i]*B) )
    
    n_avg = len(filt) # length of the signal
    k_avg = np.arange(n)
    Fs = n/t[-1] # sample rate
    print("sample rate: ",Fs)
    T_avg = n_avg/Fs
    frq_avg = k_avg/T_avg # two sides frequency range
    frq_avg = frq_avg[range(int(n_avg/2))] # one side frequency range
    Y_avg = np.fft.fft(filt)/n_avg # fft computing and normalization
    Y_avg = Y_avg[range(int(n/2))]
    
    
    title = str("Signal V. Time IIR (A,B)=(" + str(A) + "," + str(B) + ")")
    
    fig, (ax1, ax2) = plt.subplots(2, 1)
    ax1.title.set_text(title)
    ax1.plot(t,data1,'black')
    ax1.plot(t,filt, 'r')
    ax1.set_xlabel('Time')
    ax1.set_ylabel('Amplitude')
    ax2.loglog(frq,abs(Y),'black') # plotting the fft
    ax2.set_xlabel('Freq (Hz)')
    ax2.set_ylabel('|Y(freq)|')
    ax2.loglog(frq_avg, abs(Y_avg), 'r')
    plt.show()
    


if FIR == True:
    
    h = [
    0.000000000000000000,
    -0.000005808574635563,
    -0.000049743723609259,
    -0.000093013397707690,
    -0.000000000000000001,
    0.000296790891789754,
    0.000589360721165233,
    0.000427487215311701,
    -0.000465135576162150,
    -0.001661822005903757,
    -0.001992943687534286,
    -0.000391945719442743,
    0.002790046202986978,
    0.005227471292631383,
    0.003908856343528834,
    -0.002078053873879001,
    -0.009417065370407762,
    -0.011645095463143053,
    -0.003936120201181082,
    0.011399359017620575,
    0.023682896399972158,
    0.019902447804684129,
    -0.004486920207322515,
    -0.037599155217253113,
    -0.053634670115478733,
    -0.027112656724521709,
    0.048941006760945531,
    0.153343170915491378,
    0.244069687647286093,
    0.279983137289537443,
    0.244069687647286121,
    0.153343170915491378,
    0.048941006760945531,
    -0.027112656724521705,
    -0.053634670115478726,
    -0.037599155217253127,
    -0.004486920207322517,
    0.019902447804684129,
    0.023682896399972161,
    0.011399359017620583,
    -0.003936120201181083,
    -0.011645095463143062,
    -0.009417065370407762,
    -0.002078053873879002,
    0.003908856343528840,
    0.005227471292631386,
    0.002790046202986982,
    -0.000391945719442743,
    -0.001992943687534285,
    -0.001661822005903757,
    -0.000465135576162150,
    0.000427487215311701,
    0.000589360721165232,
    0.000296790891789754,
    -0.000000000000000001,
    -0.000093013397707690,
    -0.000049743723609259,
    -0.000005808574635563,
    0.000000000000000000,
]
    
    
    X = len(h) # Number of FIR coefficients
    averages = np.zeros(n)  #Array to store averaged data
    
    
    for i in range(n):
        if i >= X:
            val = 0
            for j in range(X):
                val += (data1[i-j])*h[j]  #Calculate average
            averages[i] = val     #Store average. Note, first X entries are 0
    
    n_avg = len(averages) # length of the signal
    k_avg = np.arange(n)
    Fs = n/t[-1] # sample rate
    print("sample rate: ",Fs)
    T_avg = n_avg/Fs
    frq_avg = k_avg/T_avg # two sides frequency range
    frq_avg = frq_avg[range(int(n_avg/2))] # one side frequency range
    Y_avg = np.fft.fft(averages)/n_avg # fft computing and normalization
    Y_avg = Y_avg[range(int(n/2))]
    
    
    
    
    fig, (ax1, ax2) = plt.subplots(2, 1)
    ax1.title.set_text(str("Signal V. Time with " + str(X) + " FIR"))
    ax1.plot(t,data1,'black')
    ax1.plot(t,averages, 'r')
    ax1.set_xlabel('Time')
    ax1.set_ylabel('Amplitude')
    ax2.loglog(frq,abs(Y),'black') # plotting the fft
    ax2.set_xlabel('Freq (Hz)')
    ax2.set_ylabel('|Y(freq)|')
    ax2.loglog(frq_avg, abs(Y_avg), 'r')
    plt.show()
    
    

    
    
    
