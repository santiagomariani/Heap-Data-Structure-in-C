#include <stdio.h>

int cmpint(const void *a,const void *b){
	int valor1 = *(int*)a;
	int valor2 = *(int*)b;

	if(valor1 == valor2) return 0;

	if(valor1 < valor2) return -1;

	return 1;
}

int main(void){

	int valor1 = 1;
	int valor2 = 2;
	int valor3 = 1;

	if(cmpint(&valor1,&valor2) < 0){
		printf("bien");
	}

	return 0;
}