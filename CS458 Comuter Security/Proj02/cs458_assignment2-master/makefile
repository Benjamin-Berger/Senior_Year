GPP = g++ -g -std=c++11 -lcrypto

all: fscrypt test

fscrypt: fscrypt.o main.o
	$(GPP) fscrypt.o main.o -o fscrypt

main.o: main.cpp
	$(GPP) -c main.cpp

fscrypt.o: fscrypt.cpp
	$(GPP) -c fscrypt.cpp

test.o: test.cpp
	$(GPP) -c test.cpp

clean:
	rm -f *.o *~core fscrypt test

test: fscrypt.o test.o
	$(GPP) fscrypt.o test.o -o test
