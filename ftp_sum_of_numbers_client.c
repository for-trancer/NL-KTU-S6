#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>


#define MAX 1024
#define PORT 9090


void main()
{
	int sockfd,len,l;
	char buffer[MAX];
	struct sockaddr_in servaddr;
	len = sizeof(servaddr);
	
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	
	bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	printf("Enter The Filename : "); // number_list.txt
	scanf("%s",buffer);
	l=sizeof(buffer);
	sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&servaddr,sizeof(servaddr));
	memset(buffer,MAX,0);
	recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&servaddr,&len);	
	printf("Sum Of Numbers In The File : %s",buffer);
	close(sockfd);
}
