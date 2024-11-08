#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    struct sockaddr_in client, server;
    int sockfd = 0;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(10002);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    client.sin_family = AF_INET;
    client.sin_port = htons(10003);
    client.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(sockfd, (struct sockaddr *)&client, sizeof(client)) == -1) {
        perror("bind");
        exit(1);
    }

    while (1) {
        char charBuffer[100] = {0};
        char charBuffer2[100] = {0};
        int flag = 0;

        printf("Enter the message: ");
        scanf(" %[^\n]s", charBuffer);
        getchar();  // clear the input buffer
        if (strcmp(charBuffer, "stop") == 0) break;

        int snd = sendto(sockfd, charBuffer, strlen(charBuffer), flag, (struct sockaddr *)(&server), sizeof(server));
        if (snd == -1) {
            printf("Sender Error\n");
            return 1;
        }
        printf("Message sent\n");

        int temp = sizeof(server);
        int rcv = recvfrom(sockfd, charBuffer2, sizeof(charBuffer2), flag, (struct sockaddr *)(&server), &temp);
        if (rcv == -1) {
            printf("Receiver Error\n");
            return 1;
        }
        printf("Message received: %s\n", charBuffer2);
    }

    close(sockfd);
    return 0;
}
