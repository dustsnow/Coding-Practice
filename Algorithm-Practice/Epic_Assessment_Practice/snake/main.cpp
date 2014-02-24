#include <stdio.h>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

typedef struct{
	int x;
	int y;
}Point;
typedef struct Node Node;
struct Node{
	Point parent;
	Point self;
	int value;
	int length;
	Node *selfPtr;
	Node *parentPtr;
};
typedef struct{
	vector<Node> nodes;
	int length;
}Path;

stack<Node*> stackNode;
vector<Node> nodes;
//int maze[6][6] = {{0,0,0,0,0,0},{0,20,45,11,12,0},{0,6,7,10,13,0},{0,31,8,9,27,0},{0,0,1,6,7,0}};
//int maze[6][6] = {{0,0,0,0,0,0},{0,20,8,11,12,0},{0,6,7,10,13,0},{0,31,8,9,27,0},{0,0,1,6,7,0}};
int maze[6][6] = {{0,0,0,0,0,0},
				  {0,20,8,11,12,0},
				  {0,6,7,10,13,0},{0,31,8,9,27,0},{0,0,1,10,7,0},{0,0,0,0,0,0}};
int maze2[3] = {4,5,3};

void FindNext(Node currNode){
	bool found=false;

	Node *tmpNode = new Node;
	tmpNode->self.x = currNode.self.x-1;
	tmpNode->self.y = currNode.self.y;
	tmpNode->value = maze[tmpNode->self.x][tmpNode->self.y];
	if(tmpNode->value == currNode.value+1) {
		tmpNode->parent = currNode.self;
		tmpNode->length = currNode.length+1;
		tmpNode->selfPtr = tmpNode;
		tmpNode->parentPtr = currNode.selfPtr;
		stackNode.push(tmpNode);
		found = true;
	}


	tmpNode = new Node;
	tmpNode->self.x = currNode.self.x+1;
	tmpNode->self.y = currNode.self.y;
	tmpNode->value = maze[tmpNode->self.x][tmpNode->self.y];
	if(tmpNode->value == currNode.value+1) {
		tmpNode->parent = currNode.self;
		tmpNode->length = currNode.length+1;
		tmpNode->selfPtr = tmpNode;
		tmpNode->parentPtr = currNode.selfPtr;
		stackNode.push(tmpNode);
		found = true;
	}


	tmpNode = new Node;
	tmpNode->self.x = currNode.self.x;
	tmpNode->self.y = currNode.self.y-1;
	tmpNode->value = maze[tmpNode->self.x][tmpNode->self.y];
	if(tmpNode->value == currNode.value+1) {
		tmpNode->parent = currNode.self;
		tmpNode->length = currNode.length+1;
		tmpNode->selfPtr = tmpNode;
		tmpNode->parentPtr = currNode.selfPtr;
		stackNode.push(tmpNode);
		found = true;
	}


	tmpNode = new Node;
	tmpNode->self.x = currNode.self.x;
	tmpNode->self.y = currNode.self.y+1;
	tmpNode->value = maze[tmpNode->self.x][tmpNode->self.y];
	if(tmpNode->value == currNode.value+1) {
		tmpNode->parent = currNode.self;
		tmpNode->length = currNode.length+1;
		tmpNode->selfPtr = tmpNode;
		tmpNode->parentPtr = currNode.selfPtr;
		stackNode.push(tmpNode);
		found = true;
	}
	while(!stackNode.empty()){
		tmpNode = stackNode.top();
		stackNode.pop();
		nodes.push_back(*tmpNode);
		FindNext(*tmpNode);
	}
}
void FindLongest(){
	Node tmpNode;
	tmpNode.length=0;
	for(int i = 0; i != nodes.size(); i++){
		if(nodes[i].length > tmpNode.length){
			tmpNode = nodes[i];
		}
	}
	for(int i = 0; i != tmpNode.length; i++){
		cout << tmpNode.self.x << " " << tmpNode.self.y << endl;
		if(tmpNode.selfPtr == tmpNode.parentPtr){
			return;
		}
		tmpNode = *(tmpNode.parentPtr);
	}
}
int main(){
	Node root;
	root.parent.x=2;root.parent.y=1;
	root.self.x=2;root.self.y=1;
	root.length=0;
	root.value=maze[root.parent.x][root.parent.y];
	root.parentPtr = &root;
	root.selfPtr = &root;
	nodes.push_back(root);	
	FindNext(root);
	FindLongest();
}
