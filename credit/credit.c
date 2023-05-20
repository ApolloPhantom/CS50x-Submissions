#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long int n;
    printf("Number: ");
    scanf("%ld",&n);
    int p=1;
    int s=0;
    int z;
    while(n!=0){
        int y=n%10;
        if(p%2!=0){
            s+=y;
        }
        else{
            if((2*y)>=10){
                s += (2*y)/10 + (2*y)%10;
            }
            else{
                s+= 2*y;
            }
        }
        if(n>=10 && n<100){
            z=n;
        }
        p++;
        n=n/10;
    }
    if((s%10==0) && ((z==34) || (z==37) || (z>=51 && z<=55) || (z>=40 && z<= 49) )){
        if((z==34) || (z==37) && (p-1)==15 ){
            printf("AMEX\n");
        }
        else if((z>=51) && (z<=55) && (p-1)==16){
            printf("MASTERCARD\n");
        }
        else if((z>=40) && (z<=49) && ((p-1)==16 || (p-1)==13) ){
            printf("VISA\n");
        }
        else{
            printf("INVALID\n");
        }
    }
    else{
        printf("INVALID\n");
    }
}