import sys

def main(argv):
	try:
		f = open(argv[0], 'r')
		lines = f.read().splitlines()
		f.close()

	except Exception, e:
		print e

	try:
		f1 = open(argv[1], 'w')

		f1.write('\t10000\t\t\t100000\t\t\t1000000\t\t\t10000000')

		t = 0
		t1 = '10000'
		soma = 0.0;
		cont = 0
		flag = False
		for line in lines:
			if(line.startswith('THREAD')):
				num_thread = line.split(' ')[1]
				if(num_thread != t):
					f1.write('\n' + num_thread + '\t')
					t = num_thread
					flag = True
				# else:
				# 	f1.write('\t\t')
			elif(line.startswith('TOTAL')):
				total = line.split(' ')[1]
				if(total != t1):
					soma = 0.0
					cont = 1
					# if(not flag):
					# 	f1.write('\t\t\t')
					# 	flag = False
					t1 = total
				else:
					cont += 1
			elif(line.startswith('real')):
				time = line.split()[1]
				time = time.split('m')[1]
				time = time.split('s')[0]
				time = float(time)

				soma += time
				# print soma

				if(cont == 10):
					media = soma / 10.0
					# print type(media)
					f1.write(str(media) + 's\t\t\t')
			else:
				pass

		f1.close()

	except Exception, e1:
		print e1

if __name__ == '__main__':
	main(sys.argv[1:])