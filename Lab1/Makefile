# Yongmin Park

CC = g++
CFLAGS= -std=c++11 -pthread

HFILES = Semaphore.h
CFILES = Semaphore.cpp signal.cpp
OUTFILE = signal

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

ALL: $(HFILES) $(CFILES)
	$(CC) -o $(OUTFILE) $(CFILES) $(HFILES) $(CFLAGS) $(DEBUGFLAGS)

DEBUG: DEBUGFLAGS = -DDEBUG

CLEAN:
	rm *.o
