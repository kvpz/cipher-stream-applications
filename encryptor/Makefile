TARGET 	:= project2
WARN	:= -W -Wall -Wconversion -pedantic
INCLUDE	:= -O2
CC	:= gcc
LIB	:= ../lib

ALL: encryptor.x

encryptor.x: encryptor.c
	@echo "building target encryptor.x"
	$(CC) $(INCLUDE) $(WARN) -ggdb -I../lib ../lib/set.c ../lib/ciphersuite.c encryptor.c ../lib/utility.c ../lib/linkedlist.c ../lib/deck.c ../lib/card.c -o encryptor.x

clean:
	rm -rf ${TARGET}.o
