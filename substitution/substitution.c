#include <cs50.h>
#include <stdio.h>

int CIPHER[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};

int dup(string str,int k,int y){
    for(int i=0;i<y;i++){
        if(k==(int)str[i]){
            return 0;
        }
    }
    return 1;
}
int main(int argc, string argv[])
{
    if (argc == 1 || argc > 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    int flag = 0;
    string arg = argv[1];
    int i;
    for (i = 0; arg[i] != '\0'; i++)
    {
        int x = (int)(arg[i]);
        if (x >= 65 && x <= 90 && dup(arg,x,i)==1)
        {
            if (CIPHER[i] != x - 65)
            {
                CIPHER[i] = x - 65;
            }
            else
            {
                printf("Usage: ./substitution key\n");
                return 1;
                break;
            }
        }
        else if (x >= 97 && x <= 122 && dup(arg,x,i)==1)
        {
            if (CIPHER[i] != x - 97)
            {
                CIPHER[i] = x - 97;
            }
            else
            {
                printf("Usage: ./substitution key\n");
                return 1;
                break;
            }
        }
        else
        {
            printf("Usage: ./substitution key\n");
            return 1;
            break;
        }
    }
    if (i < 25)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else
    {
        string word = get_string("plaintext: ");
        for (int j = 0; word[j] != '\0'; j++)
        {
            int y = (int)word[j];
            if (y >= 65 && y <= 90)
            {
                y = CIPHER[y - 65] + 65;
                // printf(" %d ",y);
                word[j] = (char)y;
            }
            else if (y >= 97 && y <= 122)
            {
                y = CIPHER[y - 97] + 97;
                // printf(" %d ",y);
                word[j] = (char)y;
            }
        }
        printf("ciphertext: %s\n", word);
        return 0;
    }
}