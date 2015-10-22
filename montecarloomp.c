#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char *argv[])
{
    int i = 0, circle_points = 0, total_points = 100000;
    double x = 0.0, y = 0.0, pi = 0.0;

    #pragma omp parallel private(x, y) reduction(+:circle_points)
    {
        #pragma omp for
        for (i = 0; i < total_points; i++) {
            x = drand48();
            y = drand48();
            if (x * x + y * y <= 1) {
                circle_points++;
            }
        }
    }
    pi = (double)4 * (double)circle_points / (double)total_points;
    printf("Pi = %f\n", pi);
    return 0;
}