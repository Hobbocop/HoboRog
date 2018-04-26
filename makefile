CC = gcc
CFLAGS = -lpdcurses -I$(IDIR)

IDIR = ./include/
SRCDIR = ./src/

SOURCES = 	$(SRCDIR)*.c\
			$(SRCDIR)../utils/*.c

all: rogue run

rogue:	$(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -o $@

run:
	./rogue

clean:
	rm ./*.exe