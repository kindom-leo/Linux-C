#include "apue.h"
#include <string.h>
#include <pthread.h>

typedef struct person {
	int		age;
	char	name[256];
}person;


static void* thread_func(void* arg){
	person* p = malloc(sizeof(person));
	if (p) {
		p->age = 33;
		strcpy(p->name, "leopardln");
	}
	return (void*)p;
}




int main(void){
	pthread_t tid;
	printf("main begin!\n");
	int err = pthread_create(&tid, NULL, thread_func, NULL);
	if (err){
		fprintf(stderr, "err: %s \n", strerror(err));
		exit(-1);
	}


	person* p;
	pthread_join(tid, (void**)&p);
	printf(" recv value age = %d, name = %s \n", p->age, p->name);
	printf("main end!\n");
	exit(0);
}
