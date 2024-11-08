#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

int main() {
    struct sockaddr_in server, client;
    int sockfd = 0;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(10000);
    server.sin_addr.s_addr = inet_addr("192.168.177.118");

    client.sin_family = AF_INET;
    client.sin_port = htons(10003);
    client.sin_addr.s_addr = inet_addr("172.19.27.154");


    int k = bind(sockfd, (struct sockaddr *)&server, sizeof(server));
    if (k == -1) {
        printf("Bind error\n");
        return 1;
    }

    int nums[100];
    int flags = 0, temp = sizeof(client);
    int rcv = recvfrom(sockfd, nums, sizeof(nums), flags, (struct sockaddr *)(&client), &temp);

    if (rcv == -1) {
        printf("Error receiving data\n");
        return 1;
    }

    printf("Recieved Integers : ");
    for(int i=0;i<100;i++)
    printf("%d ",nums[i]);
    printf("\n");
    int low=0,high=99;  
  while(low<=high)
    {
            int t=0;
            t=nums[low];
            nums[low]=nums[high];
            nums[high]=t;
            low++;
            high--;
    }
    printf("Reversed Integers : ");
    for(int i=0;i<100;i++)
    printf("%d ",nums[i]);
    printf("\n");
    return 0;
}