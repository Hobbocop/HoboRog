CC = gcc
CFLAGS = -lpdcurses -I$(IDIR)

IDIR = ./include/
SRCDIR = ./src/

SOURCES = $(SRCDIR)*.c

all: rogue run

rogue:	$(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -o $@

run:
	./rogue

clean:
	rm ./*.exe