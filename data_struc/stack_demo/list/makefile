current_dir := $(CURDIR)

all: stack

stack: llist.o stack.o main.o
	gcc stack.o llist.o main.o -o stack

llist.o: $(CURDIR)/lib2/llist.c
	gcc $(CURDIR)/lib2/llist.c -c -o llist.o

stack.o: stack.c
	gcc stack.c -c -o stack.o

main.o: main.c
	gcc main.c -c -o main.o



clean:
	rm stack *.o -rf