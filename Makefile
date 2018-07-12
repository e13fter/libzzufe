CC := gcc

default: libzzufe

libzzufe:
	$(CC) -fPIC -c *.c
	ar cr libzzufe.a *.o
	ranlib libzzufe.a
	$(CC) -shared *.o *.h -lm -o libzzufe.so 

clean:
	rm *.o, libzzufe.a, libzzufe.so
