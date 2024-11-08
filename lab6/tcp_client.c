#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <arpa/inet.h>

int send_receive_messages(int sockfd, struct sockaddr_in)
{
    while (1)
    {
        char charBuffer[100] = {0};
        char charBuffer2[100] = {0};
        int flag = 0;

        printf("Enter the message: ");
        scanf(" %[^\n]s", charBuffer);
        getchar(); 

        if (strcmp(charBuffer, "stop") == 0)
            break;

        send(sockfd, charBuffer, strlen(charBuffer), 0);
        printf("Message sent to the server: %s\n", charBuffer);

        if (send == -1)
        {
            printf("Sender Error\n");
            return 1; 
        }
        printf("Message sent\n");

        memset(charBuffer2, 0, sizeof(charBuffer2));
        recv(sockfd, charBuffer2, sizeof(charBuffer2) - 1, 0);
        printf("Received message from server: %s\n", charBuffer2);
        if (recv == -1)
        {
            printf("Receiver Error\n");
            return 1; 
        }
        printf("Message received: %s\n", charBuffer2);
    }

    return 0; 
}

int main()
{
    int sockfd;
    struct sockaddr_in server;
    char buffer[1024];
    char buffer1[100];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("socket");
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(10000);                  
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("connect");
        close(sockfd);
        exit(1);
    }
    send_receive_messages(sockfd, server);
    close(sockfd);

    return 0;
}
