//#include <stdio.h>
//
//struct address {
//    char name[20];
//    int age;
//    char tel[20];
//    char addr[80];
//};
//
//// print_list 함수 정의
//void print_list(struct address* plist, int size) {
//    for (int i = 0; i < 3; i++) {
//        printf("%s %5d %15s %20s\n", (plist+i)->name, (plist + i)->age, (plist + i)->tel, (plist + i)->addr);
//    }
//}
//
//int main() {
//    struct address list[3] = {
//        {"홍길동", 900, "010-0000-0000", "서울 강남구"},
//        {"강감찬", 700, "010-0000-0055", "서울 강북구"},
//        {"을지문덕", 600, "010-9999-0000", "서울 강남구 서초동"},
//    };
//    /*for (int i = 0; i < 3; i++) {
//     printf("%s %5d %15s %20s\n", list[i].name, list[i].age, list[i].tel, list[i].addr);
//  }*/
//    // print_list 함수 호출
//    print_list(list,3);
//
//    return 0;
//}
//
//  