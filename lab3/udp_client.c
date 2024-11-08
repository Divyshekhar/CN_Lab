#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
int main()
{
    struct sockaddr_in client, server;
    int sockfd = 0;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    // printf("%d \n", sockfd);
    server.sin_family = AF_INET;
    server.sin_port = htons(10000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    client.sin_family = AF_INET;
    client.sin_port = htons(10001);
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(bind(sockfd, (struct sockaddr *)&client, sizeof client) == -1){
        perror("bind");
        exit(1);
    }
    char charBuffer[100];
    printf("enter the message\n");
    int flag = 0;

    scanf("%[^\n]s", charBuffer);
    int snd = sendto(sockfd, charBuffer, strlen(charBuffer), flag, (struct sockaddr*)(&server), sizeof(server));
    if(snd == -1){
        printf("Reciever Error");
        return 1;
    }
    printf("Message sent\n");


    return 0;
}
