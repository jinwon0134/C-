#include <stdio.h>

// 함수 선언
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);

int main() {
    double num1, num2, result;
    char op;

    printf("간단한 계산기 프로그램\n");
    printf("사용법: 숫자 연산자 숫자 (예: 3.5 + 2.2)\n");

    // 사용자 입력 받기
    printf("계산식을 입력하세요: ");
    scanf("%lf %c %lf", &num1, &op, &num2);

    // 연산자에 따라 함수 호출
    switch (op) {
    case '+':
        result = add(num1, num2);
        break;
    case '-':
        result = subtract(num1, num2);
        break;
    case '*':
        result = multiply(num1, num2);
        break;
    case '/':
        if (num2 == 0) {
            printf("오류: 0으로 나눌 수 없습니다.\n");
            return 1;
        }
        result = divide(num1, num2);
        break;
    default:
        printf("오류: 잘못된 연산자입니다.\n");
        return 1;
    }

    // 결과 출력
    printf("결과: %.2lf %c %.2lf = %.2lf\n", num1, op, num2, result);

    return 0;
}

// 함수 정의
double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    return a / b;
}
