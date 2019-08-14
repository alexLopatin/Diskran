import random

for i in range(10000, 110000, 10000):
    file = open('tests/test'+str(i)+'.txt','w')
    for j in range(1, i+1):
    	file.write(str(chr(random.randint(97, 122))))
    file.close()