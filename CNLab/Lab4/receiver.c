#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_DATA_SIZE 1024
#define PORT 12345

void die(const char *s)
{
    perror(s);
    exit(1);
}

int main()
{
    int sock;
    struct sockaddr_in server, client;
    socklen_t server_len = sizeof(server);
    socklen_t client_len = sizeof(client);

    // Create socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        die("socket");
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    if (bind(sock, (struct sockaddr *)&server, server_len) == -1)
    {
        die("bind");
    }

    char buffer[MAX_DATA_SIZE];

    while (1)
    {
        // Receive data
        if (recvfrom(sock, buffer, MAX_DATA_SIZE, 0, (struct sockaddr *)&client, &client_len) == -1)
        {
            die("recvfrom()");
        }
        printf("Received: %s\n", buffer);

        // Send acknowledgment
        if (sendto(sock, "ACK", 3, 0, (struct sockaddr *)&client, client_len) == -1)
        {
            die("sendto()");
        }
    }

    close(sock);
    return 0;
}
