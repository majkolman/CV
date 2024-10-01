def naloga2_tekma(dat_vhod: str, dat_izhod: str, nacin: int) -> float:
    """
    Izvedemo kodiranje ali dekodiranje datoteke z algoritmom LZW
    in morebitnimi izboljsavami.

    Parameters
    ----------
    dat_vhod : str
        Pot do vhodne datoteke

    dat_izhod : str
        Pot do izhodne datoteke;
        ce datoteka se ne obstaja, jo ustvari; ce obstaja, jo povozi.
    
    nacin : int 
        Nacin delovanja: kodiramo (0) ali dekodiramo (1).

    Returns
    -------
    R : float
        Kompresijsko razmerje
    """
    vhod_dat = open(dat_vhod, "rb")
    izhod_dat = open(dat_izhod, "wb")

    vhod = []
    izhod = []

    

    if nacin == 0:
        while 1:
            char = vhod_dat.read(1)
            char = char.decode("ascii")
            if not char:
                break
            else:
                vhod.append(char)
        kodiranje(vhod, izhod)
        R = float((len(vhod)*8)/(len(izhod)*12))
        
    else:
        while 1:
            char = vhod_dat.read(1)
            if not char:
                break
            else:
                vhod.append(ord(char))
        dekodiranje(vhod, izhod)
        R = float((len(izhod)*8)/(len(vhod)*12))

    for i in izhod:
        izhod_dat.write(bytes(i))

    vhod_dat.close()
    izhod_dat.close()
    print(R)
    return R

def kodiranje(vhod, izhod):
    slovar = dict()
    MAX_VNOSOV = 4096
    st_vnosov = 256
    for x in range(st_vnosov):
        slovar[chr(x)] = x

    N = ""
    for z in vhod:
        temp = N + z
        if (N + z) in slovar:
            N = temp
        else:
            izhod.append(slovar[N])
            if st_vnosov < MAX_VNOSOV:
                slovar[temp] = st_vnosov
                st_vnosov += 1
                
            N = z
        
    izhod.append(slovar[N])
    return izhod


def dekodiranje(vhod, izhod):
    #definiraj slovar
    slovar = dict()
    MAX_VNOSOV = 4096
    st_vnosov = 256
    for x in range(st_vnosov):
        slovar[x] = chr(x)

    #v slovarju poisci N
    N = slovar[vhod[0]]
    #izpisi N
    izhod.append(N)
    #K=N
    K = ""
    K = N
    #ponavljaj dokler so kodne zamenjave na vhodu
    #preberi kodno zamenjavo k
    for k in vhod[1::]:
        #ce je k v slovarju
        if (k in slovar):
            #v slovarju poisci pripadajoci niz N
            N = slovar[k]
        #sicer
        else:
            #N = K+K[0]
            N = K+K[0]
        #izpisi N
        izhod.extend(N)
        #v slovar dodaj K+N[0]
        if st_vnosov < MAX_VNOSOV:
            slovar[st_vnosov] = K+N[0]
            st_vnosov += 1
        #K = N
        K = N
    return izhod

import sys
st = 0
for i in sys.argv:
    st += 1
if st != 4:
    print("error")
    exit()
naloga2_tekma(sys.argv[1], sys.argv[2], int(sys.argv[3]))
