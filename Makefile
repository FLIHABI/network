CC=gcc
CFLAGS=-Wall -Wextra

all: broadcaster listener

clean:
	rm -rf *.o broadcaster listener

.PHONY: clean all
