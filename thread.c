#include "apue.h"
#include <pthread.h>

void* th1(void* arg){
	long i = (long)arg;
	sleep(1);
	printf("the %ldth thread pid = %d, thread_id = %lu\n",  i, getpid(), pthread_self());
	return NULL;
}


int main(void) {
	pthread_t tid;
	int ret;
	long i;
	printf("main thread pid = %d, thread id = %lu\n", getpid(), pthread_self());

	for (i = 0;i < 5;++i) {
		ret = pthread_create(&tid, NULL, th1, (void*)i );
		if (ret){
			perror("error :pthread_create()");
			exit(-1);
		}
	}
//	sleep(6);
	pthread_exit((void*)0);
	exit(0);
}
