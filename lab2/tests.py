import random

for i in range(10000, 360000, 10000):
    file = open('tests/test'+str(i)+'.txt','w')
    file.write(str(i)+' '+str(int(i/10))
            +'\n')
    for j in range(1, i):
        file.write(str(random.randint(-1000000,1000000))
            +'\n')
    for j in range(1, int(i/10)):
        file.write(str(random.randint(-1000000,1000000))
            +'\n')
    file.close()