#include "apue.h"
#include <pthread.h>

typedef struct msg {
	int num;
	struct msg* pnext;
} msg;

msg* head = NULL;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void sys_error(int errno, const char* msg) {
	fprintf(stderr, "%s  error : %s\n", msg, strerror(errno)); 
}

void* producer(void* arg){
	for (int i = 0;i < 20;++i){
		int ret = pthread_mutex_lock(&mutex);
		if (ret) {
			sys_error(ret, "producer pthread_mutex_lock");
		}

		msg* new_product = malloc(sizeof(msg));
		new_product->pnext = head;
		new_product->num = rand() % 1000 + 1;
		head = new_product;
		printf("producer generate ++++++,pro_number :%d\n", new_product->num);

		ret = pthread_mutex_unlock(&mutex);
		if (ret) {
			sys_error(ret, "producer pthread_mutex_unlock");
		}
		ret = pthread_cond_signal(&cond);
		if (ret) {
			sys_error(ret, "producer pthread_cond_signal");
		}
		sleep(rand() % 3);
	}
	return NULL;
}

void* consumer(void* arg) {
	for(int i = 0;i < 20;++i){
		int ret = pthread_mutex_lock(&mutex);
		if (ret) {
			sys_error(ret, "consumer pthread_mutex_lock");
		}

		while (head == NULL){
			pthread_cond_wait(&cond, &mutex);
		}
		msg* recv_pro = head;	
		head = head->pnext;
		printf("receive a product ------, pro_number = %d\n",recv_pro->num);
		free(recv_pro);
		ret = pthread_mutex_unlock(&mutex);
		if (ret) {
			sys_error(ret, "consumer pthread_mutex_unlock");
		}
		sleep(rand() % 3);
	}
	return NULL;
}


int main(void) {
	srand(time(NULL));
	pthread_t tid_pro, tid_con;
	int ret = pthread_create(&tid_pro, NULL, producer, NULL);
	if (ret) {
		sys_error(ret, "pthread create(&tid_pro)");
	}
	ret = pthread_create(&tid_con, NULL, consumer, NULL);
	if (ret) {
		sys_error(ret, "pthread create(&tid_con)");
	}



	ret = pthread_join(tid_con, NULL);
	if (ret) {
		sys_error(ret, "pthread_join(&tid_con)");
	}

	ret = pthread_join(tid_pro, NULL);
	if (ret) {
		sys_error(ret, "pthread_join(&tid_pro)");
	}
	exit(0);
}
