#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8084
#define MAXLINE 1024

void main()
{
	int sockfd,len,n,ack;
	struct sockaddr_in servaddr;
	len = sizeof(servaddr);
	char buffer[MAXLINE],*test="hey";
	
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	printf("Connected To Server!\n");
	printf("Enter The Total Number Of Frames : ");
	scanf("%d",&n);
	send(sockfd,&n,sizeof(n),0);
	for(int i=1;i<=n;i++)
	{
		ack=-1;
		do
		{
			printf("\nSending Frame [%d]\n",i);
			send(sockfd,&i,sizeof(n),0);
			printf("Waiting For Response!\n");
			recv(sockfd,&ack,sizeof(n),0);
			
			if(ack==-1)
			{
				printf("Negative Acknowledgement Received.Resending!\n");
			}
		}
		while(ack==-1);
	}
	ack=99;
	send(sockfd,&ack,sizeof(n),0);
	printf("All Frames Are Delivered!");
	close(sockfd);
}
