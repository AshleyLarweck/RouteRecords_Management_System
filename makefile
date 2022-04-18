myProgram: main.o RouteRecords.o
	gcc main.o RouteRecords.o -o myProgram
main.o: main.c RouteRecords.h
	gcc -c main.c -o main.o
RouteRecords.o: RouteRecords.c RouteRecords.h
	gcc -c RouteRecords.c -o RouteRecords.o
clean:
	rm -rf *.o 
	rm myProgram
 
