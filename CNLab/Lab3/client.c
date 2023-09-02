#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <IP> <port>\n", argv[0]);
        return 1;
    }

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in serverAddr;

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
    serverAddr.sin_port = htons(atoi(argv[2]));

    char msg[100];

    while (1)
    {
        printf("Enter message: ");
        fgets(msg, 100, stdin);
        msg[strlen(msg) - 1] = '\0';
        sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

        if (strcmp(msg, "exit") == 0)
        {
            printf("Exiting...\n");
            break;
        }
    }

    return 0;
}