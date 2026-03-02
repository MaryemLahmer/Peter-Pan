import numpy
import matplotlib.pyplot as plt

H = 8.7
R = 25/2
h_max = 19.2
h_min = 1.4

N=100

h_l = []
p_l = []
np_l = []

for i in range(N) :
    h = (h_min+i*(h_max-h_min)/(N-1))
    alpha = numpy.arcsin((h-H)/R)
    p = R*numpy.cos(alpha)*2*numpy.pi
    h_l.append(h)
    p_l.append(p/32)
    np_l.append(-p/32)

plt.plot(h_l, p_l)
plt.plot(h_l, np_l)
plt.plot([8.7], [3])
plt.fill_between(h_l, p_l, y2=np_l, color='blue')
plt.fill_between([8.7], [3], [-3], color='red')
plt.show()
