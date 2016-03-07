Ajedrez: pieza.o main.o
	g++ pieza.o main.o -o Ajedrez -lncurses

main.o: main.cpp pieza.h
	g++ -c main.cpp

pieza.o: pieza.cpp pieza.h
	g++ -c pieza.cpp

