arboles :	lse.o pilas.o colas.o ab.o abb.o main.o
	@gcc lse.o pilas.o colas.o ab.o abb.o main.o -o arboles

main.o : main.c abb.h
	@gcc -c main.c 

abb.o : abb.c abb.h ab.h
	@gcc -c abb.c

ab.o : ab.c ab.h pilas.h colas.h
	@gcc -c ab.c 

pilas.o : pilas.c pilas.h
	@gcc -c pilas.c 

colas.o : colas.c colas.h
	@gcc -c colas.c 

lse.o : lse.c lse.h
	@gcc -c lse.c 

clean : 
	@rm -f *.o arboles