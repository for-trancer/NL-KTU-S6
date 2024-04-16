
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 6060 // Change Port Number After Each Execution
#define  MAX 1024

void main()
{
	int sockfd;
	struct sockaddr_in servaddr;
	char buffer[MAX];
	
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	
	memset(&servaddr,0,sizeof(servaddr));
	
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(PORT);
	
	connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	
	printf("Enter The String To Be Reversed : ");
	fgets(buffer,MAX,stdin);
	buffer[strcspn(buffer,"\n")]='\0';
	send(sockfd,buffer,sizeof(buffer),0);
	recv(sockfd,buffer,MAX,0);
	printf("\n Reversed String : %s\n",buffer);
	
	close(sockfd);
}
