#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[20];
    double weight;
} Fitness;

// ��ü ȸ�� ��� �� ���
void total_number(int count) {
    printf("��ü ȸ�� ��� ��: %d��\n", count);
}

// ��� ü�� ���
double average_weight(Fitness** pary, int count) {
    double sum = 0;
    for (int i = 0; i < count; i++) {
        sum += (*pary)[i].weight; // �ùٸ� ���� ���
    }
    return sum / count;
}

// �ְ� ü�� ȸ���� �ε��� ��ȯ
int max_weight(Fitness** pary, int count) {
    int max_index = 0;
    for (int i = 1; i < count; i++) {
        if ((*pary)[i].weight > (*pary)[max_index].weight) {
            max_index = i;
        }
    }
    return max_index;
}

// Ư�� ȸ�� ���� ���
void print_info(Fitness** pary, int index) {
    printf("�л��� �̸��� %s, ID�� %d, ü���� %.1lfkg�Դϴ�.\n",(*pary)[index].name,(*pary)[index].id, (*pary)[index].weight);
}

// ���� �Ҵ� ����
void free_ary(Fitness** pary, int count) {
    free(*pary);
    *pary = NULL;
}

int main() {
    int count;
    printf("ȸ�� ���� �Է��ϼ���: ");
    scanf("%d", &count);

    // ���� �Ҵ�
    Fitness* members = (Fitness*)malloc(sizeof(Fitness) * count);
    if (members == NULL) {
        printf("�޸� �Ҵ� ����!\n");
        return 1;
    }

    // ȸ�� ���� �Է�
    for (int i = 0; i < count; i++) {
        printf("\nȸ�� %d ���� �Է�\n", i + 1);
        members[i].id = i + 1;
        printf("�̸�: ");
        scanf("%s", members[i].name); // ���ڿ� �Է� �� ���� ũ�� ����
        printf("ü��(kg): ");
        scanf("%lf", &members[i].weight);
    }

    Fitness* ptr = members; // ���� ������ ������ ����

    total_number(count);
    printf("��� ü��: %.1f kg\n", average_weight(&ptr, count));

    int max_idx = max_weight(&ptr, count);
    printf("���� ü���� ���� ȸ��:\n");
    print_info(&ptr, max_idx);

    // �޸� ����
    free_ary(&ptr, count);

    return 0;
}
