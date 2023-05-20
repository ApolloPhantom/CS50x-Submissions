#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if(argc<2){
        printf("Usage: ./reverse input.wav output.wav");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *infile;
    infile = fopen(argv[1],"rb");
    if(infile==NULL){
        exit(1);
    }
    // Read header
    // TODO #3
    WAVHEADER header;
    fread(&header, sizeof(header), 1, infile);

    // Use check_format to ensure WAV format
    // TODO #4
    if(check_format(header)!=1){
        return 1;
    }
    // Open output file for writing
    // TODO #5
    FILE *outfile;
    outfile = fopen(argv[2],"wb");
    if(outfile==NULL){
        outfile=fopen(argv[2],"wb+");
    }

    // Write header to file
    // TODO #6
    fwrite(&header,sizeof(header),1,outfile);


    // Use get_block_size to calculate size of block
    // TODO #7
    long int y = get_block_size(header);

    // Write reversed audio to file
    // TODO #8
    DWORD data_size = header.subchunk2Size;
    BYTE *data = (BYTE*)malloc(data_size);
    fread(data, data_size, 1, infile);
    DWORD i;
    for (i = 0; i < data_size / 2; i++) {
        BYTE tmp = data[i];
        data[i] = data[data_size - i - 1];
        data[data_size - i - 1] = tmp;
    }
    fwrite(data, data_size, 1, outfile);
    free(data);
    fclose(infile);
    fclose(outfile);
}

int check_format(WAVHEADER header)
{
    //TODO
    int a=(int)header.format[0];
    int b=(int)header.format[1];
    int c=(int)header.format[2];
    int d=(int)header.format[3];
    if(a==87 && b==65 && c==86 && d==69){
        return 1;
    }
    return 0;
}

int get_block_size(WAVHEADER header)
{
    int x = (int)round(header.bitsPerSample * header.numChannels * (1/8));
    return x;

}