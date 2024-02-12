test.exe : test.c BigInt.h BigInt.o
	gcc -std=c99 -o test.exe test.c BigInt.o

BigInt.o : BigInt.c BigInt.h
	gcc -c -std=c99 BigInt.c