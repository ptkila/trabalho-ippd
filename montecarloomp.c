#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NUM_THREADS 4   // Define o numero de threads

int main(int argc, char *argv[])
{
    int i = 0;
    int circle_points = 0;  // Quantidade de pontos que se encontram dentro do circulo
    int total_points = 100000;  // Total de pontos calculados, valor usado nos testes iniciais
    int num_threads = NUM_THREADS;  // Seta a variavel num_threads com o numero de threads definido
    double x = 0.0, y = 0.0;    // Pontos a serem determinados pelo metodo usado
    double pi = 0.0;    // Variavel que recebe o resultado final

    omp_set_num_threads(num_threads);   // Seta o numero de threads a ser utilizado

    // Os valores de x e y não devem se compartilhadas por isso são passados como private, entretanto o valor de 
    //circle_points deve ser recebido 
    //como a soma de todos os valores encontrados para essa variavel, portanto é usado reduction
    #pragma omp parallel private(x, y) reduction(+:circle_points)
    {
        #pragma omp for
        for (i = 0; i < total_points; i++) {
            x = drand48();  // Funcao usada para calcular valores entre 0 e 1
            y = drand48();  //com ela a velocidade de execução aumenta, entretanto a precisão acaba sendo reduzida
            if (x * x + y * y <= 1) {
                circle_points++;    // Se o valor gerado se encontra no circulo, adiciona esse número na variavel usada no calculo
            }
        }
    }
    pi = (double)4 * (double)circle_points / (double)total_points;  // Funcao usada na especificacao do trabalho
    printf("Pi = %f\n", pi);
    return 0;
}