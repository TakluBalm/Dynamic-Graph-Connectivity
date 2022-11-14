import random
import argparse
parser = argparse.ArgumentParser()
parser.add_argument("ver", help="display a square of a given number",
                    type=int)
args = parser.parse_args()
V = args.ver
# V = 10
ops = 1000000
# ops = 500


f = open("test.txt", "w")
f.write(f'{V} {ops}\n')
f_graph_u = open("graph_update.txt","a")
f_graph_u.write("ver" + str(V) + "\n")
f_graph_q = open("graph_query.txt","a")
f_graph_q.write("ver" + str(V) + "\n")
f_brute_u = open("brute_update.txt","a")
f_brute_u.write("ver" + str(V) + "\n")
f_brute_q = open("brute_query.txt","a")
f_brute_q.write("ver" + str(V) + "\n")
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