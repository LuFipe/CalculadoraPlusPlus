calculadora: calculadora.o funcCalculadora.o
	g++ calculadora.o funcCalculadora.o -o calculadora

calculadora.o: calculadora.cpp ./CLASSES/classeCalculadora.h
	g++ -c calculadora.cpp -o calculadora.o

funcCalculadora.o: ./FUNCTIONS/funcCalculadora.cpp ./CLASSES/classeCalculadora.h
	g++ -c ./FUNCTIONS/funcCalculadora.cpp -o funcCalculadora.o

make exec:
	./calculadora

calc: calculadora
	./calculadora

limpar:
	rm calculadora.o funcCalculadora.o

refazer: limpar calc