#pomoc funkcije
#help(help)
#tip necesa
type(None)

#float je double
1 + 3.14

#to deluje
st_zvezd = 123812381231923192307123891723812738129367189237129837121723681723671823871

#imaginarno stevilo
z = 2 + 3j
type(z)
z.real
z.imag
z.conjugate()

#nizi
niz = 'Eureka!'

niz = 'Arhimed je vzkliknil: "Eureka!"'
print(niz)

niz = '''"Ej'ga, Eureka!"'''

niz = 'Dober' + ' ' + 'dan'

#bool
res = True
type(res)
res = False

#prirejanje
x = 2
y = 2
#---enako---
x = y = 2
x, y, z = 1, 2, 3
    # x=1,y=2,z=3

#list -> [x,y]  spremenljiv
#tuple -> (x,y) nespremenljiv
x,y,z = (1,2,3) # enak ko zgori

#zamenjava vrednosti
x,y = y,x

prvi, drugi, tretji = 'TIS'
prvi, *ostali = 'TIS' #ostali -> ['I', 'S']

i = 0
i += 1 #ne obstaja i++

#izpise vsa imena
dir() 

#typecasting
int('22') #---> 22
int('22', 3) #---> 8
int('1000',2) #---> 8
int(43.6) #---> 43
str(42) #---> '42'

print('Rezultat je: ', 3)#Rezultat je:  3
#sep=' ' default vrednost
print('Rezultat je: ', 3, sep=',')#Rezultat je: ,3 
print('Rezultat je: ', 3, sep='')#Rezultat je: 3

#bool vrednosti
bool(True) #True
bool(1) #True
bool(0) #False
bool(None) #False
bool(5) #True
bool(0.0) #False
bool(-0) #False
bool('niz') #True
bool('') #False
bool([]) #False
bool({}) #False

chr(65) #---> A
ord('A') #---> 65

chr(0x2192) #---> →
ord('→') #---> 8594

not True and '' #False
not True or ''  #'' --> False
not True or 'false' #'false' --> True
bool('false') #---> True

volitve = 'levi' or 'desni' #'levi'
volitve = 'levi' and 'desni' #'desni'

#pogoji / operacije
1 <= 2
1 >= 2
1 == 2
1 != 2

a = 0.5
-1 < a < 1

3 / 2 #---> 1.5
2 / 2 #---> 1.0
3 // 2 #---> 1
3.2 // 2 #---> 1.0

3 % 2 # 1
2 ** 3 # 8

#uporabne funkcije
abs(-1)
abs(3+2j)
min(1,2,3)
max(1,2,3)
sum((1,2,3))

min('abc') #a
min('bca') #a

dir(__builtins__) #vse funkcije

#dodatne funkcije z import
import math
type(math) # module
math.pi
math.sin(math.pi)
math.factorial(3)
from math import sin
from math import pi,log,log2,log10
sin(pi)
log2(8)

#bitne operacije
~5 #bitno negiranje --> -6
1 & 2 #bitni in --> 0
1 | 2 #bitni ali --> 3
1 ^ 2 #xor --> 3
1 << 2 #shiftanje levo --> 4
4 >> 2 #shiftanje desno --> 1

#pisanje fun
def lastna_informacija(p):
    from math import log2
    return -log2(p)

I = lastna_informacija(0.5)
print('Rezultat je:', I, 'bit.')
print('Rezultat je: '+ str(I) + ' bit.')
print(f'Rezultat je: {I:.2f} bit.')

#default vrednost r=2
def lastna_informacija(p, r = 2):
    from math import log2, log10, nan
    if r == 2:
        I = -log2(p)
    elif r == 10:
        I = -log10(p)
    else:
        I = nan
    return I 

#lahko tudi poljuben vrstni red tako
lastna_informacija(r=2, p=0.5)

#while
s = 0
i = 0
while i <= 100:
    s += i
    i += 1
print(s)

#for
zaporedje = 'niz'
zaporedje = ['SE', 'ZN', 'AM']
zaporedje = ['A', 3, 'WOW']
for element in zaporedje:
    print(element)

zaporedje[0] #A
zaporedje[0:2] #od vkljucno 0 do nevkljucno 2

zaporedje = [0,1,2,3,4,5,6,7]
zaporedje[0:8:2] #[od:do:korak]
zaporedje[::2]

zaporedje[-1] # zadni

zaporedje[-1:-9:-1] #obrnes
zaporedje[::-1]  

range(0,7,1) #generator
list(range(0,7,1)) #dobis vse

seznam = ['TIS' , 42, 3+2j]
for i in range(len(seznam)):
    print(f'{i}: {seznam[i]}')

for i,element in enumerate(seznam):
    print(f'{i}: {element}')