#include <stdio.h>

void main()
{
	/*
		�迭���� �迭�� �����ּҸ� ��Ÿ����.
		���ڿ��� ���ڿ�ũ�� +1�� �迭ũ�⸦ ������.
	*/
	char ch = 'a';
	printf("ch: %c, ch: %d\n", ch, ch);
	
	char str[] = "apple";
	printf("str: %s\n", str);

	printf("str[0]: %c\n", str[0]);
	printf("str[4]: %c\n", str[4]);
	printf("str[5]: %c\n", str[5]); //NULL ���� ���

	char str1[] = "banana";
	//char str2[30] = str + st1;
	int a = 10, b = 20;
	int c = a + b;
}