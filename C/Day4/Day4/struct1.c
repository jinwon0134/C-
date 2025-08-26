//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//struct profile {
//	char name[20];
//	int age; 
//	double height;
//	double weight;
//	char* info;
//	//신경써야할 점: double은 8바이트지만 int는 4바이트기 때문에 메모리의 크기를 맞춰주기 위해 int를 하나 더 사용해야 한다.
//};
//
//void main() {
//	struct profile m;
//	m.age = 25;
//	m.height = 173;
//	m.weight = 67;
//	strcpy(m.name, "홍길동") ;//배열이기 때문에 주소에 홍길동을 넣을 수 없기에 strcpy를 이용
//	m.info = (char* )malloc(80);//return 시킬 동일한 타입으로 작성
//
//	printf("자기소개: ");
//	scanf("%s", m.info);
//	printf("이름: %s\n", m.name);
//	printf("나이: %d\n", m.age);
//	printf("몸무게: %.1lf\n", m.weight);
//	printf("키: %.1lf\n", m.height);
//	printf("소개: %s\n", m.info);
//
//}