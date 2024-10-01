import numpy as np
from math import log2

def naloga3(vhod: list, n: int) -> tuple[list, str]:
    """
    Izvedemo dekodiranje binarnega niza `vhod`, zakodiranega 
    z razsirjenim Hammingovim kodom dolzine `n` in poslanega 
    po zasumljenem kanalu.
    Nad `vhod` izracunamo vrednost `crc` po standardu CRC-8/CDMA2000.

    Parameters
    ----------
    vhod : list
        Sporocilo y, predstavljeno kot seznam bitov (stevil tipa int) 
    n : int
        Stevilo bitov v kodni zamenjavi
    
    Returns
    -------
    (izhod, crc) : tuple[list, str]
        izhod : list
            Odkodirano sporocilo y (seznam bitov - stevil tipa int)
        crc : str
            Vrednost CRC, izracunana nad `vhod`. Niz dveh znakov.
    """

    crc = np.int8(0xFF)

    m = int(log2(n) + 1)
    k = n - m

    table = []
    ntable = []

    for x in vhod:
        crc = calculateCRC(x, crc)
        ntable.append(x)
        if len(ntable) == n:
            table.append(ntable)
            ntable = []

    #get total parity bit
    ptable = []
    for x in table:
        p = 0
        for y in x:
            p ^= y
        ptable.append(p)
   
    table = np.array(table)
    table = np.delete(table, table.shape[1] - 1, 1)

    #make HL
    numlist = []
    powoftwo = 1
    for st in range(1,n):
        if st == powoftwo:
            powoftwo *= 2
            continue
        numlist.append(st)
    while powoftwo > 1:
        powoftwo >>= 1
        numlist.append(powoftwo)
    
    HL = []
    for x in numlist:
        row = bin(x)[2:].zfill(m-1)
        row_new = []
        for y in row:
            row_new.append(int(y))
        HL.append(row_new)
    HL = np.array(HL)

    outtable = []
    for row in table:
        rett = []
        for j in range(0, len(HL[0])):
            el = 0
            for i in range(0, len(row)):
                el ^= row[i] * HL[i][j]
            rett.append(el)
        outtable.append(rett)

    s = np.array(outtable)

    snum = []
    for x in s:
        num = 0
        for bit in x:
            num = num * 2
            num = num + (int(bit) % 2)
        snum.append(num)

    table = table.tolist()
    for i in range(0, len(ptable)):
        row = table[i]
        if ptable[i] != 0 and snum[i] != 0:
            #change bit s in row
            index = numlist.index(snum[i])
            row[index] ^= 1
            
    
    
    izhod = []
    i = 0
    for x in table:
        for appender in range(0, k, 1):
            izhod.append(table[i][appender])
        i = i + 1

    crc = hex(crc)[2:]
    crc = crc.upper()

    return (izhod, crc)

def compare(HL, s):
    for i in range(0,HL.shape[0]):
        if np.array_equal(HL[[i],:], np.broadcast_to(s,HL[[1],:].shape)):
            return i

def calculateCRC(x, crc):
    power = pow(2,7)
    last = np.int8((crc & power) / power) ^ x
    if last == 1:
        crc = (crc << 1) ^ 0x9B
    else:
        crc = crc << 1

    crc = (crc & 0xFE) + last
    return crc