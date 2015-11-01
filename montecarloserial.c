# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <math.h>

int main(int argc, char *argv[])
{
	int total_points = 1000;
	int circle_points = 0;
	int i = 0;
	double x, y, resultado;

	srand( time( NULL ) );

	for (i = 0; i < total_points; i++)
	{
		x = (double) rand() / (double)RAND_MAX;
		y = (double) rand() / (double)RAND_MAX;

		if (x * x + y * y <= 1)
		{
			circle_points++;
		}
	}

	resultado = (((double)4 * (double)circle_points) / (double)total_points);
	printf("PI = %lf\n", resultado);

	return 0;
}