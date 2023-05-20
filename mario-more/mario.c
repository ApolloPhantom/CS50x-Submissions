#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h=0;
    while(1){
        if(h>8){
            printf("Height: ");
            scanf("%d", &h);
        }
        else if(h<1){
            printf("Height: ");
            scanf("%d", &h);
        }
        else{
            break;
        }
    }
    for (int i = 1; i <= h; i++)
    {
        for (int p = 1; p <= h - i; p++)
        {
            printf(" ");
        }
        for (int p = 1; p <= i; p++)
        {
            printf("#");
        }
        printf("  ");
        for (int p = 1; p <= i; p++)
        {
            printf("#");
        }
        printf("\n");
    }
}