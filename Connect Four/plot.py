import numpy as np
import matplotlib.pyplot as plt

UCB1 = np.loadtxt('plot1.dat')
UCB2 = np.loadtxt('plot2.dat')

plt.figure(1)
plt.plot(UCB1)
plt.plot(UCB2)
#plt.title('UCB')
plt.legend(labels=['First player', 'Second player'],  loc='best')
plt.xlabel("Game Round")
plt.ylabel("UCB value")
plt.grid(True)
plt.show()
