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
    int sockfd, n;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    printf("Enter filename: ");
    fgets(buffer, MAXLINE, stdin);
    
    buffer[strcspn(buffer, "\n")] = 0; // Remove trailing newline
    
    send(sockfd, buffer, strlen(buffer), 0);

    printf("Content of the file:\n");
    while ((n = recv(sockfd, buffer, MAXLINE, 0)) > 0) 
    {
        fwrite(buffer, 1, n, stdout);
    }
    
    close(sockfd);

    return 0;
}
