import random

for i in range(1, 11, 1):
    file = open('tests/test'+str(i)+'.txt','w')
    file.write(str((1000000*i)))
    file.close()