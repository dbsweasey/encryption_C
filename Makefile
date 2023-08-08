CC = gcc
CFLAGS = -Wall -std=c99 -g 

all: encrypt decrypt aesTest fieldTest

encrypt: io.o aes.o field.o encrypt.o 
	gcc io.o aes.o field.o encrypt.o -o encrypt

encrypt.o: encrypt.c io.h aes.h field.h

decrypt: io.o aes.o field.o decrypt.o
	gcc io.o aes.o field.o decrypt.o -o decrypt

decrypt.o: decrypt.c io.h aes.h field.h

fieldTest: fieldTest.o field.o
	gcc fieldTest.o field.o -o fieldTest

fieldTest.o: fieldTest.c field.h

aesTest: aesTest.o aes.o field.o
	gcc aesTest.o aes.o field.o -o aesTest

aesTest.o: aesTest.c aes.h field.h

io.o: io.c io.h field.h
aes.o: aes.c aes.h field.h
field.o: field.c field.h

clean:
	rm -f encrypt.o decrypt.o io.o aes.o field.o aesTest.o fieldTest.o
	rm -f encrypt decrypt aesTest fieldTest
	rm -f output.dat output.txt stderr.txt