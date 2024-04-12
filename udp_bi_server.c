#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>

#define MAXLINE 1024
#define PORT 8080


void main()
{
	int sockfd;
	struct sockaddr_in servaddr;
	socklen_t len;
	char buffer[MAXLINE];
	
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	len = sizeof(servaddr);
	
	while(1)
	{
		recvfrom(sockfd,buffer,MAXLINE,0,(struct sockaddr *)&servaddr,&len);
		printf("\nClient : %s\n",buffer);
		memset(&buffer,0,MAXLINE);
		printf("Server : ");
		fgets(buffer,MAXLINE,stdin);
		sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&servaddr,len);
		if(strcmp(buffer,"bye\n")==0)
		{
			break;
		}
	}
	
	close(sockfd);
}

