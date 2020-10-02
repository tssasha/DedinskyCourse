all: test run

build:
	g++ -Wall -o solution solution.cpp library.cpp

run: build
	./solution

test: build
	./solution debug