#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#define MAX 1024
#define PORT 8080

void main()
{
	int sockfd, newsockfd,len;
	struct sockaddr_in servaddr, cliaddr;
    	char send_msg[MAX],receive_msg[MAX];

    	sockfd = socket(AF_INET, SOCK_STREAM, 0);

    	servaddr.sin_family = AF_INET;
    	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    	servaddr.sin_port = htons(PORT);

    	bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));

    	listen(sockfd, 5);

    	len = sizeof(cliaddr);

    	newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &len);
	
	while(1)
	{
		recv(newsockfd,receive_msg,MAX,0);
		printf("\nClient : %s\n",receive_msg);
		printf("Server : ");
		fgets(send_msg,MAX,stdin);
		send(newsockfd,send_msg,sizeof(send_msg),0);
		if((strcmp(send_msg,"bye\n")==0)||(strcmp(receive_msg,"bye\n")==0))
		{
			break;
		}
	}
	
	close(sockfd);
	close(newsockfd);
}
