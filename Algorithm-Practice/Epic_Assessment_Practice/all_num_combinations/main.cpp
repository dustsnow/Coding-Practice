#include <stdio.h>
#include <iostream>
#include <stdlib.h>
using namespace std;
void itoa(int num, char *numarr){
	sprintf(numarr,"%d", num);
}

void Increment(char *numArr){
	char buf[sizeof(numArr)/sizeof(numArr[0])];
	int tmpNum = atoi(numArr);
	tmpNum++;
	itoa(tmpNum,numArr);
}
bool ValidNum(char *numArr,int len){
	int tmp[10];
	for(int i = 0; i < 10; i++){
		tmp[i]=0;
	}
	for(int i = 1; i < len; i++){
		tmp[numArr[i]-'0']++;
		if(tmp[numArr[i]-'0'] > 1){
			return false;
		}
	}
	return true;
}
int main(){
	int inputNum;
	cin >> inputNum;
	char currentNum[inputNum+1];
	char minNum[inputNum+1];
	char maxNum[inputNum+1];
	maxNum[0] = '1';
	minNum[0] = '1';
	currentNum[0] = '1';
	for(int i = 1; i <= inputNum; i++){
		currentNum[i] = '0';
		minNum[i] = '0';
		maxNum[i] = '9';
	}
	while(atoi(currentNum) <= atoi(maxNum)){
		Increment(currentNum);	
		if(ValidNum(currentNum,sizeof(currentNum)/sizeof(currentNum[0]))){
			currentNum[0] = 32;
			cout << (currentNum) << endl;
			currentNum[0] = '1';
		}
	}
	return 0;
}
