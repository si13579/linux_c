build : main.o list.o 
	gcc -o build $^ -lm
main.o : main.c list.h
	gcc -g -c $^ 
clean : 
	rm *.o