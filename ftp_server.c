#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define MAXLINE 1024

int main() 
{
    int sockfd, newsockfd, n;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;
    char buffer[MAXLINE];
    FILE *fp;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));

    listen(sockfd, 5);

    len = sizeof(cliaddr);

    newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &len);

    memset(buffer, 0, MAXLINE);
    n = recv(newsockfd, buffer, MAXLINE, 0);
    
    fp = fopen(buffer, "r");

    printf("Content of the file:\n");
    while ((n = fread(buffer, 1, sizeof(buffer), fp)) > 0) 
    {
        fwrite(buffer, 1, n, stdout);
    }
    printf("\n");

    fseek(fp, 0, SEEK_SET);

    while ((n = fread(buffer, 1, sizeof(buffer), fp)) > 0) 
    {
    	send(newsockfd, buffer, n, 0);
    }

    fclose(fp);
    close(newsockfd);
    close(sockfd);

    return 0;
}
