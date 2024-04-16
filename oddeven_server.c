
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 6069 // Change Port No After Each Execution
#define  MAX 1024


void main()
{
	int sockfd,newsockfd,no;
	struct sockaddr_in servaddr,cliaddr;
	socklen_t len;
	char *buffer;
	
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	
	memset(&servaddr,0,sizeof(servaddr));
	
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(PORT);
	
	bind(sockfd,(const struct sockaddr *)&servaddr,sizeof(servaddr));
	listen(sockfd,5);
	
	len = sizeof(cliaddr);
	newsockfd = accept(sockfd,(struct sockaddr *)&cliaddr,&len);
	
	recv(newsockfd,&no,sizeof(no),0);
	printf("Number Received From The Client : %d\n",no);
	
	if(no%2==0)
	{
		buffer = "Even";
	}
	else
	{
		buffer = "Odd";
	}
	
	send(newsockfd,buffer,sizeof(buffer),0);

	close(sockfd);
	close(newsockfd);
}
