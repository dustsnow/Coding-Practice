#include "lcg.h"
#include <iostream>
int main(){
	LCG lcg(999);
	for(int i = 0; i < 14; i++){
		std::cout << lcg.rand(100) <<std::endl;
	}
	return 0;
}
