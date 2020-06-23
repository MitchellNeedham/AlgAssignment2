# Makefile for Assignment 2
#
# created for COMP20007 Design of Algorithms 2020
# written by Tobias Edwards <tobias.edwards@unimelb.edu.au>
# changes by <Insert Name Here>

# The compiler flags used when compiling
CFLAGS=-Wall -Wno-comment -std=c99 -lm

a2: main.o hash.o text_analysis.o linkedlist.o hashtable.o queue.o trie.o
	gcc $(CFLAGS) -o a2 main.o hash.o text_analysis.o linkedlist.o hashtable.o queue.o trie.o

main.o: main.c hash.h text_analysis.h queue.h
	gcc $(CFLAGS) -c main.c

hash.o: hash.c hash.h hashtable.h
	gcc $(CFLAGS) -c hash.c

text_analysis.o: text_analysis.c text_analysis.h linkedlist.h hashtable.h queue.h trie.h
	gcc $(CFLAGS) -c text_analysis.c

linkedlist.o: linkedlist.c linkedlist.h
	gcc $(CFLAGS) -c linkedlist.c

hashtable.o: hashtable.c hashtable.h
	gcc $(CFLAGS) -c hashtable.c

queue.o: queue.c queue.h
	gcc $(CFLAGS) -c queue.c

trie.o: trie.c trie.h linkedlist.h
	gcc $(CFLAGS) -c trie.c

# Add or update any of these rules to include additional files/modules you may
# include. You can add additional compiler flags as well, however you should
# not remove the -Wall flag.

# This .PHONY command declares the "clean" rule as a phony one, i.e., it means
# that the clean rule will run instructions but it wont create a file called
# "clean" like a normal rule would (e.g., the util.o rule results in a file
# called util.o being created).
.PHONY: clean

clean:
	rm *.o
	rm a2
