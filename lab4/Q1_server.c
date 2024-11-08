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
    struct sockaddr_in server, client;
    int sockfd = 0;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    // printf("%d \n", sockfd);
    server.sin_family = AF_INET;
    server.sin_port = htons(10002);
    server.sin_addr.s_addr = inet_addr("192.168.4.118");

    client.sin_family = AF_INET;
    client.sin_port = htons(10003);
    client.sin_addr.s_addr = inet_addr("10.0.2.15");

    if(bind(sockfd, (struct sockaddr *)&server, sizeof server) == -1){
        perror("bind");
        exit(1);
    }
    char charBuffer[100];
    char charBuffer2[100];
    int flag = 0, temp = sizeof(client);
    int rcv = recvfrom(sockfd, charBuffer, sizeof (charBuffer), flag, (struct sockaddr*)(&client), &temp);
    if(rcv == -1){
        printf("Reciever Error");
        return 1;
    }
    printf("Message recieved: %s\n", charBuffer);

    printf("Enter the message you want to send back: ");
    scanf("%[^\n]s", charBuffer2);
    int snd = sendto(sockfd, charBuffer2, strlen(charBuffer2), flag, (struct sockaddr*)(&client), sizeof(client));
    if(snd == -1){
        printf("Reciever Error");
        return 1;
    }
    printf("Message sent\n");

    return 0;
}