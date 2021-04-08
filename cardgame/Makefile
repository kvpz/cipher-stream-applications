WARN	:= -W -Wall -Wconversion -pedantic
INCLUDE	:= -O2
CC	:= gcc
LIB	:= ../lib

ALL: cardgame.x

cardgame.x: cardgame_main.c ../lib/deck.c ../lib/card.c player.c ../lib/linkedlist.c shuffler.c ../lib/ciphersuite.c
	@echo "building target cardgame.x"
	$(CC) $(INCLUDE) $(WARN) -ggdb -I$(LIB) -I. cardgame_main.c ../lib/deck.c player.c ../lib/linkedlist.c shuffler.c ../lib/utility.c ../lib/set.c ../lib/ciphersuite.c ../lib/card.c -o cardgame.x

run:
	./cardgame.x

clean:
	rm -rf ${TARGET}.o
