all: main learn learn-sampling paramGen paramRead

main: main.o rbm.o
	g++ -o main main.o rbm.o

learn: learn.o rbm.o
	g++ -o learn learn.o rbm.o

learn-sampling: learn-sampling.o rbm.o
	g++ -o learn-sampling learn-sampling.o rbm.o

paramGen: paramGen.o rbm.o
	g++ -o paramGen paramGen.o rbm.o

paramRead: paramRead.o rbm.o
	g++ -o paramRead paramRead.o rbm.o

main.o: main.cpp rbm.h
	g++ -c main.cpp

learn.o: learn.cpp rbm.h
	g++ -c learn.cpp

learn-sampling.o: learn-sampling.cpp rbm.h
	g++ -c learn-sampling.cpp

paramGen.o: paramGen.cpp rbm.h
	g++ -c paramGen.cpp

paramRead.o: paramRead.cpp rbm.h
	g++ -c paramRead.cpp

rbm.o: rbm.cpp rbm.h
	g++ -c rbm.cpp

clean:
	rm main.o rbm.o learn.o learn-sampling.o paramGen.o paramRead.o main learn learn-sampling paramGen paramRead

dataclean:
	rm ./data/*