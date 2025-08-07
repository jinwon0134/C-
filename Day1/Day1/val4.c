#include <stdio.h>

void main()
{
	/*
		배열명은 배열의 시작주소를 나타낸다.
		문자열은 문자열크기 +1의 배열크기를 가진다.
	*/
	char ch = 'a';
	printf("ch: %c, ch: %d\n", ch, ch);
	
	char str[] = "apple";
	printf("str: %s\n", str);

	printf("str[0]: %c\n", str[0]);
	printf("str[4]: %c\n", str[4]);
	printf("str[5]: %c\n", str[5]); //NULL 문자 출력

	char str1[] = "banana";
	//char str2[30] = str + st1;
	int a = 10, b = 20;
	int c = a + b;
}