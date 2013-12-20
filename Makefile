# Cratyle Makefile
CFLAGS = -O2 -Wall -g
CC = gcc

all : Cratyle

Cratyle: cratyle.o libcratyle.o libminitel.o cratyledico.o cratyledico_genrenombre.o testunitaire.o testunitaire.c
	$(CC) $(CFLAGS) -o Cratyle cratyle.o libcratyle.o libminitel.o cratyledico.o cratyledico_genrenombre.o testunitaire.o
