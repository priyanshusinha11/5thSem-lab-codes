#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

void receive_file(int server_sock, const char *filename)
{
    long file_size;
    recv(server_sock, &file_size, sizeof(file_size), 0);

    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        perror("File creation failed");
        exit(1);
    }

    char buffer[1024];
    int bytes_received;
    long bytes_total = 0;

    while (bytes_total < file_size)
    {
        bytes_received = recv(server_sock, buffer, sizeof(buffer), 0);
        fwrite(buffer, 1, bytes_received, file);
        bytes_total += bytes_received;
    }

    fclose(file);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <server_ip> <server_port>\n", argv[0]);
        exit(1);
    }

    int server_sock;
    struct sockaddr_in server_addr;
    char filename[256];

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0)
    {
        perror("Socket creation failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);

    if (connect(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(1);
    }

    int file_count = 0;
    recv(server_sock, filename, sizeof(filename), 0);
    printf("Files available on the server:\n");
    while (strlen(filename) > 0) {
        printf("%d. %s\n", ++file_count, filename);
        recv(server_sock, filename, sizeof(filename), 0);
    }

    int choice;
    printf("Enter the number of the file you want to download: ");
    scanf("%d", &choice);
    send(server_sock, argv[choice], strlen(argv[choice]), 0);

    receive_file(server_sock, argv[choice]);

    close(server_sock);
    return 0;
}
