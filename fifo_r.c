#include "apue.h"

int main(void){
	int fd;
	fd = open("myfifo", O_RDONLY);
	if (fd < 0){
		perror("open()");
		exit(-1);
	}
	int n;
	char buf[256] = {0};
	while (1){
		n = read(fd, buf, sizeof(buf));
		write(STDOUT_FILENO, buf, n);
		sleep(2);
	}

	close(fd);
	exit(0);
}
