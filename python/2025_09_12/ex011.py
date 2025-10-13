count = 0
for i in range(800,901):
    if i %4 != 0:
        print('%4d'% i, end = "")
        count = count+1
    if count % 10 == 0:
        print()