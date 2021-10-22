OBJS=main.o tool1.o tool2.o
CC=gcc

mytool:$(OBJS)
	$(CC) $^ -o $@

%.o:%.c
	$(CC) $^ -c -o $@
clean:
	$(RM) *.o mytool -r
