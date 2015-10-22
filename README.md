# trabalho-ippd
trabalho de ippd

Compilar openmp

gcc -fopenmp <arquivo.c> -o <nomedasaida>

Compilar openmpi

mpicc <arquivo.c> -o <nomedasaida>

Compilar openmpi + openmp

mpicc -fopenmp <arquivo.c> -o <nomedasaida>

(Considerando como wrapper o gcc)

Executar mpi

mpirun -n <numerodeprocessos> ./<nomedoexecgerado> [arg1, arg2,...]
