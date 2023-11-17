#include <sys/socket.h>
#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>

int main()
{
    int sktfd;
    struct sockaddr_in serveradd, clientadd;
    FILE *fp;
    DIR *d;
    struct dirent *dir;
    char buff[1024], msg[1024], ch;
    for (int i = 0; i < 1024; i++)
    {
        msg[i] = '\0';
        buff[i] = '\0';
    }
    sktfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sktfd == -1)
    {
        printf("\nSocket Creation Error");
        return 0;
    }
    

    serveradd.sin_family = AF_INET;
    serveradd.sin_port = htons(42069);
    serveradd.sin_addr.s_addr = INADDR_ANY;
    
    int lenS = sizeof(serveradd);
    int lenC = sizeof(clientadd);
    
    int b = bind(sktfd, (struct sockaddr *)&serveradd, lenS);
    if (b == -1)
    {
        printf("Bind Error\n");
        return 0;
    }
    else
    {
        
    }
    printf("Waiting to receive from client\n");
    listen(sktfd, 5);
    int fd1 = accept(sktfd, (struct sockaddr *)&clientadd, &lenC);
    if (fd1 == -1)
    {
        printf("Accept Error\n");
        return 0;
    }
    else
    {
       
    }
    int n = recv(fd1, buff, sizeof(buff), 0);
    printf("Message from client:%s\n", buff);
    if (strcmp(buff, "file") == 0)
    {
        d = opendir(".");
        if (d)
        {
            while ((dir = readdir(d)) != NULL)
            {
                
                strcat(msg, dir->d_name);
                strcat(msg, "\n");
            }

            closedir(d);
        }
    }
    int m = send(fd1, msg, sizeof(msg), 0);
    int mn = recv(fd1, buff, sizeof(buff), 0);
    printf("File name received:%s\n", buff);
    fp = fopen(buff, "r");
    if (fp == NULL)
    {
        printf("File not found\n");
        return 0;
    }
    else
    {
        printf("File found\n");
    }
    int i = 0;
    while (fgets(msg, 1024, fp) != NULL)
    {
        int nm = send(fd1, msg, strlen(msg), 0);
        printf("Sending line %s\n", msg);
    }
    
    strcpy(msg, "end");
    int nm = send(fd1, msg, sizeof(msg), 0);
    close(sktfd);
    fclose(fp);
    printf("\nClosing socket\n");
    return 0;
}

