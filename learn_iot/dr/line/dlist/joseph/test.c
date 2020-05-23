#include "joseph.h"

int main(int argc, char *argv[])
{
	joselink H;
	H = create_jose();
	show_jose(H);
	int k,m;
	printf("input two num:");
	scanf("%d %d",&k, &m);
	out_jose(H, k, m);
	return 0;
}
