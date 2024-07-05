#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#define MAX 1024
#define PORT 8080

void main()
{
	int sockfd,len;
	struct sockaddr_in servaddr,cliaddr;
    	char send_msg[MAX],receive_msg[MAX];

    	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    	servaddr.sin_family = AF_INET;
    	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    	servaddr.sin_port = htons(PORT);

    	bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));
	len = sizeof(cliaddr);
	
	while(1)
	{
		recvfrom(sockfd,receive_msg,MAX,0,(struct sockaddr*)&cliaddr,&len);
		printf("\nClient : %s\n",receive_msg);
		printf("Server : ");
		fgets(send_msg,MAX,stdin);
		sendto(sockfd,send_msg,sizeof(send_msg),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
		if((strcmp(send_msg,"bye\n")==0)||(strcmp(receive_msg,"bye\n")==0))
		{
			break;
		}
	}
	
	close(sockfd);
}
