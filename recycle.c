#include "apue.h"
#include <signal.h>
#include <sys/wait.h>

#define COUNT 15

void catch_child(int number) {
	pid_t wpid;
	int status;
	while ((wpid = waitpid(-1, &status, 0)) != -1) {
		printf("wpid = %d\n", wpid);
		if (WIFEXITED(status)) {
			printf("catch_child return value = %d, pid = %d\n", WEXITSTATUS(status), wpid);	
		}
	}
}



int main(void){
	pid_t pid;
	int i;	
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGCHLD);
	sigprocmask(SIG_BLOCK, &set, NULL);
	for (i = 0;i < COUNT;++i){
		pid = fork();
		if (pid < 0){
			perror("fork()");
			exit(-1);
		}
		if (pid == 0){
			break;
		}
	}

	if (i == COUNT){
		struct sigaction action;
		action.sa_handler = catch_child;
		sigemptyset(&action.sa_mask);
		action.sa_flags = 0;

		sigaction(SIGCHLD, &action, NULL);
		sigprocmask(SIG_UNBLOCK, &set, NULL);
		while (1);
		printf("parent end..............................\n");
	}else {
		printf("i am child %d, pid = %d\n", i, getpid());
		return i;
	}



	exit(0);
}
