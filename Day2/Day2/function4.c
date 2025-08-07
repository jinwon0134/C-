/*출력(반환값)이 없고 입력이 있는 함수

#include <stdio.h>

void func(int);

void main() {
	int num = 10;
	func(1);//호출 쪽 입력은 실인수
	func(num);
}

void func(int n) { 
	printf("%d\n", n); //받는 쪽 입력은 매개변수
}*/