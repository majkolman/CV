def naloga2(vhod: list, nacin: int) -> tuple[list, float]:
    """
    Izvedemo kodiranje ali dekodiranje z algoritmom LZW.
    Zacetni slovar vsebuje vse 8-bitne vrednosti (0-255). 
    Najvecja dolzina slovarja je 4096.

    Parameters
    ----------
    vhod : list
        Seznam vhodnih znakov: bodisi znaki abecede
        (ko kodiramo) bodisi kodne zamenjave 
        (ko dekodiramo).
    nacin : int 
        Stevilo, ki doloca nacin delovanja: 
            0: kodiramo ali
            1: dekodiramo.

    Returns
    -------
    (izhod, R) : tuple[list, float]
        izhod : list
            Ce je nacin = 0: "izhod" je kodiran "vhod"
            Ce je nacin = 1: "izhod" je dekodiran "vhod"
        R : float
            Kompresijsko razmerje
    """
    izhod = []
    if nacin == 0:
        kodiranje(vhod, izhod)
        R = float((len(vhod)*8)/(len(izhod)*12))
    else:
        dekodiranje(vhod, izhod)
        R = float((len(izhod)*8)/(len(vhod)*12))
    
    return (izhod, R)


def kodiranje(vhod, izhod):
    st=0
    slovar = dict()
    MAX_VNOSOV = 4096
    st_vnosov = 256
    for x in range(st_vnosov):
        slovar[chr(x)] = x

    N = ""
    for z in vhod:
        st+=1
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

