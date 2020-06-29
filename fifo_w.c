#include "apue.h"
#include <string.h>

int main(void){
	int fd;
	fd = open("myfifo", O_WRONLY);
	if (fd < 0){
		perror("open()");
		exit(-1);
	}
	int i = 0;
	char buf[256] = {0};
	while (1){
		sprintf(buf, "i = %d\n", ++i);	
		write(fd, buf, strlen(buf));
		sleep(1);
	}

	close(fd);
	exit(0);
}
