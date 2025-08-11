//#include <stdio.h>
//#include <stdlib.h>
//void main() {
//	int* ptr;
//	int size = 10;
//	//heap영역에 메모리 공간을 할당 받음.
//	ptr =(int*) malloc(sizeof(int) *size);
//
//	if (ptr == NULL) {
//		perror("메모리 할당 실패");
//		return 1;
//	}
//	for (int i = 0; i < size; i++) {
//		ptr[i] = i + 1;
//	}
//	for (int i = 0; i < size; i++) {
//		printf("%d ", ptr[i]);
//	}
//	//동적 메모리 해제(free가 없으면 메모리를 계속 차지)-> 요즘은 운영체제가 자동으로 메모리 반환 해주기는 함.
//	free(ptr);
//}