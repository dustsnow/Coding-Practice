#include <iostream>
enum tower {A='A',B='B',C='C'};

void Hanoi1(int n, tower x, tower y, tower z){

	if(n){
		Hanoi1(n-1,x,z,y);
		std::cout << "Move top disk from tower " << char(x) << " to top of tower " << char(y) << std::endl;
		Hanoi1(n-1,z,y,x);
	}
}
/**
 *
 * Imagine there're only two disks, small one and large one. 
 * When disks number increase, treat all disks other than the largest one as one disk so that we go
 * back to the case "small one and large one"
 *
 **/
void Hanoi2(int n, tower x, tower y, tower z){
	if(n == 1){
		std::cout << "Move disk from " << char(x) << " to " << char(z) << std::endl;
	}
	else{
		Hanoi2(n-1, x, y, z);//Move smaller one
		Hanoi2(1, x, z, y);//Move larger one
		Hanoi2(n-1, z, x, y);//Move smaller one
	}
}
int main(){
	tower x = A;
	tower y = B;
	tower z = C;
	Hanoi2(2,x,y,z);

	return 0;
}
