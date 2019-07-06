import random

for i in range(10000, 120000, 10000):
    file = open('tests/test'+str(i)+'.txt','w') 
    for j in range(1, i):
        file.write(str(random.randint(0,9))
            +chr(random.randint(65,90))
            +chr(random.randint(65,90))
            +chr(random.randint(65,90))
            +str(random.randint(0,9))
            +str(random.randint(0,9))
            +'\t'
            +str(random.randint(0,4294967295))
            +'\n')
    file.close()