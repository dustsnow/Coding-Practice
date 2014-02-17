#include <stdio.h>

int gcd(int u, int v){
	int t;
	while(u > 0){
		if(u < v){
			t = u;
			u = v;
			v = t;
		}
		u = u-v;
	}
	return v;
}
int main(int argc, char** argv){
	int u = 8;
	int v = 6;
	printf("%d, %d, %d\n",u,v,gcd(u,v));
}
