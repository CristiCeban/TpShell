EXEC=shell.exe
SOURCES=shell.c
OBJECTS=$(SOURCES:.c=.o)
CC=gcc
CFLAGS=-W -Wall -std=gnu99 -g

.PHONY: default clean

defaul: $(EXEC)

shell.o: shell.c

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^

clean:
	rm -rf $(EXEC) $(OBJECTS) $(SOURCES)
