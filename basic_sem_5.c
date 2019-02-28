#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#define HAMBURGER 0
#define CHEESEBURGER 1
#define DOUBLEDOUBLE 2
void force_sleep(int seconds) {
	struct timespec initial_spec, remainder_spec;
	initial_spec.tv_sec = (time_t)seconds;
	initial_spec.tv_nsec = 0;

	int err = -1;
	while(err == -1) {
		err = nanosleep(&initial_spec,&remainder_spec);
		initial_spec = remainder_spec;
		memset(&remainder_spec,0,sizeof(remainder_spec));
	}
}

sem_t sem_1, sem_2;
pthread_t thread_1;
pthread_t thread_2;
pthread_t thread_3;
pthread_t main_thread;
void * bbq_party(void *args) {
	force_sleep (1);
	sem_wait(&sem_1);
	printf("Thread 1 got sem_1\n");
	*(int*)args = 1;
	
	
	force_sleep (2);

	printf ("Thread 1 about to release sem_1\n");
	sem_post(&sem_1);
	printf ("Thread 1 released sem_1\n");


	return (void*)HAMBURGER;
}

void * bbq_party2(void *args) {
	//force_sleep (1);
	sem_wait(&sem_1);
	printf("Thread 2 got sem_1\n");
	*(int*)args = 2;
	
	
	force_sleep (2);

	printf ("Thread 2 about to release sem_1\n");
	sem_post(&sem_1);
	printf ("Thread 2 released sem_1\n");
	
	int r1 = 1000;
	pthread_join (thread_1, (void**)&r1);
	printf ("(Thread 2): r1 = %d\n", r1);
	
	printf ("End Thread 2\n");
	pthread_exit ( (void*) CHEESEBURGER);
	return (void*)CHEESEBURGER;
}

void * bbq_party3(void *args) {
	//force_sleep (1);
	//sem_wait(&sem_1);
	//printf("Thread 2 got sem_1\n");

	printf ("(Thread 3): Trying join with main\n");	
	int main_r = 1000;
	pthread_join (main_thread, (void**)&main_r);
	printf ("(Thread 3): main_r = %d\n", main_r);
	*(int*)args = 3;
	printf ("End Thread 3\n");

	return (void*)DOUBLEDOUBLE;
}

int main() {

	int arg1 = 0;
	int arg2 = 0;
	int arg3 = 0;
	int r2 = 0;
	
	sem_init(&sem_1,0,1);


	pthread_create(&thread_1, NULL, bbq_party, &arg1);
	pthread_create(&thread_2, NULL, bbq_party2, &arg2);
	pthread_create(&thread_3, NULL, bbq_party3, &arg3);
	main_thread = pthread_self();

	force_sleep(1);

	pthread_join (thread_2, (void**)&r2);
       	printf ("(Main Thread): arg1 = %d\n", arg1);	
       	printf ("(Main Thread): arg2 = %d\n", arg2);	
       	printf ("(Main Thread): arg3 = %d\n", arg3);	
       	printf ("(Main Thread): r2 = %d\n", r2);	

	printf ("(Main Thread): Destroying sem_1\n");
	sem_destroy(&sem_1);
	printf ("End Main Thread\n");
	pthread_exit((void*) 5);
	return 0;
}
