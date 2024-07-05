#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080
#define  MAX 1024

void main()
{
	int sockfd,newsockfd,len;
	struct sockaddr_in servaddr,cliaddr;
	char buffer[MAX];
	
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(PORT);
	
	bind(sockfd,(const struct sockaddr *)&servaddr,sizeof(servaddr));
	listen(sockfd,5);
	len=sizeof(cliaddr);
	newsockfd = accept(sockfd,(struct sockaddr *)&cliaddr,&len);
	
	recv(newsockfd,buffer,MAX,0);
	
	printf("Client : %s",buffer);
	
	close(sockfd);
	close(newsockfd);
}
