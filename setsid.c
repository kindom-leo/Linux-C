#include "apue.h"


int main(void){
	pid_t pid =fork();
	pid_t spid;
	if (pid < 0){
		perror("fork()");
		exit(-1);
	}

	if (pid == 0){
		printf("pid = %d\n", getpid());
		printf("pgid = %d\n", getpgid(0));
		printf("sid = %d\n", getsid(0));
		sleep(5);
		spid = setsid();
		printf("pid = %d\n", getpid());
		printf("pgid = %d\n", getpgid(0));
		printf("sid = %d\n", getsid(0));
		sleep(20);
	}

	
	exit(0);
}
