#include <stdio.h>
#include <math.h>

#define N 10
#define _DEBUG_

int main()
{
	double m,n;
	m += N;
	n = sqrt(m);

#ifdef _DEBUG_
	printf("debug:%lf,%lf\n",m,n);
#else
	printf("relase:%lf,%lf\n",m,n);
#endif
	return 0;
}
