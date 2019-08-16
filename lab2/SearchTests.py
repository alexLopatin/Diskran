import random

for i in range(1000, 11000, 1000):
    file = open('tests/test'+str(i)+'.txt','w')
    file.write("! Load tests/database" + str(i) + ".txt")
    for k in range(1, i + 1):
        for j in range(1, random.randint(2,100)):
            file.write(str(chr(random.randint(97, 122))))
        file.write('\n')
    file.close()