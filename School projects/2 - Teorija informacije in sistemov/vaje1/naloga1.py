from collections import Counter
def naloga1 ( besedilo : str , p : int) -> float :
    """ Izracun povprecne nedolocenosti na znak
    Parameters
    ----------
    besedilo : str
    Vhodni niz
    A=a, izlocimo . , - ...
    p : int
    Stevilo poznanih predhodnih znakov : 0 , 1 , 2 ali 3.
    p = 0: H(X1)
    racunamo povprecno informacijo na znak abecede
    brez poznanih predhodnih znakov

    besedilo uredis: aB,.cCAb -> ABCCAB
    gres cez besedilo, zracunas posamezne verjetnosti das Vsota(-log2(pi))*pi = H(x)


    p = 1: H(X2|X1)
    racunamo povprecno informacijo na znak abecede
    pri enem poznanem predhodnemu znaku .

    H(X2|X1) = H(X1,X2) - H(X1)
    H(X1) - klices naloga1(X1,0)
    dobis pare vn: ABBABC -> AB,BB,BA,AB,BC
    za njih dobis verjetnosti: AB-> 2/5, BB -> 1/5, BA-> 1/5, BC-> 1/5
    to je (X1,X2)
    potem das Vsota(-log2(pi))*pi = H(x) nad tem


    p = 2: H(X3|X1 ,X2)
    racunamo povprecno informacijo na znak abecede
    pri dveh poznanih predhodnih znakih .

    H(X3|X1 ,X2) = H(X1,X2,X3) - H(X1,X2)
    (X1,X2,X3): ABBABC -> ABB,BBA,BAB,ABC -> ABB: 1/4,...


    p = 3: H(X4|X1 ,X2 ,X3)
    racunamo povprecno informacijo na znak abecede
    pri treh poznanih predhodnih znakih .
    Returns
    -------
    H : float
    Povprecna informacija na znak abecede z upostevanjem
    stevila poznanih predhodnih znakov ’p ’. V bitih .
    """
    str2 = ""
    for x in besedilo:
        if 65 <= ord(x) <= 90 or 97 <= ord(x) <= 122:
            str2 += x
    str2 = str2.upper()
    X1 = (list(str2))
    X12 = (list(zip(str2[:-1],str2[1:])))
    X123 = (list(zip(str2[:-1],str2[1:],str2[2:])))
    X1234 = (list(zip(str2[:-1],str2[1:],str2[2:],str2[3:])))

    if p == 0:
        return H(X1)
    elif p == 1:
        return H(X12) - H(X1)
    elif p == 2:
        return H(X123) - H(X12)
    elif p == 3:
        return H(X1234) - H(X123)
    return "nan"

def I(p):
    from math import log2
    return -log2(p)

def H(X):
    H = float(0)
    counter = Counter(X)
    f = {}
    skupi = 0
    for x in counter:
        f[x] = counter[x]
        skupi += counter[x]
    # p={}
    for x in f:
        #p[x] = f[x] / skupi
        H += I(f[x] / skupi) * f[x] / skupi
    return H