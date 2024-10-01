
str = "azZAbc..,.,ACdAbc..,.,ACdeAbc..,.,ACdeAbc..,.,ACdeAbc..,.,ACdeAbc..,.,ACdeAbc..,.,ACdee"
str2 = ""
for x in str:
    if 65 <= ord(x) <= 90 or 97 <= ord(x) <= 122:
        str2 += x
str2 = str2.upper()
print(str2)

prev = ''
tab = {}
count = 0
for x in str2:
    if prev != '':
        count += 1
        curr = prev + x
        if not curr in tab:
            tab[curr] = 1
        else :
            tab[curr] += 1
    prev = x

a = str2.count('A')
print(a)

for x in tab:
    print(f"{x}: {tab[x]}")
print(count)

u = set(str2)
print(u)
f = [str2.count(unikat) for unikat in u]
print(f)
p = [frekvenca/len(str2) for frekvenca in f]
print(p)
from collections import Counter
a = Counter(str2)
print(a)
print(a['A'])
pari = (list(zip(str2[:-1],str2[1:])))

#print(list(zip(str2[:-1],str2[1:],str2[2:],str2[3:])))

pari = (list(zip(str2[:-1],str2[1:])))
counter = Counter(pari)
f = {}
skupi = 0
for x in counter:
    print(f"{x}: {counter[x]}")
    f[x] = counter[x]
    skupi += counter[x]

p={}
for x in f:
    p[x] = f[x] / skupi

print(f)
print(skupi)
print(p)