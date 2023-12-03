#include<stdio.h>
#include<stdlib.h>    

int main()
{
    printf("\n\n\t\t Выключение сети Linux \n\n\n");

    system("ifconfig enp0s3 down");

    return 0;
}

