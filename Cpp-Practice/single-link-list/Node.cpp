#include "Node.h"
Node::Node(int value):next(NULL),data(value){}

void Node::setNext(Node *next){
	this->next = next;
}
void Node::setData(int value){
	this->data = value;
}
int Node::getData(){
	return this->data;
}
Node* Node::getNext(){
	return next;
}

