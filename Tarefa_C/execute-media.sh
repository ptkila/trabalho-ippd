for i in 0 1 2 4 8 16 32 64
do
	for j in {1..10}
	do
		time ./out 10000 $i
	done
	for j in {1..10}
	do
		time ./out 100000 $i
	done
	for j in {1..10}
	do
		time ./out 1000000 $i
	done
	for j in {1..10}
	do
		time ./out 10000000 $i
	done
done