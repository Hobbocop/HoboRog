CC = gcc
CFLAGS = -lncursesw -lmenuw -I$(IDIR) -g

IDIR = ./include/
SRCDIR = ./src/

SOURCES = 	$(SRCDIR)*.c\
			$(SRCDIR)utils/*.c\
			$(SRCDIR)windows/*.c

all: rogue

rogue:	$(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -o $@

run:
	./rogue

clean:
	rm ./*.exe