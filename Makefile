CXXFLAGS = -std=c++11 -O2

all: main learn paramGen paramRead log-likelihood

main: main.o rbm.o
	g++ -o main main.o rbm.o $(CXXFLAGS)

learn: learn.o rbm.o
	g++ -o learn learn.o rbm.o $(CXXFLAGS)

paramGen: paramGen.o rbm.o
	g++ -o paramGen paramGen.o rbm.o $(CXXFLAGS)

paramRead: paramRead.o rbm.o
	g++ -o paramRead paramRead.o rbm.o $(CXXFLAGS)

log-likelihood: log-likelihood.o rbm.o
	g++ -o log-likelihood log-likelihood.o rbm.o $(CXXFLAGS)

main.o: main.cpp rbm.h
	g++ -c main.cpp $(CXXFLAGS)

learn.o: learn.cpp rbm.h
	g++ -c learn.cpp $(CXXFLAGS)

paramGen.o: paramGen.cpp rbm.h
	g++ -c paramGen.cpp $(CXXFLAGS)

paramRead.o: paramRead.cpp rbm.h
	g++ -c paramRead.cpp $(CXXFLAGS)

log-likelihood.o: log-likelihood.cpp rbm.h
	g++ -c log-likelihood.cpp $(CXXFLAGS)

rbm.o: rbm.cpp rbm.h
	g++ -c rbm.cpp $(CXXFLAGS)

clean:
	rm main.o rbm.o learn.o paramGen.o paramRead.o log-likelihood.o main learn paramGen paramRead log-likelihood

dataclean:
	rm ./data/*.dat

