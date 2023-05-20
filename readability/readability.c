#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string text = get_string("Text: ");
    float L=0;
    float W=0;
    float S=0;
    for(int i=0;text[i]!='\0';i++){
        char y = text[i];
        if(y==' '){
            W += 1;
        }
        else if(y=='.' || y=='!' || y=='?'){
            if(text[i+1]!='.'){
                S +=1;
            }
        }
        else if(y!=',' && y!=';' && y!='"' && y!='-' && y!=(char)39){
            L += 1;
            printf("%c",y);
        }
    }
    W+=1;
    printf("%f Letters\n %f Words\n %f Sentences\n",L,W,S);
    float X,Y;
    X = (L/W);
    Y = (S/W);
    printf("X=%f Y=%f\n",X,Y);
    float n = 0.0588 * X * 100  - 0.296 * Y * 100 - 15.8;
    if(n>=16){
        printf("Grade 16+\n");
    }
    else if(n<1){
        printf("Before Grade 1\n");
    }
    else{
        if(n > ((int)(n) + 0.5)){
            printf("Grade %d\n",(int)n + 1);
        }
        else{
            printf("Grade %d\n",(int)n);
        }
    }
}