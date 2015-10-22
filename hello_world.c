#include <mpi.h>
#include <stdio.h>
#include "omp.h"

int main(int argc, char** argv) {

  int i = 0, circle_points = 0, total_points = 100000;
  double x = 0.0, y = 0.0, pi = 0.0;

  // Inicializa o ambiente
  MPI_Init(NULL, NULL);

  // Pega o num de proc e seta o tam do com
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // Pega o rank dos proc
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  // Pega o nome do processador
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int name_len;
  MPI_Get_processor_name(processor_name, &name_len);

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

  MPI_Finalize();
}