//#include <stdio.h> 
//int main()
//{
//    int score[3][4];  // 3명의 학생, 4과목 점수
//    int total;
//    double avg;
//
//    // 점수 입력 받기
//    for (int i = 0; i < 3; i++) {
//        printf("%d의 4과목 점수를 입력하세요: ", i + 1);
//        for (int j = 0; j < 4; j++) {
//            scanf_s("%d", &score[i][j]);
//        }
//    }
//
//    for (int i = 0; i < 3; i++) {
//        total = 0;
//        for (int j = 0; j < 4; j++) {
//            total += score[i][j];
//        }
//        avg = total / 4.0;
//        printf("학생 %d - 총점: %d, 평균: %.2f\n", i + 1, total, avg);
//    }
//
//    return 0;
//}
