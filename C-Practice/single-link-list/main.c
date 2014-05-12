#include <stdlib.h>
#include <stdio.h>

struct ListElement{
	struct ListElement *next;
	int data;
};
typedef struct ListElement ListElement;

int main(int argv, char** args){
	printf("hello\n");
	struct ListElement a;
	struct ListElement b;
	ListElement c;
	a.data = 10;
	a.next = &b;
	b.data = 20;
	b.next = &c;
	c.data = 30;
	printf("c %d\n", b.next->data);
}
