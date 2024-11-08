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
    server.sin_port = htons(10000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(bind(sockfd, (struct sockaddr *)&server, sizeof server) == -1){
        perror("bind");
        exit(1);
    }
    char charBuffer[100];
    int flag = 0, temp = sizeof(client);
    int rcv = recvfrom(sockfd, charBuffer, sizeof (charBuffer), flag, (struct sockaddr*)(&client), &temp);
    if(rcv == -1){
        printf("Reciever Error");
        return 1;
    }
    printf("Message recieved: %s\n", charBuffer);


    // printf("%d\n", bind(sockfd, (struct sockaddr *)&server, sizeof server));
    return 0;
}
