kor = input("국어 성적을 입력하세요: ")
eng = input("영어 성적을 입력하세요: ")
math = input("수학 성적을 입력하세요: ")

sum = int(kor) + int(eng) + int(math)
average = sum/3
print('합계: %d, 평균: %.2f'%(sum, average))