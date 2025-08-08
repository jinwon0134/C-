//#include <stdio.h>
//
//struct node {
//	int num;
//	struct node* next;
//};
//
//void main() {
//	struct node n = { 10,0 }, n1 = { 20,0 }, n2 = { 30,0 };
//	struct node* head = &n;
//	n.next = &n1;
//	n1.next = &n2;
//
//	printf("head->num: %d\n", head->num);
//	printf("head->next->num: %d\n", head->next->num);
//	printf("head->next->next->num: %d\n", head->next->next->num);
//
//
//	return 0;
//}