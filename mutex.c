#include "apue.h"
#include <pthread.h>

pthread_mutex_t mutex;

void* sayHello(void* arg){
	for (int i = 0;i < 20;++i) {
		pthread_mutex_lock(&mutex);	
		printf("hello ");
		sleep(rand()%2);
		printf("world!\n");
		pthread_mutex_unlock(&mutex);
		sleep(rand()%2);
	}
	return NULL;
}

int main(void) {
	pthread_t tid;
	int ret = pthread_mutex_init(&mutex, NULL);
	if (ret){
		fprintf(stderr, "pthread_mutex_init() error: %s\n",strerror(ret));
		exit(-1);
	}
	ret = pthread_create(&tid, NULL, sayHello, NULL);
	if (ret){
		fprintf(stderr, "pthread_create() error: %s\n",strerror(ret));
		exit(-1);
	}
	
	for (int i = 0;i < 20;++i) {
		pthread_mutex_lock(&mutex);	
		printf("HELLO ");
		sleep(rand()%2);
		printf("WORLD!\n");
		pthread_mutex_unlock(&mutex);
		sleep(rand()%2);
	}

	ret = pthread_join(tid, NULL);
	if (ret){
		fprintf(stderr, "pthread_join() error: %s\n",strerror(ret));
		exit(-1);
	}
	ret = pthread_mutex_destroy(&mutex);
	exit(0);
}

