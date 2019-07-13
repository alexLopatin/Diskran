import matplotlib.pyplot as plt 
import numpy as np

f=open("time.txt")
x= []
for i in range(1, 11, 1):
    x.append(1000000*i)
values = np.array([[float(x.split(' ')[0]), float(x.split(' ')[1])] for x in f] );
y = values[:,0]


plt.plot(x, y) 

plt.xlabel('Количество строк') 
plt.ylabel('Время') 
plt.grid(True)
plt.show() 
y = values[:,1]
plt.plot(x, y) 
plt.xlabel('Количество строк') 
plt.ylabel('Килобайт') 
plt.grid(True)
plt.show() 