#include <stdlib.h>
#include <stdio.h>

int main(){
	char arr[][5] = {'i','l','o','v','e',
					'd','i','n','t','e',
					'n','e','w','e','p',
					'a','i','v','r','i',
					'm','a','x','e','c'};
	int i, j,k=0,size = 5;
	for(i = size-1,j=0;i>j;i--,j++){
		for(k=j;k<=i;k++) printf("%c",arr[j][k]);
		for(k=j+1;k<=i;k++) printf("%c",arr[k][i]);
		for(k=i-1;k>=j;k--) printf("%c",arr[i][k]);
		for(k=i-1;k>j;k--) printf("%c",arr[k][j]);
	}
	printf("%c",arr[(size-1)/2][(size-1)/2]);
}
