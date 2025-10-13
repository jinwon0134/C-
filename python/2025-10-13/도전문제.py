dna = input("염기 서열을 입력해주세요: ")
#window method
codon_list = []
codon_dict = {}
for i in range(0, len(dna), 3):
    codon_list.append(dna[i:i + 3])
print(codon_list)