import random
size = 100;
for i in range(1, 11, 1):
    countOfEdges = 0
    edges = []
    file = open('tests/test'+str(i)+'.txt','w')
    file.write(str(size*i) + ' ')
    for j in range(1, size*i, 1):
        for k in range(j + 1, size*i, 1):
            r = random.randint(1, 4)
            if (r == 1) :
                edges.append(str(j) + ' ' + str(k))
                countOfEdges += 1
    file.write(str(countOfEdges) + '\n')
    for s in edges:
        file.write(s + '\n')
    file.close()
    