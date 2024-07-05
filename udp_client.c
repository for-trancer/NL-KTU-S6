#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>

#define MAXLINE 1024
#define PORT 8080


void main()
{
	int sockfd,len;
	struct sockaddr_in servaddr;
	char buffer[MAXLINE];
	
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	len=sizeof(servaddr);
	
	connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	
	printf("Client : ");
	fgets(buffer,MAXLINE,stdin);
	
	sendto(sockfd,buffer,MAXLINE,0,(struct sockaddr *)&servaddr,len);
	
	close(sockfd);
}
