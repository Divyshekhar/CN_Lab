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
    server.sin_family = AF_INET;
    server.sin_port = htons(10002);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    client.sin_family = AF_INET;
    client.sin_port = htons(10003);
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(bind(sockfd, (struct sockaddr *)&client, sizeof client) == -1){
        perror("bind");
        exit(1);
    }
    int nums[2];
    printf("enter the two numbers\n");
    int flag = 0;

    scanf("%d %d", &nums[0], &nums[1]);
    int snd = sendto(sockfd, nums, sizeof(nums), flag, (struct sockaddr*)(&server), sizeof(server));
    if(snd == -1){
        printf("Reciever Error");
        return 1;
    }
    printf("Message sent\n");

    return 0;
}
