//#include <stdio.h>
//
//void main() {
//	char animal[5][20];
//	int i;
//	int size;
//	size = sizeof(animal) / sizeof(animal[0]);
//	printf("%d\n", size);
//
//	printf("input: ");
//	for (int i = 0; i < size; i++) {
//		scanf_s("%s", animal[i], (unsigned)sizeof(animal[i]));
//	}
//	for (int i = 0; i < size; i++) {
//		printf("%s", animal[i]);
//	}
//}