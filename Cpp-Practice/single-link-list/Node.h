#ifndef Node_H
#define Node_H
class Node{
	public:
		Node(int value):next(NULL),data(value){}
		void setNext(Node *next){
		//	this->next = next;
		}
		void setData(int value){
		//	this->data = value;
		}
		int getData(){
		//	return this->data;
		}
		Node* getNext(){
		//	return next;
		}
	private:
		Node *next;
		int data;
};
#endif
