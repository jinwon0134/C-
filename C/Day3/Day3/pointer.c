//#include <stdio.h>
//
//void main() {
//	int a = 10;
//	int* pa;
//	pa = &a;
//	printf("&a: %p, pa: %p\n", &a, pa); //int* pa�� �׳� ��ȣ�� ��� but *pa�� ���������ڱ� ������ ����Ʈ ������ ����
//	//���� *pa =20�̸� pa�� ����Ű�� ���� 20�� ����־��
//	printf("a: %d, *pa:%d\n", a, *pa);
//
//	*pa = 20;
//	printf("a: %d, *pa: %d\n", a, *pa);
//	printf("pa+ 1: %p\n", pa + 1);
//
//	char c = 'a';
//	pa = &c;
//	printf("pa: %p, pa+1: %p\n", pa, pa + 1);
//	/*�������� ��ǥ�ÿ� ��ġ�� ���� ������ �ٸ�.
//	���� a�� �ּҰ��� �����ͺ����� ���� �ϴ� �ڵ�*/
//}