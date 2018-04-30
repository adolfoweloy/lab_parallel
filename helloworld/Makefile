OUTPUT=main
CC=gcc
CFLAGS=-I.
BIN_DIR=bin

run: $(OUTPUT)
	./$(OUTPUT) 10

$(OUTPUT): $(OUTPUT).o
	$(CC) -Wall -g -o $(OUTPUT) $(OUTPUT).o -I -lpthread.

clean:
	rm -f *.o
	rm -f $(OUTPUT)
