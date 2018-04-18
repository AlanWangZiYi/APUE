#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <cstdio>
#include <string>

using namespace std;


int main(void)
{
	int server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(1000);
	
	socklen_t server_len = sizeof(struct sockaddr_in);

	bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
	socklen_t templen = sizeof(server_address);

	listen(server_sockfd, 5);
	printf("server waitint connect \n");
	struct sockaddr_in client_address;
	while(1)
	{
		int client_len = sizeof(client_address);
		int client_sockfd = accept(server_sockfd, (struct sockaddr*)&client_address, (socklen_t *)&client_len);
		if(client_sockfd == -1)
		{
			printf("accept error\n");
			continue;
		}

		char char_recv[5];
		recv(client_sockfd, char_recv, 5, 0);
		printf("receive from client is %s \n", char_recv);
	}
	return 0;
}
