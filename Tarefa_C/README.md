Como funciona a tarefa C:

Assumindo que a compilacao foi feita da forma a gerar um executavel chamado "out", ou seja, compilado dessa forma:

gcc -fopenmp montecarloomp-script.c -o out

Os passos feitos foram:
1) Executar o script execute.sh:

chmod 755 execute.sh
./execute.sh

2) Copiar a saida do terminal para um arquivo txt, por exemplo, "result.txt"

3) Rodar o script parser.py para gerar um novo arquivo com a tabela (nese caso chamei o arquivo de "table.txt"):

python parser.py result.txt table.txt