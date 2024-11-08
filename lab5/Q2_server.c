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
    struct sockaddr_in server, client;
    int sockfd = 0;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(10002);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) == -1) {
        perror("bind");
        exit(1);
    }

    while (1) {
        char charBuffer[100] = {0};
        char charBuffer2[100] = {0};
        int flag = 0, temp = sizeof(client);

        int rcv = recvfrom(sockfd, charBuffer, sizeof(charBuffer), flag, (struct sockaddr *)(&client), &temp);
        if (rcv == -1) {
            printf("Receiver Error\n");
            return 1;
        }
        printf("Message received: %s\n", charBuffer);

        if (strcmp(charBuffer, "stop") == 0) break;

        printf("Enter the message you want to send back: ");
        scanf(" %[^\n]s", charBuffer2);
        getchar();  // clear the input buffer
        if (strcmp(charBuffer2, "stop") == 0) break;

        int snd = sendto(sockfd, charBuffer2, strlen(charBuffer2), flag, (struct sockaddr *)(&client), sizeof(client));
        if (snd == -1) {
            printf("Sender Error\n");
            return 1;
        }
        printf("Message sent\n");
    }

    close(sockfd);
    return 0;
}
