#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>

#define PORT 7070
#define MAX 1024

int main() {
    int sockfd, newsockfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;
    time_t raw_time;
    char *time_string;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(sockfd, 5);
    len = sizeof(cliaddr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &len);

    // Get current time
    raw_time = time(NULL);
    time_string = ctime(&raw_time);

    // Send time to client
    send(newsockfd, time_string, strlen(time_string), 0);

    close(sockfd);
    close(newsockfd);

    return 0;
}
