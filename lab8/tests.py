import random

for i in range(10000, 110000, 10000):
    file = open('tests/test'+str(i)+'.txt','w')
    file.write(str((i))+'\n')
    for j in range(1, i+1):
    	file.write(str((random.randint(1, 3)))+' ')
    file.close()