#include <stdio.h>
int main()
{
    int num;
    printf("enter the number");
    scanf("%d", &num);
    char b1, b2, b3, b4;
    b1 = (num & 0xFF);
    b2 = (num >> 8) & 0xFF;
    b3 = (num >> 16) & 0xFF;
    b4 = (num >> 24) & 0xFF;
    printf("Byte 1 : %x Address : %p \n",b1,&b1);
    printf("Byte 2 : %x Address : %p \n",b2,&b2);
    printf("Byte 3 : %x Address : %p \n",b3,&b3);
    printf("Byte 4 : %x Address : %p \n",b4,&b4);
    if(&b1<&b2)
    {
            printf("Little Endian\n");
            int n = (b4 & 0xFF) | ((b3 & 0xFF) << 8) | ((b2 & 0xFF) << 16) | ((b1 & 0xFF) << 24);
            printf("No in Big Endian :%x \n",n);

    }
    else
    {
        printf("Big Endian\n");
        int n = (b4 & 0xFF) | ((b3 & 0xFF) << 8) | ((b2 & 0xFF) << 16) | ((b1 & 0xFF) << 24);
        printf("No in Little Endian :%x \n",n);
    }
    return 0;
}