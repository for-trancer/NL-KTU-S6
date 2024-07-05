
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080
#define  MAX 1024

void main()
{
	int sockfd;
	struct sockaddr_in servaddr;
	char buffer[MAX];
	
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(PORT);
	
	connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	
	printf("Client : ");
	fgets(buffer,MAX,stdin);
	send(sockfd,buffer,sizeof(buffer),0);
	
	close(sockfd);
}
