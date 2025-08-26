#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[20];
    double weight;
} Fitness;

// 전체 회원 등록 수 출력
void total_number(int count) {
    printf("전체 회원 등록 수: %d명\n", count);
}

// 평균 체중 계산
double average_weight(Fitness** pary, int count) {
    double sum = 0;
    for (int i = 0; i < count; i++) {
        sum += (*pary)[i].weight; // 올바른 접근 방식
    }
    return sum / count;
}

// 최고 체중 회원의 인덱스 반환
int max_weight(Fitness** pary, int count) {
    int max_index = 0;
    for (int i = 1; i < count; i++) {
        if ((*pary)[i].weight > (*pary)[max_index].weight) {
            max_index = i;
        }
    }
    return max_index;
}

// 특정 회원 정보 출력
void print_info(Fitness** pary, int index) {
    printf("학생의 이름은 %s, ID는 %d, 체중은 %.1lfkg입니다.\n",(*pary)[index].name,(*pary)[index].id, (*pary)[index].weight);
}

// 동적 할당 해제
void free_ary(Fitness** pary, int count) {
    free(*pary);
    *pary = NULL;
}

int main() {
    int count;
    printf("회원 수를 입력하세요: ");
    scanf("%d", &count);

    // 동적 할당
    Fitness* members = (Fitness*)malloc(sizeof(Fitness) * count);
    if (members == NULL) {
        printf("메모리 할당 실패!\n");
        return 1;
    }

    // 회원 정보 입력
    for (int i = 0; i < count; i++) {
        printf("\n회원 %d 정보 입력\n", i + 1);
        members[i].id = i + 1;
        printf("이름: ");
        scanf("%s", members[i].name); // 문자열 입력 시 버퍼 크기 제한
        printf("체중(kg): ");
        scanf("%lf", &members[i].weight);
    }

    Fitness* ptr = members; // 더블 포인터 전달을 위해

    total_number(count);
    printf("평균 체중: %.1f kg\n", average_weight(&ptr, count));

    int max_idx = max_weight(&ptr, count);
    printf("가장 체중이 높은 회원:\n");
    print_info(&ptr, max_idx);

    // 메모리 해제
    free_ary(&ptr, count);

    return 0;
}
