#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <port>\n", argv[0]);
        return 1;
    }

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientLen = sizeof(clientAddr);

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
    serverAddr.sin_port = htons(atoi(argv[2]));

    if (bind(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        perror("Binding failed");
        return 1;
    }

    char msg[100];

    while (1)
    {
        memset(msg, 0, 100);
        recvfrom(sock, msg, 100, 0, (struct sockaddr *)&clientAddr, &clientLen);
        printf("Received message: %s\n", msg);
        if (strcmp(msg, "exit") == 0)
        {
            printf("Exiting...\n");
            break;
        }
    }
    return 0;
}