//#include <stdio.h>
//
//void swap(int x, int y) {
//	int temp;
//	temp = x;
//	x = y;
//
//	y = temp;
//}
//void swap1(int* pa, int* pb);
//void swap(int x, int y);
//
//void main() {
//	int a = 10, b = 20;
//	printf("a: %d, b: %d\n", a, b);
//	//���� ���� ����
//	swap(a, b);
//	//�ּҿ� ���� ����
//	swap1(&a, &b);
//	printf("a: %d, b: %d\n", a, b);
//	int temp = a;
//	a = b;
//	b = temp;
//
//	printf("a: %d, b: %d\n", a, b);
//	
//
//}
//void swap1(int* pa, int* pb) {
//	int temp = *pa;
//	*pa = *pb;
//	*pb = temp;
//}