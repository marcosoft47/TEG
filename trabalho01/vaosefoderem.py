from numpy import size


mTeste = [[0,1,0,0,0,0],
        [1,0,1,1,0,0],
        [0,1,0,1,0,0],
        [0,1,1,0,0,0],
        [0,0,0,0,0,1],
        [0,0,0,0,1,0]]

visitados = [[0,0,0,0,0,0],
             [0,0,0,0,0,0],
             [0,0,0,0,0,0],
             [0,0,0,0,0,0],
             [0,0,0,0,0,0],
             [0,0,0,0,0,0]]

fila = []
i = iV = jV = 0
parar = False
nrows = 6
while i < nrows:
    visitados[iV][jV] = i
    for j in range(i,nrows):
        if mTeste[i][j] == 1 and not j in fila:
            print(f"i: {i}   j: {j}")
            fila.append(j)
    jV += 1
    print(f"iV: {iV}   jV: {jV}")
    try:
        i = fila.pop(0)
    except:
        iV += 1
        jV = 0
        i = 0
        while not parar:
            i += 1
            if not (i in visitados):
                parar = True
        parar = False

       
print(visitados)