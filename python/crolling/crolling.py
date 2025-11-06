from bs4 import BeautifulSoup
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.chrome.options import Options
import time
import pandas as pd
import urllib.parse
from webdriver_manager.chrome import ChromeDriverManager
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC


# --- 1. 29CM 크롤링 함수 ---
def crawl_29cm(keyword, pages=1):
    print(f"\n--- 29CM 크롤링 시작 (검색어: '{keyword}', {pages}페이지) ---")
    encoded_keyword = urllib.parse.quote(keyword)
    results_29cm = []

    options = Options()
    options.add_argument("--start-maximized")
    options.add_argument(
        "User-Agent=Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/123.0.0.0 Safari/537.36")
    options.add_experimental_option("detach", True)
    options.add_experimental_option("excludeSwitches", ["enable-logging", "enable-automation"])

    driver = webdriver.Chrome(service=Service(ChromeDriverManager().install()), options=options)

    for page in range(1, pages + 1):
        url = f'https://shop.29cm.co.kr/search?keyword={encoded_keyword}&sort=RECOMMENDED&page={page}'
        driver.get(url)
        print(f"🔗 29CM 크롤링 중: {url}")
        time.sleep(3)  # 페이지 로딩 대기

        # 페이지 끝까지 스크롤 (Lazy Load)
        last_height = driver.execute_script("return document.body.scrollHeight")
        while True:
            driver.execute_script("window.scrollTo(0, document.body.scrollHeight);")
            time.sleep(2)
            new_height = driver.execute_script("return document.body.scrollHeight")
            if new_height == last_height:
                break
            last_height = new_height

        # 상품 로딩 대기
        try:
            WebDriverWait(driver, 10).until(
                EC.presence_of_all_elements_located((By.CSS_SELECTOR, "li > div.mb-40.space-y-12"))
            )
        except:
            print(f"❌ 29CM {page}페이지 상품 로딩 실패 또는 요소 없음.")
            continue

        html = driver.page_source
        soup = BeautifulSoup(html, 'html.parser')

        items = soup.select("li > div.mb-40.space-y-12")  # 단일 상품 컨테이너

        print(f"✅ 29CM {page}페이지 ({len(items)}개 상품 발견)")

        for rank, item in enumerate(items, 1):
            try:
                brand_element = item.select_one("span.align-middle.text-s-bold")
                brand = brand_element.text.strip() if brand_element else "브랜드 없음"

                title_element = item.select_one("a.line-clamp-2.break-all.mb-6")
                title = title_element.text.strip() if title_element else "상품명 없음"

                discount_element = item.select_one("p.text-l-bold.text-accent")
                discount = discount_element.text.strip() if discount_element else "할인 없음"

                price_element = item.select_one(
                    "div.items-center.flex.gap-2.text-xxl-bold.text-primary > p:nth-child(2)")
                price = price_element.text.strip() if price_element else "가격 정보 없음"

                product_link_element = item.select_one("a.line-clamp-2.break-all.mb-6")
                product_link = product_link_element['href'] if product_link_element else "링크 없음"

                results_29cm.append({
                    "쇼핑몰": "29CM",
                    "브랜드": brand,
                    "상품명": title,
                    "가격": price,
                    "할인율": discount,
                    "링크": product_link
                })

            except Exception as e:
                print(f"29CM 상품 추출 오류 ({rank}번 상품): {e}")
                pass

    driver.quit()
    print(f"--- 29CM 크롤링 완료! 총 {len(results_29cm)}개 상품 ---")
    return pd.DataFrame(results_29cm)


# --- 2. 무신사 크롤링 함수 (최종 업데이트된 선택자 적용) ---
def crawl_musinsa(keyword, pages=1):
    print(f"\n--- 무신사 크롤링 시작 (검색어: '{keyword}', {pages}페이지) ---")
    encoded_keyword = urllib.parse.quote(keyword)
    results_musinsa = []

    # WebDriver 설정은 생략 (전체 코드에서는 포함되어 있음)
    options = Options()
    options.add_argument("--start-maximized")
    options.add_argument(
        "User-Agent=Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/123.0.0.0 Safari/537.36")
    options.add_experimental_option("detach", True)
    options.add_experimental_option("excludeSwitches", ["enable-logging", "enable-automation"])
    driver = webdriver.Chrome(service=Service(ChromeDriverManager().install()), options=options)

    for page in range(1, pages + 1):
        url = f'https://www.musinsa.com/search/musinsa/goods?q={encoded_keyword}&listType=small&target=category&sortCode=pop&page={page}'
        driver.get(url)
        print(f"🔗 무신사 크롤링 중: {url}")
        time.sleep(3)

        # 스크롤 로직 생략 (전체 코드에서는 포함되어 있음)
        last_height = driver.execute_script("return document.body.scrollHeight")
        while True:
            driver.execute_script("window.scrollTo(0, document.body.scrollHeight);")
            time.sleep(2)
            new_height = driver.execute_script("return document.body.scrollHeight")
            if new_height == last_height:
                break
            last_height = new_height

        # 상품 로딩 대기
        try:
            # 전체 상품 컨테이너 대기
            WebDriverWait(driver, 10).until(
                EC.presence_of_all_elements_located(
                    (By.CSS_SELECTOR, "div.UIStyleComponents__UIItemContainerStyle-sc-d36st-1"))
            )
        except Exception as e:
            print(f"❌ 무신사 {page}페이지 상품 로딩 실패 또는 요소 없음.")
            continue

        html = driver.page_source
        soup = BeautifulSoup(html, 'html.parser')

        # ⭐ 상품 목록 선택자 (최대한 안정적으로) ⭐
        items = soup.select("div.UIStyleComponents__UIItemContainerStyle-sc-d36st-1")

        print(f"✅ 무신사 {page}페이지 ({len(items)}개 상품 발견)")

        for rank, item in enumerate(items, 1):
            try:
                # 1. 브랜드명: '샵으로 이동' <a> 태그 안의 <span>
                brand_element = item.select_one("a[aria-label$='샵으로 이동'] > span")
                brand = brand_element.text.strip() if brand_element else "브랜드 없음"

                # 2. 상품명 및 링크: '상품상세로 이동' <a> 태그
                title_link_element = item.select_one("a[aria-label$='상품상세로 이동']")
                product_link = title_link_element['href'] if title_link_element else "링크 없음"

                # 상품명은 링크 태그 안의 <span>에서 추출
                title_element = title_link_element.select_one("span")
                title = title_element.text.strip() if title_element else "상품명 없음"

                # 3. 가격 및 할인율
                # 가격 컨테이너: sc-jwTyAe sc-hjsuWn DVxSk ANWFy
                price_container = item.select_one("div.sc-jwTyAe.sc-hjsuWn.DVxSk.ANWFy")

                discount = "할인 없음"
                price = "가격 정보 없음"

                if price_container:
                    # 할인율: text-red 클래스를 가진 span
                    discount_element = price_container.select_one("span.text-red")
                    discount = discount_element.text.strip() if discount_element else "할인 없음"

                    # 가격: text-red가 없는 span을 가격으로 간주
                    # 또는 모든 span 중 마지막 span을 가격으로 간주
                    price_element = price_container.select_one("span:not(.text-red)")
                    if price_element:
                        price = price_element.text.strip()
                    else:
                        # 할인 없는 상품의 경우 하나의 span만 있을 수 있음 (가격)
                        all_spans = price_container.select("span")
                        if all_spans and discount == "할인 없음":
                            price = all_spans[-1].text.strip()

                results_musinsa.append({
                    "쇼핑몰": "무신사",
                    "브랜드": brand,
                    "상품명": title,
                    "가격": price,
                    "할인율": discount,
                    "링크": product_link
                })

            except Exception as e:
                # print(f"무신사 상품 추출 오류 ({rank}번 상품): {e}")
                pass

    driver.quit()
    print(f"--- 무신사 크롤링 완료! 총 {len(results_musinsa)}개 상품 ---")
    return pd.DataFrame(results_musinsa)

# --- 3. 메인 실행 블록 ---
if __name__ == "__main__":
    search_keyword = input("크롤링할 옷 카테고리/상품을 입력하세요 (예: 후드티, 코트): ")
    num_pages = int(input("각 쇼핑몰에서 몇 페이지를 크롤링할까요? (숫자 입력): "))

    # 29CM 크롤링 실행
    df_29cm = crawl_29cm(search_keyword, pages=num_pages)

    # 무신사 크롤링 실행
    df_musinsa = crawl_musinsa(search_keyword, pages=num_pages)

    # 결과 병합 (두 DataFrame이 있다면)
    if not df_29cm.empty and not df_musinsa.empty:
        combined_df = pd.concat([df_29cm, df_musinsa], ignore_index=True)
        combined_df.to_csv(f"shopping_comparison_{search_keyword}.csv", index=False, encoding="utf-8-sig")
        print(f"\n✅ 29CM와 무신사 크롤링 결과가 'shopping_comparison_{search_keyword}.csv' 파일로 저장되었습니다.")
    elif not df_29cm.empty:
        df_29cm.to_csv(f"29cm_{search_keyword}.csv", index=False, encoding="utf-8-sig")
        print(f"\n✅ 29CM 크롤링 결과만 '29cm_{search_keyword}.csv' 파일로 저장되었습니다.")
    elif not df_musinsa.empty:
        df_musinsa.to_csv(f"musinsa_{search_keyword}.csv", index=False, encoding="utf-8-sig")
        print(f"\n✅ 무신사 크롤링 결과만 'musinsa_{search_keyword}.csv' 파일로 저장되었습니다.")
    else:
        print("\n❌ 두 쇼핑몰 모두에서 데이터를 가져오지 못했습니다.")

    print("\n모든 크롤링 프로세스가 완료되었습니다.")