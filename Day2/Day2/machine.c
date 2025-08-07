#include <stdio.h>

// �Լ� ����
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);

int main() {
    double num1, num2, result;
    char op;

    printf("������ ���� ���α׷�\n");
    printf("����: ���� ������ ���� (��: 3.5 + 2.2)\n");

    // ����� �Է� �ޱ�
    printf("������ �Է��ϼ���: ");
    scanf("%lf %c %lf", &num1, &op, &num2);

    // �����ڿ� ���� �Լ� ȣ��
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
            printf("����: 0���� ���� �� �����ϴ�.\n");
            return 1;
        }
        result = divide(num1, num2);
        break;
    default:
        printf("����: �߸��� �������Դϴ�.\n");
        return 1;
    }

    // ��� ���
    printf("���: %.2lf %c %.2lf = %.2lf\n", num1, op, num2, result);

    return 0;
}

// �Լ� ����
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
