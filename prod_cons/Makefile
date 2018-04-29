OUTPUT=main
CC=gcc
CFLAGS=-I.
BIN_DIR=bin

run: $(OUTPUT)
	./$(OUTPUT)

$(OUTPUT): $(OUTPUT).o
	$(CC) -o $(OUTPUT) $(OUTPUT).o -I.

clean:
	rm -f *.o
	rm -f $(OUTPUT)
