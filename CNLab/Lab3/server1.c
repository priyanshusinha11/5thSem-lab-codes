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
    int sockfd;
    char buffer[MAXLINE];
    char *hello = "Hello from server";
    struct sockaddr_in servaddr, cliaddr;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    // this is to give the server a definite port and
    // address. the client will need to know this to
    // be able to connect to the server.
    if (bind(sockfd, (struct sockaddr *)&servaddr,
             sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int len, n;

    len = sizeof(cliaddr);

    // extra comments: we are passing the client address structure
    // because we want to capture the IP address and port of the client.
    // in UDP there are no connections. so, we need to look into the packet
    // received from the client to know its address. we can use that address
    // to send a message back to the client.
    n = recvfrom(sockfd, buffer, MAXLINE,
                 0, (struct sockaddr *)&cliaddr,
                 &len);
    buffer[n] = '\0';
    printf("Client : %s\n", buffer);
    sendto(sockfd, hello, strlen(hello),
           0, (struct sockaddr *)&cliaddr,
           len);
    printf("Hello message sent.\n");

    printf("The client port is %d ", ntohs(cliaddr.sin_port));

    close(sockfd);
    return 0;
}