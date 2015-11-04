#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TOTAL_POINTS 100000
#define NUM_THREADS 4

int main(int argc, char *argv[])
{
    int i = 0, circle_points = 0, total_points = TOTAL_POINTS;
    int num_threads = NUM_THREADS;
    double x = 0.0, y = 0.0, pi = 0.0;

    if(argc == 3) {
        total_points = atoi(argv[1]);
        num_threads = atoi(argv[2]);
    }

    omp_set_num_threads(num_threads);

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
        // printf("\n\nTHREADS: %d\n", omp_get_num_threads());
    }
    pi = (double)4 * (double)circle_points / (double)total_points;
    // printf("Pi = %f\n", pi);
    printf("\n\nTHREADS: %d\n", num_threads);
    printf("TOTAL: %d\n", total_points);
    return 0;
}