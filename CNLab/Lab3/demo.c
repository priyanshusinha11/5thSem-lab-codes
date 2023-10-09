#include <fcntl.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
    int sktfd;
    struct sockaddr_in serveradd, clientadd;
    char buff[1024], msg[1024];
    for (int i = 0; i < 1024; i++)
    {
        msg[i] = '\0';
        buff[i] = '\0';
    }
    sktfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sktfd == -1)
    {
        printf("Socket Creation Error");
    }
    // printf("\nSocket ID:%d\n",sktfd);
    clientadd.sin_family = AF_INET;
    clientadd.sin_port = htons(9990);
    clientadd.sin_addr.s_addr = inet_addr("172.27.5.204");
    int lenC = sizeof(clientadd);
    int lenS = sizeof(serveradd);
    // printf("Size of the clientadd:%d\n",lenC);
    // printf("Port:%d\n",clientadd.sin_port);
    int ii = connect(sktfd, (struct sockaddr *)&clientadd, lenC);
    if (ii == -1)
    {
        printf("Connect Error\n");
        return 0;
    }
    else
    {
        printf("\nConnect Success\n");
        // printf("Connect value:%d\n\n",ii);
    }
    int n = recv(sktfd, buff, sizeof(buff), 0);
    printf("Received from server:%s\n", buff);
    strcpy(msg, "Hello from Client");
    int m = send(sktfd, msg, sizeof(msg), 0);
    while (1)
    {
        int n = recv(sktfd, buff, sizeof(buff), 0);
        printf("Received from server:%s\n", buff);
        if (strcmp(buff, "exit") == 0)
        {
            printf("Closing socket\n");
            close(sktfd);
            return 0;
        }
        printf("Enter message to send to server:");
        fgets(msg, 1024, stdin);
        msg[strcspn(msg, "\n")] = '\0';
        int m = send(sktfd, msg, sizeof(msg), 0);
        if (strcmp(msg, "1680") == 0 || strcmp(msg, "1681") == 0 || strcmp(msg, "1682") == 0)
        {
            printf("\n");
            int r = recv(sktfd, buff, sizeof(buff), 0);
            printf("Name:%s\n", buff);
            r = recv(sktfd, buff, sizeof(buff), 0);
            printf("Roll No:%s\n", buff);
            r = recv(sktfd, buff, sizeof(buff), 0);
            printf("Marks:%s\n", buff);
            printf("\n");
        }
        if (strcmp(msg, "exit") == 0)
        {
            printf("Closing socket\n");
            close(sktfd);
            return 0;
        }
    }
}