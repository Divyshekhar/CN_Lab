#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

int handle_client(int newsockfd)
{
    char charBuffer[100] = {0};
    char charBuffer2[100] = {0};

    while (1)
    {
        memset(charBuffer, 0, sizeof(charBuffer));
        int recv_len = recv(newsockfd, charBuffer, sizeof(charBuffer) - 1, 0);
        if (recv_len == -1)
        {
            perror("recv");
            close(newsockfd);
            return 1;
        }
        charBuffer[recv_len] = '\0';
        printf("Message received: %s\n", charBuffer);

        if (strcmp(charBuffer, "stop") == 0)
        {
            printf("Stopping communication with client.\n");
            break;
        }

        printf("Enter the message you want to send back: ");
        scanf(" %[^\n]s", charBuffer2);
        getchar();
        if (strcmp(charBuffer2, "stop") == 0)
        {
            printf("Stopping communication with client.\n");
            break;
        }

        int send_len = send(newsockfd, charBuffer2, strlen(charBuffer2), 0);
        if (send_len == -1)
        {
            perror("send");
            close(newsockfd);
            return 1;
        }
        printf("Message sent: %s\n", charBuffer2);
    }

    close(newsockfd);
    return 0;
}

int main()
{
    struct sockaddr_in server, client;
    int sockfd;
    socklen_t client_len;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("socket");
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(10000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        perror("bind");
        close(sockfd);
        exit(1);
    }

    listen(sockfd, 5);
    printf("Server listening on port 10000\n");

    while (1)
    {
        client_len = sizeof(client);
        int newsockfd = accept(sockfd, (struct sockaddr *)&client, &client_len);
        if (newsockfd < 0)
        {
            perror("accept");
            continue;
            handle_client(newsockfd);
        }

        printf("Accepted a new connection\n");

        // if (handle_client(newsockfd) != 0) {
        //     printf("Error occurred while handling client.\n");
        // }

        printf("Finished communication with client, ready for next client.\n");
    }

    close(sockfd);
    return 0;
}
