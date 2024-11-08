#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

// Function to count consonants in a string
int countCons(const char *str)
{
    int count = 0;
    char ch;

    for (int i = 0; str[i] != '\0'; i++)
    {
        ch = str[i];
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        {
            if (ch != 'a' && ch != 'e' && ch != 'i' && ch != 'o' && ch != 'u' &&
                ch != 'A' && ch != 'E' && ch != 'I' && ch != 'O' && ch != 'U')
            {
                count++;
            }
        }
    }

    return count;
}

// Function to handle communication with the client
int handle_client(int newsockfd, char *charBuffer)
{
    memset(charBuffer, 0, 100);
    int recv_len = recv(newsockfd, charBuffer, 99, 0);
    if (recv_len == -1)
    {
        perror("recv");
        close(newsockfd);
        return 1;
    }
    charBuffer[recv_len] = '\0';
    printf("Message received: %s\n", charBuffer);

    return 0;
}

int main()
{
    struct sockaddr_in server, client;
    int sockfd;
    socklen_t client_len;
    char charBuffer[100] = {0};

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

    client_len = sizeof(client);
    int newsockfd = accept(sockfd, (struct sockaddr *)&client, &client_len);
    if (newsockfd < 0)
    {
        perror("accept");
        close(sockfd);
        exit(1);
    }

    printf("Accepted a new connection\n");

    if (handle_client(newsockfd, charBuffer) != 0) {
        printf("Error occurred while handling client.\n");
        close(newsockfd);
        close(sockfd);
        exit(1);
    }

    int ans = countCons(charBuffer);
    printf("The number of consonants is %d\n", ans-1);

    close(newsockfd); // Close client socket after handling
    close(sockfd); // Close server socket after finishing

    return 0;
}
