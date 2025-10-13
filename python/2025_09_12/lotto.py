import numpy as np

def generate_lotto():
    """1~45 중 6개 번호 뽑기 (중복 없음, 정렬된 배열)"""
    return np.sort(np.random.choice(range(1, 46), size=6, replace=False))

def check_rank(user_numbers, winning_numbers, bonus_number):
    """유저 번호와 당첨 번호 비교 후 등수 반환"""
    matches = len(set(user_numbers) & set(winning_numbers))
    has_bonus = bonus_number in user_numbers

    if matches == 6:
        return "1등"
    elif matches == 5 and has_bonus:
        return "2등"
    elif matches == 5:
        return "3등"
    elif matches == 4:
        return "4등"
    elif matches == 3:
        return "5등"
    else:
        return "꽝"
    
# 컴퓨터: 당첨 번호 + 보너스 번호
winning_numbers = generate_lotto()
remaining = set(range(1, 46)) - set(winning_numbers)
bonus_number = np.random.choice(list(remaining))

# 유저 입력
user_input = input("당신의 로또 번호 6개를 입력하세요: ")
user_numbers = list(map(int, user_input.split()))

# 유효성 검사
if len(user_numbers) != 6 or not all(1 <= n <= 45 for n in user_numbers):
    print("잘못된 입력입니다. 1~45 사이의 서로 다른 숫자 6개를 입력하세요.")
else:
    user_numbers = np.sort(user_numbers)
    print(f"당첨 번호: {winning_numbers} + 보너스({bonus_number})")
    print(f"유저 번호: {user_numbers}")

    # 결과
    result = check_rank(user_numbers, winning_numbers, bonus_number)
    print(f"결과: {result}")
