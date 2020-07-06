#include "apue.h"
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <sys/socket.h>


#define SERV_PORT 6666

void sys_error(const char* msg) {
	perror(msg);
	exit(-1);
}


int main(void){
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		sys_error("socket()");

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
//	serv_addr.sin_addr = inet_pton("127.0.0.1");
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY) ;

	int ret = bind(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if (ret < 0)
		sys_error("bind()");

	ret = listen(sock, SOMAXCONN);
	if (ret < 0)
		sys_error("listen()");

	struct sockaddr_in client_addr;
	socklen_t len = sizeof(client_addr);
	int sock_client = accept(sock, (struct sockaddr*)&client_addr, &len);
	if (sock_client < 0)
		sys_error("accept()");

	char buf[BUFSIZ];
	while (1) {
		len = read(sock_client, buf, BUFSIZ);
		if (len < 0)
			sys_error("read()");
		write(STDOUT_FILENO, buf, len);
		for (int i = 0;i < len; ++i){
			buf[i] = toupper(buf[i]);
		}
		write(sock_client, buf, len);
	}

	close(sock);
	close(sock_client);


}
