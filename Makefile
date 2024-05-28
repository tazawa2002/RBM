all: main

main: main.o rbm.o
	g++ -o main main.o rbm.o

main.o: main.cpp rbm.h
	g++ -c main.cpp

rbm.o: rbm.cpp rbm.h
	g++ -c rbm.cpp

clean:
	rm main.o bm.o learn.o