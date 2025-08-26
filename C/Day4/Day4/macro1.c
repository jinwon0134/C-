//#include <stdio.h>
//#define NAME_CAT(x,y) (x ## y)					//##은 x와 y를 붙이라는 뜻
//#define PRINT_EXPR(x)	printf(#x " = %d\n",x)  //#은 x의 값을 문자열로 출력하라
//
//int main() {
//
//	int a1, a2;
//	NAME_CAT(a, 1) = 10;//따라서 a와 1을 붙여 a1이 출력
//	NAME_CAT(a, 2) = 20;
//
//	PRINT_EXPR(a1 + a2);
//
//	//printf("a1 + a2 = %d\n", a1 + a2);
//
//	return 0;
//}