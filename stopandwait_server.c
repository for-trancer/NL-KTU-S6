#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>

#define PORT 8084
#define MAXLINE 1024

void main()
{
	int sockfd,newsockfd,len,n,ack=-1,i;
	struct sockaddr_in servaddr,cliaddr;
	len = sizeof(servaddr);
	char buffer[MAXLINE];
	
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	listen(sockfd,5);
	printf("Waiting For Client Connection!\n");
	newsockfd = accept(sockfd,(struct sockaddr*)&cliaddr,&len);
	printf("Client Connected!\n");
	recv(newsockfd,&n,sizeof(n),0);
	printf("Total Number Of Packets To Receive : %d\n",n);
	printf("Getting Ready To Receive Packets!\n");
	recv(newsockfd,&i,sizeof(n),0);
	do
	{
		printf("Frame [%d] Received!\n",i);
		printf("Press 1 for +ve ACK or -1 for -ve ACK : ");
		scanf("%d",&ack);
		send(newsockfd,&ack,sizeof(n),0);
		if(ack==-1)
		{
			printf("Sending An Resend Request!\n");
		}
		else
		{
			printf("Frame Sucessfully Received!\n");
		}
		recv(newsockfd,&i,sizeof(n),0);
	}
	while(i!=99);
	printf("All frames are received sucessfully");
	close(sockfd);
	close(newsockfd);
}
