all: theGame udps tcps
theGame: main.o cat.o world.o tcpc.o point.o
	gcc -o theGame main.o cat.o world.o tcpc.o point.o -lSDL2 -lSDL2_image -lSDL2_net
udps: udps.o point.o
	gcc -o udps udps.o point.o -lSDL2_net -lSDL2
tcps: tcps.o point.o
	gcc -o tcps tcps.o point.o -lSDL2_net -lSDL2
tcps.o: tcps.c
	gcc -c tcps.c
main.o: main.c
	gcc -c main.c
world.o: world.c
	gcc -c world.c
cat.o: cat.c
	gcc -c cat.c
tcpc.o: tcpc.c
	gcc -c tcpc.c 
point.o: point.c
	gcc -c point.c
clean:
	rm *.o