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
		for line in lines:
			if(line.startswith('THREAD')):
				num_thread = line.split(' ')[1]
				if(num_thread != t):
					f1.write('\n' + num_thread + '\t')
					t = num_thread
				else:
					f1.write('\t\t')
			elif(line.startswith('real')):
				time = line.split()[1]
				f1.write(time)
			else:
				pass

		f1.close()

	except Exception, e1:
		print e1

if __name__ == '__main__':
	main(sys.argv[1:])