#include <cstdio>
#include <iostream>
#include "Node.h"
using namespace std;
//class Node{
//	public:
//		Node(int value):next(NULL),data(value){}
//		void setNext(Node *next){
//			this->next = next;
//		}
//		void setData(int value){
//			this->data = value;
//		}
//		int getData(){
//			return this->data;
//		}
//		Node* getNext(){
//			return next;
//		}
//	private:
//		Node *next;
//		int data;
//};
int main(){
	cout << "Hello" << endl;
	Node a(10);
	Node b(20);
	a.setNext(&b);
	cout << "b " << a.getNext()->getData() << endl;
}
