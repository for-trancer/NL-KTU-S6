
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 6060 // Change Port No After Each Execution
#define  MAX 1024


void main()
{
	int sockfd,newsockfd,i;
	struct sockaddr_in servaddr,cliaddr;
	socklen_t len;
	char buffer[MAX],reverse[20],k;
	
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	
	memset(&servaddr,0,sizeof(servaddr));
	
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(PORT);
	
	bind(sockfd,(const struct sockaddr *)&servaddr,sizeof(servaddr));
	listen(sockfd,5);
	
	len = sizeof(cliaddr);
	newsockfd = accept(sockfd,(struct sockaddr *)&cliaddr,&len);
	
	recv(newsockfd,buffer,MAX,0);
	
	int l = strlen(buffer);
	k=l-1;
	for(i=0;i<l;i++)
	{
		reverse[i]=buffer[k];
		k--;
	}
	reverse[i]='\0';
	
	send(newsockfd,reverse,sizeof(reverse),0);

	close(sockfd);
	close(newsockfd);
}
