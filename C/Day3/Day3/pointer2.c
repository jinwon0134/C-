//#include <stdio.h>
//
//void main() {
//	int ary[] = { 1,2 };
//
//	int(*pary);
//	pary = ary;
//	printf("%p, %p\n", ary, pary);
//	printf("%p, %p\n", ary+1, pary+1);
//
//	printf("===================================================\n");
//
//	char ary2[] = { 'a','b' };
//	char (*pary2) = ary2;
//	printf("%p, %p\n", ary2 + 0, pary2+0);
//	printf("%p, %p\n", ary2+ 1, pary2 + 1);
//	printf("===================================================\n");
//
//	int ary3[2][2] = { {1,2},{3,4} };
//	int (*pary3) = ary3;
//	printf("%p, %p\n", ary3, pary3);
//	printf("%p, %p\n", ary3 + 1, pary3 + 1);
//	/*
//		p1= &a;    --> 변수 주소
//		p2= ary    ==> 1차원 배열 주소
//		p3 = ary*; --> 2차원 배열 주소
//		배역 가르는 포인터  --> int(*P2) = ary
//		int (*p3[2])=ary2
//		*/
//
//}