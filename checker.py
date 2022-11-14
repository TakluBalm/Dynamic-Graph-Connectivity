f1 = open("brute_output.txt", "r")
f2 = open("graph_output.txt", "r")
f3 = open("test.txt","r")
cnt = 0
l1 = f1.readline()
l2 = f2.readline()
con_check = []
l3 = f3.readline()
while l3!= '':
	arr = l3.strip(' \n').split(' ')
	if arr[0]=='con':
		con_check.append([arr[1],arr[2]])
	l3 = f3.readline()

lin =0
hasError = False
while l1 != '':
	if(l1 != l2):
		print("Expected ", l1, " got ", l2)
		print(con_check[lin])
		cnt += 1
		hasError = True
	lin+=1
	l1 = f1.readline()
	l2 = f2.readline()

if hasError:
	print("Total ", cnt, " mistakes")
	exit(1)
else:
	exit(0)