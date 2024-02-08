all: sqstack
sqstack: sqstack.o main.o
	$(CC) $^ -O0 -g -o $@

clean:
	rm sqstack *.o -rf