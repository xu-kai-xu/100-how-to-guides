
all: ball_clock

ball_clock: sqstack.o main.o queue.o
	$(CC) $^ -g -o $@

clean:
	rm -rf ball_clock *.o