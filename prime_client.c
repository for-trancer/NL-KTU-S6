#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8088
#define MAXLINE 1024

void main()
{
	int sockfd,len,number;
	struct sockaddr_in servaddr;
	len = sizeof(servaddr);
	char buffer[MAXLINE];
	
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	
	printf("Enter The Number : ");
	scanf("%d",&number);
	
	send(sockfd,&number,sizeof(number),0);
	recv(sockfd,buffer,sizeof(buffer),0);
	printf("%s",buffer);
	close(sockfd);
}
