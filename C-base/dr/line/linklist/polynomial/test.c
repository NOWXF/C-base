#include <stdio.h>
#include <stdlib.h>
#include "poly.h"

int main(int argc, char *argv[])
{
	polylink A,B,C;
	A = create_poly();
	B = create_poly();
	while(1){
		data_t temp;
		printf("input two num(0 0 exit):");
		scanf("%d %d",&temp.coe, &temp.exp);
		if(temp.coe == 0 && temp.exp == 0)
			break;
		insert_poly(A, temp);
		show_poly(A);
	}
	while(1){
		data_t temp;
		printf("input two num(0 0 exit):");
		scanf("%d %d",&temp.coe, &temp.exp);
		if(temp.coe == 0 && temp.exp == 0)
			break;
		insert_poly(B, temp);
		show_poly(B);
	}
	C=merge_poly(A, B);
	show_poly(C);
	return 0;
}
