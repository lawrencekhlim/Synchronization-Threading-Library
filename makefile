all:
	
thread:
	g++ -c -o threads.o threads.cpp -m32


clean:
	rm threads.o

