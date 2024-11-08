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
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    client.sin_family = AF_INET;
    client.sin_port = htons(10003);
    client.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(bind(sockfd, (struct sockaddr *)&server, sizeof server) == -1){
        perror("bind");
        exit(1);
    }
    int nums[2];
    int flag = 0, temp = sizeof(client);
    int rcv = recvfrom(sockfd, nums, sizeof(nums), flag, (struct sockaddr*)(&client), &temp);
    if(rcv == -1){
        printf("Reciever Error");
        return 1;
    }
    printf("Numbers recieved: %d %d\n", nums[0], nums[1]);
    printf("Addition of the numbers recieved : %d\n", nums[0] + nums[1]);
    printf("Subtraction of the numbers recieved : %d\n", nums[0] - nums[1]);
    printf("Multiplication of the numbers recieved : %d\n", nums[0] * nums[1]);
    printf("Division of the numbers recieved : %d\n", nums[0] / nums[1]);

    return 0;
}