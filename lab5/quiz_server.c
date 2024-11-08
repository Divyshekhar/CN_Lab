#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h> 

int countVowels(const char *str) {
    int count = 0;
    char ch;

    for (int i = 0; str[i] != '\0'; i++) {
        ch = str[i];
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' ||
            ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U') {
            count++;
        }
    }

    return count;
}

int main() {
    struct sockaddr_in server, client;
    int sockfd = 0;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(10002);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) == -1) {
        perror("bind");
        close(sockfd);
        exit(1);
    }

    while (1) {
        char charBuffer[100] = {0};
        char response[100] = {0};
        int flag = 0;
        socklen_t client_len = sizeof(client);

        int rcv = recvfrom(sockfd, charBuffer, sizeof(charBuffer), flag, (struct sockaddr *)&client, &client_len);
        if (rcv == -1) {
            perror("recvfrom");
            close(sockfd);
            return 1;
        }

        printf("Message received from client %s\n", charBuffer);

        int vowelCount = countVowels(charBuffer);

        snprintf(response, sizeof(response), "Number of vowels: %d", vowelCount);

        int snd = sendto(sockfd, response, strlen(response), flag, (struct sockaddr *)&client, client_len);
        if (snd == -1) {
            perror("sendto");
            close(sockfd);
            return 1;
        }

        printf("Response sent to client");
    }

    close(sockfd);
    return 0;
}
