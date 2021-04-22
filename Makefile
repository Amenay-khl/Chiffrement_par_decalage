CC=clang -g

all: hello_world cesarSimple decrypte-v1 projetX planB crypteSeq

%.o : %.c
	$(CC) -c $< -Wall -Werror -g

	
hello_world.o: hello_world.c client.h
cesarSimple.o: cesarSimple.c client.h	
decrypte-v1.o: decrypte-v1.c client.h
projetX.o: projetX.c client.h
planB.o: planB.c client.h
crypteSeq.o: crypteSeq.c client.h 
client.o: client.c client.h

hello_world: hello_world.o client.o
	clang -o hello_world hello_world.o client.o
	
cesarSimple: cesarSimple.o client.o
	clang -o cesarSimple cesarSimple.o client.o	

decrypte-v1: decrypte-v1.o client.o
	clang -o decrypte-v1 decrypte-v1.o client.o
	
projetX: projetX.o client.o
	clang -o projetX projetX.o client.o

planB: planB.o client.o
	clang -o planB planB.o client.o

crypteSeq: crypteSeq.o client.o 
	clang -o crypteSeq crypteSeq.o client.o

	



clean:
	rm -f *.o hello_world cesarSimple decrypte-v1 projetX planB crypteSeq
