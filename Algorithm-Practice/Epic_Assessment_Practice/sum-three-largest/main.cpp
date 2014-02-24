#include <iostream>
using namespace std;
int tmp=0;
int sum=0,l=0,m=0,s=0;
void swap(int *a, int *b){
	int c = *a;
	*a = *b;
	*b = c;
}
int main(){
	int count=0;
	sum = l+m+s;
	cin >> tmp;
	while(tmp != 0){
		sum += tmp;
		if(tmp > l){
			swap(l,tmp);
		}
		if(tmp > m){
			swap(m,tmp);
		}
		if(tmp > s){
			swap(s,tmp);
		}
		count=count+1;
		cin >> tmp;
	}
	double ave = (sum-l-m-s)/(count-3.0);
	cout << l << endl;
	cout << m << endl;
	cout << s << endl;
	cout << ave << endl;
	return 0;
}
