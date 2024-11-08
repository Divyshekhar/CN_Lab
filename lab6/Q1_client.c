#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>



int send_receive_messages(int sockfd, int n)
{
     char charBuffer[100] = {0};
        char charBuffer2[100] = {0};
        int flag = 0;

        printf("Enter the message: ");
        scanf(" %[^\n]s", charBuffer);
        getchar(); 
        send(sockfd, charBuffer, strlen(charBuffer), 0);
        printf("Message sent to the server: %s\n", charBuffer);

        if (send == -1)
        {
            printf("Sender Error\n");
            return 1; 
        }
        printf("Message sent\n");
        return 0;
}

int main()
{
    int sockfd;
    struct sockaddr_in server;
    int n;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("socket");
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(10000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter the number of characters you want to send: ");
    scanf("%d", &n);

    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("connect");
        close(sockfd);
        exit(1);
    }

    send_receive_messages(sockfd, n);
    close(sockfd);

    return 0;
}
