import random

f = open("test.txt", "w")

V = random.randint(100, 5000)
# V = 10
ops = random.randint(100, V*V)
# ops = 500
f.write(f'{V} {ops}\n')

print(f'V = {V}, ops = {ops}')

mp = set()
i = 0
while i < ops:
	s = random.randint(1, 10*ops)

	if s <= int((len(mp)/2)*ops/V*V):
		k = mp.pop()
		f.write(f'rem {k[0]} {k[1]}\n')
		mp.remove((k[1], k[0]))
	elif s <= 2*ops:
		v1 = random.randint(1,V)
		v2 = random.randint(1,V)
		while v1 == v2 or {(v1,v2)}.issubset(mp):
			v1 = random.randint(1,V)
			v2 = random.randint(1,V)
		f.write(f'add {v1} {v2}\n')
		mp.add((v1,v2))
		mp.add((v2,v1))
	else:
		v1 = random.randint(1,V)
		v2 = random.randint(1,V)
		while v1 == v2:
			v1 = random.randint(1,V)
			v2 = random.randint(1,V)
		f.write(f'con {v1} {v2}\n')
	i += 1