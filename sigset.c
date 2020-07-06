#include "apue.h"
#include <signal.h>

void printSigset(const sigset_t* set){
	for (int i =1;i < 32;++i){
		sigismember(set, i) == 1 ? putchar('1') : putchar('0');
	}
	puts("");
}





int main(void){
	sigset_t signew, sigold;
	sigemptyset(&signew);
	sigaddset(&signew, SIGINT);
	sigprocmask(SIG_BLOCK, &signew, NULL);

	printf("%ld\n",sizeof(sigset_t));
	while (1) {
		sigpending(&sigold);
		printSigset(&sigold);
		sleep(1);
	}
	exit(0);
}
