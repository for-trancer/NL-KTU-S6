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
	int sockfd, newsockfd;
	struct sockaddr_in servaddr, cliaddr;
    	socklen_t len;
    	char buffer[MAX];

    	sockfd = socket(AF_INET, SOCK_STREAM, 0);

    	memset(&servaddr, 0, sizeof(servaddr));

    	servaddr.sin_family = AF_INET;
    	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    	servaddr.sin_port = htons(PORT);

    	bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));

    	listen(sockfd, 5);

    	len = sizeof(cliaddr);

    	newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &len);
	
	while(1)
	{
		memset(buffer,0,MAX);
		recv(newsockfd,buffer,MAX,0);
		printf("\nClient : %s\n",buffer);
		printf("Server : ");
		fgets(buffer,MAX,stdin);
		send(newsockfd,buffer,strlen(buffer),0);
		if(strcmp(buffer,"bye\n")==0)
		{
			break;
		}
	}
	
	close(sockfd);
	close(newsockfd);
}
