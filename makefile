all:
	g++ -c -o threads.o threads.cpp -m32
	g++ -o sem_test_1  basic_sem_1.c threads.o -m32
	g++ -o sem_test_2  basic_sem_2.c threads.o -m32
	g++ -o sem_test_3  basic_sem_3.c threads.o -m32
	g++ -o sem_test_4  basic_sem_4.c threads.o -m32
	
clean:
	rm threads.o
	rm sem_test_1
	rm sem_test_2
	rm sem_test_3
	rm sem_test_4

