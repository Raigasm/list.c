# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS = -g -Wall -o3 -std=c99

default: all

all: filelist.o findfile.o main.o 
	$(CC) $(CFLAGS) -o findfile findfile.o main.o 

test: filelist.o findfile.o test.o
	$(CC) $(CFLAGS) -o findfile filelist.o findfile.o test.o

findfile.o: debugprint.h minunit.h findfile.h findfile.c
	$(CC) $(CFLAGS) -o findfile.o findfile.c -c

filelist.o: debugprint.h minunit.h filelist.h filelist.c
	$(CC) $(CFLAGS) -o filelist.o filelist.c -c

test.o: debugprint.h minunit.h filelist.h filelist.c findfile.h test.c
	$(CC) $(CFLAGS) -o test.o test.c -c
