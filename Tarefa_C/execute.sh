for i in 1 2 4 8 16 32 64
do
	time ./out 10000 $i
	time ./out 100000 $i
	time ./out 1000000 $i
	time ./out 10000000 $i
done