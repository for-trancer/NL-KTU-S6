#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>

#define PORT 8088
#define MAXLINE 1024

void main()
{
	int sockfd,newsockfd,len,flag=0,i,number;
	struct sockaddr_in servaddr,cliaddr;
	len = sizeof(servaddr);
	char buffer[MAXLINE],ch;
	
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	listen(sockfd,5);
	
	newsockfd = accept(sockfd,(struct sockaddr*)&cliaddr,&len);
	
	recv(newsockfd,&number,sizeof(number),0);
	
	printf("Number Received : %d",number);
	
	for(i=2;i<number;i++)
	{
		if(number%i==0)
		{
			flag=1;
			break;
		}
	}
	
	memset(buffer,MAXLINE,0);
	if(flag==0)
	{
		strcat(buffer,"The Number Is Prime!");
		printf("\n%s",buffer);
		send(newsockfd,buffer,sizeof(buffer),0);
	}
	else
	{
		strcat(buffer,"The Number Is Not Prime!");
		printf("\n%s",buffer);
		send(newsockfd,buffer,sizeof(buffer),0);
	}
	close(sockfd);
	close(newsockfd);
}
