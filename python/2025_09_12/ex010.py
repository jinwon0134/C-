from pkgutil import resolve_name

list_of_list = [[1,2,3], [4,5,6,7], [8,9]]
for i in range(3):
    for j in range(len(list_of_list[i])):
        print(list_of_list[i][j], end = "  ")
    print()