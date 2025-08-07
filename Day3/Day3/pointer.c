//#include <stdio.h>
//
//void main() {
//	int a = 10;
//	int* pa;
//	pa = &a;
//	printf("&a: %p, pa: %p\n", &a, pa); //int* pa는 그냥 기호로 사용 but *pa는 참조연산자기 때문에 포인트 역할을 가짐
//	//따라서 *pa =20이면 pa가 가리키는 곳에 20을 집어넣어라
//	printf("a: %d, *pa:%d\n", a, *pa);
//
//	*pa = 20;
//	printf("a: %d, *pa: %d\n", a, *pa);
//	printf("pa+ 1: %p\n", pa + 1);
//
//	char c = 'a';
//	pa = &c;
//	printf("pa: %p, pa+1: %p\n", pa, pa + 1);
//	/*포인터의 별표시에 위치에 따라 역할이 다름.
//	변수 a의 주소값을 포인터변수에 대입 하는 코드*/
//}