#include <stdio.h>
struct pkt
{
        char ch1;
        char ch2[2];
        char ch3;
};
int main()
{
        int a;
        struct pkt p;
        printf("enter the number");
        scanf("%d", &a);
        p.ch1 = (a & 0XFF);
        p.ch2[0] = (a >> 8) & 0XFF;
        p.ch2[1] = (a >> 16) & 0XFF;
        p.ch3 = (a >> 24) & 0XFF;
        printf("byte1: %d \n", p.ch1);
        printf("byte2: %d \n", p.ch2[0]);
        printf("byte3: %d\n", p.ch2[1]);
        printf("byte4: %d\n", p.ch3);
        printf("Number is :%d", p.ch1 | (p.ch2[0] << 8) | (p.ch2[1] << 16) | (p.ch3 << 24));
        return 0;
}