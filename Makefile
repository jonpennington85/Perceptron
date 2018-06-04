CC=g++
FLAGS =-Wall -Wpedantic -c

all: perceptron

perceptron: driver.o perceptron.o preparation.o
	$(CC) driver.o perceptron.o preparation.o -o Perceptron

driver.o:
	$(CC) $(FLAGS) driver.cpp

perceptron.o:
	$(CC) $(FLAGS) perceptron.cpp

preparation.o:
	$(CC) $(FLAGS) preparation.cpp

clean:
	rm *o Perceptron
