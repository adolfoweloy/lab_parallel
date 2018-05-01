OUTPUT=main
CC=gcc
BIN_DIR=bin

run: $(OUTPUT)
	./$(OUTPUT) 4 3 2

$(OUTPUT): $(OUTPUT).o
	$(CC) -Wall -g -o $(OUTPUT) $(OUTPUT).o -I. -lpthread

clean:
	rm -f *.o
	rm -f $(OUTPUT)
