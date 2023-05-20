#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if(argc<2){
        printf("Usage: ./recover IMAGE");
        return 1;
    }

    FILE *card;
    card = fopen(argv[1],"rb");
    if(card==NULL){
        return 1;
    }
    typedef uint8_t BYTE;
    BYTE str[512];
    int x=0;
    char * filename = (char *)malloc(8);
    sprintf(filename,"%03i.jpg",x);
    FILE * ptr;
    while (fread(str,1,512,card) == 512){
        if(x==0 && str[0] == 0xff  && str[1]== 0xd8  && str[2]== 0xff && (str[3] & 0xf0)==0xe0){
            ptr = fopen(filename,"wb");
            fwrite(str,1,512,ptr);
            x++;
        }
        else if(x!=0 && str[0] == 0xff  && str[1]== 0xd8  && str[2]== 0xff && (str[3] & 0xf0)==0xe0){
            fclose(ptr);
            sprintf(filename,"%03i.jpg",x);
            ptr=fopen(filename,"wb");
            fwrite(str,1,512,ptr);
            x++;
        }
        else{
            if(x!=0){
            fwrite(str,1,512,ptr);
            }
        }
    }

    fclose(ptr);
    fclose(card);
    free(filename);

}
