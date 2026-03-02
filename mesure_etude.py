import serial
import statistics as stats

import matplotlib.pyplot as plt

ser = serial.Serial("/dev/ttyUSB0", 115200)

dataX = [i for i in range(0, 66000, 500)]
dataVide=[]
dataBois=[]
dataPlastique=[]
dataMetal=[]
dataVerre=[]

def computeData(data, name) :
    print(name)
    for i in range(0, 66000, 500) :
        r = stats.mean(list(map(int, ser.readline().decode('utf-8')[:-1].split(',')[:-1])))
        data.append(r)
        print(r)

    print(data)
    plt.plot(dataX, data, label = name)

#computeData(dataVide, "0")

computeData(dataBois, "1")
computeData(dataPlastique, "2")
computeData(dataMetal, "3")
computeData(dataVerre, "4")

plt.xlabel("Measure time")
plt.ylabel("touchRead() readout")
plt.title("Evolution of touchRead() on glass with multiple participants")
plt.legend(loc="upper left")
plt.show()
