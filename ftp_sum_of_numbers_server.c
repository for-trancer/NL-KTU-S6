#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <ctype.h>


#define MAX 1024
#define PORT 9090


void main()
{
	int sockfd,len;
	FILE *file;
	char buffer[MAX],msg[MAX];
	struct sockaddr_in servaddr;
	len = sizeof(servaddr);
	
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	recvfrom(sockfd,buffer,MAX,0,(struct sockaddr*)&servaddr,&len);
	file = fopen(buffer,"r");
	int sum=0,no;
	char ch,temp[10];
	while((ch=fgetc(file))!=EOF)
	{
		if(isdigit(ch))
		{
			no = ch - '0';
			sum += no;
		}
		else
		{ 
			putchar(ch);	
		}
	}
	sprintf(temp, "%d", sum);  // Convert sum to string
    	printf("Sum: %s\n", temp);

    	strncpy(msg, temp, sizeof(msg));  // Copy temp to msg
    	msg[sizeof(msg) - 1] = '\0';
    	
	sendto(sockfd,msg,sizeof(msg),0,(struct sockaddr*)&servaddr,sizeof(servaddr));
	fclose(file);
	close(sockfd);
}
