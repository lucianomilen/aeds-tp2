#LUCIANO OTONI MILEN [2012079754]
CC = gcc
CFLAGS = -g -Wall -std=c99
demo: levenshtein.o
	$(CC) $(CFLASGS) main.c levenshtein.c -o tp2
