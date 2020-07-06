#include "apue.h"
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <sys/socket.h>

#include <vector>

#define SERV_PORT 6666

void sys_error(const char* msg) {
	perror(msg);
	exit(-1);
}


int main(void){
	std::vector<int> v;
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		sys_error("socket()");

	struct sockaddr_in serv_addr;
	socklen_t len = sizeof(serv_addr);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr.s_addr); 

	int ret = connect(sock, (struct sockaddr*)&serv_addr, len);
	if (ret < 0)
		sys_error("connect");

	char buf[BUFSIZ];
	while (1) {
		int n = read(STDIN_FILENO, buf, BUFSIZ);
		if (len < 0)
			sys_error("read()");

		write(sock, buf, n);
		n = read(sock, buf,BUFSIZ);
		write(STDOUT_FILENO, buf, n);
	}

	close(sock);
}









