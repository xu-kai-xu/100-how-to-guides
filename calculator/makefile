
all: sqstack

sqstack: sqstack.o main.o
	$(CC) $^ -g -o $@

clean:
	rm -rf sqstack *.o