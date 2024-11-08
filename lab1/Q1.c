#include<stdio.h>
#include<stdlib.h>
void swap(int *a, int *b){
    int temp = *a; 
    *a = *b;
    *b = temp;
}

int main(int argsc, char* argsv[]){
    int a;
    a = atoi(argsv[1]);
    int b;
    b = atoi(argsv[2]);
    printf("the values that you have entered as a = %d and b = %d\n", a, b);
    swap(&a, &b);
    printf("the values after the swap is a = %d and b = %d\n", a, b);

    return 0;
}