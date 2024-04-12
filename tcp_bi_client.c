#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#define MAX 1024
#define PORT 9090

void main()
{
    	int sockfd;
    	char buffer[MAX];
    	struct sockaddr_in servaddr;

    	sockfd = socket(AF_INET, SOCK_STREAM, 0);

    	memset(&servaddr, 0, sizeof(servaddr));

    	servaddr.sin_family = AF_INET;
    	servaddr.sin_port = htons(PORT);
    	servaddr.sin_addr.s_addr = INADDR_ANY;

    	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	
	while(1)
	{
		printf("\nClient : ");
		fgets(buffer,MAX,stdin);
		send(sockfd,buffer,sizeof(buffer),0);
		memset(buffer,MAX,0);
		recv(sockfd,buffer,MAX,0);
		printf("\nServer : %s",buffer);
		if(strcmp(buffer,"bye\n")==0)
		{
			break;
		}
	}
	
	close(sockfd);
}
