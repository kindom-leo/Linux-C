#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void sig_handler(int number) {
	printf("number = %d\n", number);
}


int main(void){
	struct sigaction action;
	sigemptyset(&action.sa_mask);

	action.sa_handler = sig_handler;
	action.sa_flags = 0;
	
	int  n = sigaction(SIGINT, &action, NULL);
	if (n < 0){
		perror("error sigaction()");
		exit(-1);
	}

	while (1){
		printf("**************\n");
		sleep(1);
	}
	exit(0);
}
