CC = gcc
CFLAGS := -g

OBJ := my_malloc.o test.o
all: $(OBJ)
	$(CC) $(CFLAGS) $^ -o main
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
clean:
	rm main *.o
