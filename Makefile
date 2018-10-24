CC = g++
CFLAGS = -g -c -std=c++11
.C.o:
	$(CC) $(CFLAGS) $< -o $@

all:
	scl enable devtoolset-3 '/bin/bash --rcfile <(echo "make csim; exit")'

csim: csim.o Cache.o Simulate.o

Cache.o: Cache.h

csim.o: Cache.h Simulate.h

Simulate.o: Cache.h Simulate.h

#
# Clean the src dirctory
#
clean:
	rm -rf *.o
	rm -f csim
