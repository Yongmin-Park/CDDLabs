

# % is matching
# checks the date and time

# -c it's not full compiling
# -o out file name

CC = g++
CFLAGS= -std=c++11 -pthread

HFILES = Semaphore.h
CFILES = Semaphore.cpp Mutex.cpp
OUTFILE = Mutex

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

ALL: $(HFILES) $(CFILES)
	$(CC) -o $(OUTFILE) $(CFILES) $(HFILES) $(CFLAGS) $(DEBUGFLAGS)

DEBUG: DEBUGFLAGS = -DDEBUG

CLEAN:
	rm *.o
