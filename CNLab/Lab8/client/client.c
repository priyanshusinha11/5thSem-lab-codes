#include <sys/socket.h>
#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int sktfd, count = 0, fileno;
    struct sockaddr_in serveradd, clientadd;
    FILE *file;
    char msg[1024], buff[1024], filelist[1024][1024];
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

    clientadd.sin_family = AF_INET;
    clientadd.sin_port = htons(42069);
    clientadd.sin_addr.s_addr = INADDR_ANY;
    int lenC = sizeof(clientadd);
    int lenS = sizeof(serveradd);

    int ii = connect(sktfd, (struct sockaddr *)&clientadd, lenC);
    if (ii == -1)
    {
        printf("Connect Error\n");
        return 0;
    }
    else
    {
    }
    printf("Enter a message:");

    scanf("%s", msg);
    printf("Sending to server value:%s\n", msg);
    int m = send(sktfd, msg, sizeof(msg), 0);
    printf("\nWaiting to receive from server\n");
    int n = recv(sktfd, buff, sizeof(buff), 0);

    int j = 0;
    for (int i = 0; i < strlen(buff); i++)
    {
        filelist[count][j] = buff[i];
        if (buff[i] == '\n')
        {
            filelist[count][j] = '\0';
            count++;
            j = 0;
        }
        else
        {
            j++;
        }
    }
    printf("The received file list:\n");
    for (int i = 2; i < count; i++)
    {
        printf("%d:%s\n", i - 1, filelist[i]);
    }
    printf("\nEnter the file number to be downloaded:");
    scanf("%d", &fileno);
    printf("Sending to server value:%s\n", filelist[fileno + 1]);
    m = send(sktfd, filelist[fileno + 1], sizeof(filelist[fileno + 1]), 0);
    file = fopen(filelist[fileno + 1], "w");
    if (file == NULL)
    {
        printf("File not found\n");
        return 0;
    }
    while (1)
    {
        n = recv(sktfd, buff, strlen(buff) - 1, 0);
        if (n == -1)
        {
            printf("recv failed\n");
            return 1;
        }
        buff[n] = '\0';
        if (strcmp(buff, "end") == 0)
        {
            break;
        }
        fprintf(file, "%s", buff);
        printf("Received from server:%s\n", buff);
    }
    printf("\nFile downloaded successfully\n");
    fclose(file);
    printf("\nClosing socket\n");
    close(sktfd);
    return 0;
}