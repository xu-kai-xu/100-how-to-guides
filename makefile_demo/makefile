OBJS = main.o tool_1.o tool_2.o
CC = gcc
CFLAGS += -c -Wall -g

mytool: $(OBJS)
	$(CC) $^ -o $@

%.o : %.c
	$(CC) $^ $(CFLAGS) -o $@

#main.o: main.c
#	$(CC) $^ $(CFLAGS) -o $@

#tool_1.o: tool_1.c
#	$(CC) $^ $(CFLAGS) -o $@

#tool_2.o: tool_2.c
#	$(CC) $^ $(CFLAGS) -o $@

clean:
	$(RM) *.o mytool

# 分清楚依赖和被依赖关系
