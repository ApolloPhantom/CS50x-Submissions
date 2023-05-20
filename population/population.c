#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int x,y,n=0;
    printf("Start Size: ");
    scanf("%d",&x);
    while(1){
    if(x<9){
        printf("Invalid Size, Enter Start Size Again");
        scanf("%d",&x);
    }
    else{
        break;
    }
    }
    printf("End Size: ");
    scanf("%d",&y);
    while(1){
    if(y<x){
        printf("Invalid Size, Enter End Size Again");
        scanf("%d",&y);
    }
    else{
        break;
    }
    }
    while(x<y){
        x = x/3 - x/4 +x;
        n++;
    }
    printf("Years: %d\n",n);
}
