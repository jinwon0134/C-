import pandas as pd

# 1. 저장된 CSV 파일 불러오기 (예시: "shopping_comparison_후드티.csv")
# 실제 파일명과 경로에 맞게 수정하세요.
try:
    df = pd.read_csv("shopping_comparison_후드티.csv", encoding="utf-8-sig")
    print("CSV 파일을 성공적으로 불러왔습니다.")
    print("원본 데이터프레임의 상위 5개 행:")
    print(df.head())
    print("\n")
except FileNotFoundError:
    print("파일을 찾을 수 없습니다. 파일 경로와 이름을 확인해주세요.")
    exit()

# 2. DataFrame에서 조건 걸어 데이터 추출하기

# --- 예시 1: 특정 쇼핑몰의 상품만 추출 ---
condition_musinsa = (df['쇼핑몰'] == '무신사')
df_musinsa_only = df[condition_musinsa]
print("--- 무신사 상품만 추출 ---")
print(df_musinsa_only.head())
print(f"추출된 무신사 상품 수: {len(df_musinsa_only)}\n")

# --- 예시 2: 특정 브랜드의 상품만 추출 ---
condition_brand = (df['브랜드'] == '29CM')
df_spao_only = df[condition_brand]
print("--- 29CM 상품만 추출 ---")
print(df_spao_only.head())
print(f"추출된 29CM 상품 수: {len(df_spao_only)}\n")

# --- 예시 3: 가격이 특정 금액 이하인 상품 추출 ---
# 가격 열이 문자열 ('35,900원')일 경우 숫자로 변환해야 합니다.
# '원', ',' 제거 후 숫자로 변환
df['가격_숫자'] = df['가격'].str.replace('원', '').str.replace(',', '').astype(int)

condition_price_under_40k = (df['가격_숫'] <= 40000)
df_under_40k = df[condition_price_under_40k]
print("--- 가격 4만원 이하 상품 추출 ---")
print(df_under_40k.head())
print(f"추출된 4만원 이하 상품 수: {len(df_under_40k)}\n")

# --- 예시 4: 할인율이 특정 값 이상인 상품 추출 ---
# 할인율 열이 문자열 ('45%')일 경우 숫자로 변환해야 합니다.
# '할인 없음' 같은 문자열은 0%로 처리
df['할인율_숫자'] = df['할인율'].str.replace('%', '').str.replace('할인 없음', '0').astype(int)

condition_discount_over_30 = (df['할인율_숫자'] >= 30)
df_discount_over_30 = df[condition_discount_over_30]
print("--- 할인율 30% 이상 상품 추출 ---")
print(df_discount_over_30.head())
print(f"추출된 30% 이상 할인 상품 수: {len(df_discount_over_30)}\n")

# --- 예시 5: 여러 조건 동시 적용 (AND 조건) ---
# 무신사의 상품 중 가격이 5만원 이하인 상품
condition_musinsa_and_price = (df['쇼핑몰'] == '무신사') & (df['가격_숫자'] <= 50000)
df_musinsa_price_filtered = df[condition_musinsa_and_price]
print("--- 무신사에서 5만원 이하 상품 추출 ---")
print(df_musinsa_price_filtered.head())
print(f"추출된 상품 수: {len(df_musinsa_price_filtered)}\n")

# --- 예시 6: 여러 조건 동시 적용 (OR 조건) ---
# 무신사 또는 29CM 상품 중 할인율이 20% 이상인 상품
condition_shop_or_discount = ((df['쇼핑몰'] == '무신사') | (df['쇼핑몰'] == '29CM')) & (df['할인율_숫자'] >= 20)
df_shop_or_discount_filtered = df[condition_shop_or_discount]
print("--- (무신사 또는 29CM) 중 할인율 20% 이상 상품 추출 ---")
print(df_shop_or_discount_filtered.head())
print(f"추출된 상품 수: {len(df_shop_or_discount_filtered)}\n")


# 3. 추출된 데이터를 새로운 CSV 파일로 저장
df_musinsa_price_filtered.to_csv("musinsa_under_50k_hoody.csv", index=False, encoding="utf-8-sig")
print("조건에 맞는 상품이 'musinsa_under_50k_hoody.csv'로 저장되었습니다.")