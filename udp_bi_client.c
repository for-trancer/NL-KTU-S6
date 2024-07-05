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
    	char send_msg[MAX],receive_msg[MAX];
    	struct sockaddr_in servaddr;

    	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    	servaddr.sin_family = AF_INET;
    	servaddr.sin_port = htons(PORT);
    	servaddr.sin_addr.s_addr = INADDR_ANY;

    	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    	len = sizeof(servaddr);
	
	while(1)
	{
		printf("\nClient : ");
		fgets(send_msg,MAX,stdin);
		sendto(sockfd,send_msg,sizeof(send_msg),0,(struct sockaddr*)&servaddr,sizeof(servaddr));
		recvfrom(sockfd,receive_msg,MAX,0,(struct sockaddr*)&servaddr,&len);
		printf("\nServer : %s",receive_msg);
		if((strcmp(send_msg,"bye\n")==0)||(strcmp(receive_msg,"bye\n")==0))
		{
			break;
		}
	}
	
	close(sockfd);
}
