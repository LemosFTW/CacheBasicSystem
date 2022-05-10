# Compilation flags
CFLAGS=-c -I. -g

# .c files
SOURCES=$(wildcard *.c)

# .h files
HEADERS=$(wildcard *.h)

# Object files
OBJS=$(SOURCES:.c=.o)

all: tpc6

tpc6: $(OBJS)
	cc -o $@ $^

%.o: %.c %.h
	cc -o $@ $< $(CFLAGS)



clean:
	rm -f $(OBJS)

.PHONY: all clean