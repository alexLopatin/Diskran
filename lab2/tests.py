import random

for i in range(1000, 11000, 1000):
    file = open('tests/test'+str(i)+'.txt','w')
    for k in range(1, i + 1):
        file.write('+ ')
        for j in range(1, random.randint(2,100)):
            file.write(str(chr(random.randint(97, 122))))
        file.write(' ' + str(random.randint(1,1000000)))
        file.write('\n')
    file.write("! Save tests/database" + str(i) + ".txt")
    file.close()