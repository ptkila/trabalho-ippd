#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "omp.h"

#define NUM_THREADS 8
#define NUM_ITER INT_MAX

int monte_carlo_partition(int end_value) {

  int i = 0;
  int circle_points = 0;  // Quantidade de pontos que se encontram dentro do circulo
  double x = 0.0, y = 0.0;  // Pontos a serem determinados pelo metodo usado
  double z = 0.0; // Valor que define se um ponto se encontra dentro de um circulo

  srandom((int)time(NULL)); // Gerador de numeros pseudo aleatorios

  // num_threads se refere a quantidade de threads usadas nos testes iniciais 
  #pragma omp parallel private(x, y) reduction(+:circle_points) num_threads(NUM_THREADS)
  {
    #pragma omp for
    for (i = 0; i < end_value; i++) {
      x = (double)random() / (double)RAND_MAX;  // Funcao usada para calcular os pontos, RAND_MAX sera sempre maior ou
      y = (double)random() / (double)RAND_MAX;  // igual a Random, fazendo o resultado variar de 0 a 1
      z = sqrt((x * x) + (y * y));  // Calculo da localizacao do ponto
      if (z <= 1.0) { circle_points++; }  // Determina se faz parte do circulo
    }
  }
  return circle_points;
}

int main(int argc, char** argv) {

  MPI_Status status;  // Recebe quem enviou a mensagem e seu tag
  int i = 0, proc = 0;
  int circle_points = 0;  // Valor total usado no calculo final
  int circle_points_part = 0; // Valor recebido de cada interação com MPI 
  int num_iter = NUM_ITER;  // Quantidade de iteracoes usadas no teste
  int num_proc = 0, proc_id = 0;  // Quantidade e ids dos processos que serao usados
  int master = 0, tag = 1313; // Variaveis necessarias para o MPI
  double pi = 0.0;  // Variavel que recebe o resultado final

  // Inicializacao do MPI
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &num_proc);
  MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);

  // Particoes serao o total de iteracoes dividido pelo numero de processos menos um que recebe o resultado final
  int part = num_iter / (num_proc - 1);

  // Dependendo da id do processo sera feito Send ou Recv
  if (proc_id == 0) { // Processo usado para receber o resultado da execucao

    for (proc = 1; proc < num_proc; proc++) {
      MPI_Recv(&circle_points_part, 1, MPI_REAL, proc, tag, MPI_COMM_WORLD, &status);
      circle_points += circle_points_part;
    }
    pi = (double)circle_points / (double)num_iter * (double)4.0;  // Funcao usada na especificacao do trabalho
    printf("Pi = %f\n", pi);

  } else {

    circle_points_part = monte_carlo_partition(part);
    MPI_Send(&circle_points_part, 1, MPI_REAL, master, tag, MPI_COMM_WORLD);

  }
  MPI_Finalize(); // Termina o MPI
}