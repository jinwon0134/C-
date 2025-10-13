numbers = [103, 52,273,32,77]
sorted_numbers = sorted(numbers)

print(f'최솟값  : {min(numbers)})')
print(f' 최솟값 : {sorted_numbers[0]}')

print(f'최댓값 : {max(numbers)})')
print(f'최댓값 : {sorted_numbers[len(sorted_numbers)-1]}')

print(f'총합 : {sum(numbers)})')

summation =0
for i in numbers:
    summation += i
print(summation)
print(f'평균값 : {sum(numbers)/len(numbers)})')