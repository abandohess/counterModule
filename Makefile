# Makefile for 'counters' module
#
# Anders Bando-Hess, April 2017

PROG = counterstest
OBJS = counterstest.o counters.o ../common/readlinep.o ../common/memory.o 
LIBS =

# uncomment the following to turn on verbose memory logging
# TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../common
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

countertest.o: counters.h ../common/readlinep.h
counter.o: counters.h
readline.o: ../common/readlinep.h

.PHONY: clean

clean:
	rm -f *~ *.o *.dSYM
	rm -f $(PROG)
	rm -f stocks
