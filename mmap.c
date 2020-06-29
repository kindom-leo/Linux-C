#include "apue.h"
#include <string.h>
#include <sys/mman.h>


int main(void) {
	int fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (fd < 0){
		perror("open()");
		exit(-1);
	}
	
	int n = ftruncate(fd, 100);
	if (n < 0){
		perror("ftruncate()");
		exit(-1);
	}
	void* buf = mmap(NULL, 100, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
	if (buf == MAP_FAILED){
		perror("mmap()");
		exit(-1);
	}
	if(buf)	
		strcpy((char*)buf, "hello");


	if(munmap(buf, 100) < 0){
		perror("ummap()");
		exit(-1);
	}
	exit(0);
}
