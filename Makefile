all: main learn

main: main.o rbm.o
	g++ -o main main.o rbm.o

learn: learn.o rbm.o
	g++ -o learn learn.o rbm.o

learn-sampling: learn-sampling.o rbm.o
	g++ -o learn-sampling learn-sampling.o rbm.o

main.o: main.cpp rbm.h
	g++ -c main.cpp

learn.o: learn.cpp rbm.h
	g++ -c learn.cpp

learn-sampling.o: learn-sampling.cpp rbm.h
	g++ -c learn-sampling.cpp

rbm.o: rbm.cpp rbm.h
	g++ -c rbm.cpp

clean:
	rm main.o rbm.o learn.o

dataclean:
	rm ./data/*