import numpy as np

# Ustvarimo sporocilo
z=np.array([1, 1, 0, 1], dtype=np.uint8)

# Ustvarimo generatorsko matriko oblike [I|B^T] 
B = np.array([[0, 1, 1, 1],[1, 0, 1, 1],[1, 1, 0, 1]], dtype=np.uint8)
G=np.concatenate((
                 np.eye(B.shape[1],dtype=np.uint8), 
                 B.transpose()),
                 axis=1)

# Generiramo kodno zamenjavo x
x=z.dot(G)
x=np.remainder(x,2)

# Izracunamo paritetni bit
parity = np.remainder(np.sum(x),2)

x=np.concatenate((x,np.array([parity],dtype=np.uint8)))

# Simuliramo napako v komunikacijskem kanalu
# Pokvarimo drugi bit kodne zamenjave 
e = np.zeros((1,8),dtype=np.uint8)
e[0,1] = 1
y=x^e

# Izpis
print(y)