#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <cstdio>
#include <string.h>


int main(void)
{
	int sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
		printf("socket failed");

	struct sockaddr_in address;
	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(1000);
	address.sin_addr.s_addr=inet_addr("127.0.0.1");
	int len = sizeof(struct sockaddr);

	if(connect(sockfd, (struct sockaddr *)&address, len))
		printf("connected\n");
	while(1)
	{
		char char_send[5] = {0};
		scanf("%s", char_send);
//		fflush(stdin);
		send(sockfd, char_send, 5, 0);
		printf("send finish\n");
	}
	return 0;
}
