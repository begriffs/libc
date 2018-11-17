#include <stdio.h>

double a[] = {1.0, 2.0};

double sqr(double x) { return x*x; }

int main(void)
{
	double *p = a;
	#define sqr(x) x*x
	printf("%lf %d %d %d %lf %lf\n",
			sqr(3.0), sqr(3), sqr(3+3),
			!sqr(3), sqr(*p++), (sqr)(3+3));

	p = a;
	#define sqr(x) (x)*(x)
	printf("%lf %d %d %d %lf %lf\n",
			sqr(3.0), sqr(3), sqr(3+3),
			!sqr(3), sqr(*p++), (sqr)(3+3));

	return 0;
}
