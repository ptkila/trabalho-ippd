#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "omp.h"

#define NUM_THREADS 8
#define NUM_ITER INT_MAX

int monte_carlo_partition(int end_value) {

  int i = 0, circle_points = 0;
  double x = 0.0, y = 0.0, z = 0.0;

  srandom((int)time(NULL));

  #pragma omp parallel private(x, y) reduction(+:circle_points) num_threads(NUM_THREADS)
  {
    #pragma omp for
    for (i = 0; i < end_value; i++) {
      x = (double)random() / (double)RAND_MAX;
      y = (double)random() / (double)RAND_MAX;
      z = sqrt((x * x) + (y * y));
      if (z <= 1.0) { circle_points++; }
    }
  }
  return circle_points;
}

int main(int argc, char** argv) {

  MPI_Status status;
  int i = 0, proc = 0;
  int circle_points = 0, circle_points_part = 0, num_iter = NUM_ITER;
  int num_proc = 0, proc_id = 0;
  int master = 0, tag = 1313;
  double pi = 0.0;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &num_proc);
  MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);

  int part = num_iter / (num_proc - 1);

  if (proc_id == 0) {

    for (proc = 1; proc < num_proc; proc++) {
      MPI_Recv(&circle_points_part, 1, MPI_REAL, proc, tag, MPI_COMM_WORLD, &status);
      circle_points += circle_points_part;
    }
    pi = (double)circle_points / (double)num_iter * (double)4.0;
    printf("Pi = %f\n", pi);

  } else {

    circle_points_part = monte_carlo_partition(part);
    MPI_Send(&circle_points_part, 1, MPI_REAL, master, tag, MPI_COMM_WORLD);

  }
  MPI_Finalize();
}