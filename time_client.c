#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 7070
#define MAX 1024

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[MAX];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    
    recv(sockfd, buffer, MAX, 0);

    printf("Server Time: %s\n", buffer);

    close(sockfd);

    return 0;
}
