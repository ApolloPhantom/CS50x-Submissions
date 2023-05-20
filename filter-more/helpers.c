#include "helpers.h"
#include<math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            float x = (float)image[i][j].rgbtRed;
            float y = (float)image[i][j].rgbtBlue;
            float z = (float)image[i][j].rgbtGreen;
            float b = (x+y+z)/3;
            int a;
            if(b>=(int)b+0.5){
                a=(int)b+1;
            }
            else{
                a=(int)b;
            }
            image[i][j].rgbtRed=a;
            image[i][j].rgbtBlue=a;
            image[i][j].rgbtGreen=a;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i=0;i<height;i++){
        for(int j=0;j<width/2;j++){
            BYTE x = image[i][j].rgbtRed;
            BYTE y = image[i][j].rgbtBlue;
            BYTE z = image[i][j].rgbtGreen;
            image[i][j].rgbtRed=image[i][width - 1 - j].rgbtRed;
            image[i][j].rgbtBlue=image[i][width - 1 - j].rgbtBlue;
            image[i][j].rgbtGreen=image[i][width - 1 - j].rgbtGreen;
            image[i][width - 1 - j].rgbtRed=x;
            image[i][width - 1 - j].rgbtBlue=y;
            image[i][width - 1 - j].rgbtGreen=z;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE Image[height][width];
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            float a=0;
            float b=0;
            float c=0;
            float m=0;
            for(int x=i-1;x<=i+1;x++){
                if(x>=0 && x<=height-1){
                    for(int y=j-1;y<=j+1;y++){
                        if(y>=0 && y<=width-1){
                            a += (float)image[x][y].rgbtRed;
                            b += (float)image[x][y].rgbtBlue;
                            c += (float)image[x][y].rgbtGreen;
                            m += 1;
                        }
                        else{}
                    }
                }
                else{}
            }

            float p,q,r;
            p = (int)round(a/(m));
            q = (int)round(b/(m));
            r = (int)round(c/(m));
            Image[i][j].rgbtRed=(BYTE)(p);
            Image[i][j].rgbtBlue=(BYTE)(q);
            Image[i][j].rgbtGreen=(BYTE)(r);
        }
    }
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            image[i][j].rgbtRed=Image[i][j].rgbtRed;
            image[i][j].rgbtBlue=Image[i][j].rgbtBlue;
            image[i][j].rgbtGreen=Image[i][j].rgbtGreen;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE Image[height][width];
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            float ax=0,ay=0;
            float bx=0,by=0;
            float cx=0,cy=0;
            if(i>=0 && i<=height-1 && j>=0 && j<=width-1){
                ax+=0*(float)image[i][j].rgbtRed;
                bx+=0*(float)image[i][j].rgbtBlue;
                cx+=0*(float)image[i][j].rgbtGreen;
                ay+=0*(float)image[i][j].rgbtRed;
                by+=0*(float)image[i][j].rgbtBlue;
                cy+=0*(float)image[i][j].rgbtGreen;
            }
            else{
                ax+=0;
                bx+=0;
                cx+=0;
                ay+=0;
                by+=0;
                cy+=0;
            }
            if(i>=0 && i<=height-1 && j-1>=0 && j-1<=width-1){
                ax+=-2*(float)image[i][j-1].rgbtRed;
                bx+=-2*(float)image[i][j-1].rgbtBlue;
                cx+=-2*(float)image[i][j-1].rgbtGreen;
                ay+=0*(float)image[i][j-1].rgbtRed;
                by+=0*(float)image[i][j-1].rgbtBlue;
                cy+=0*(float)image[i][j-1].rgbtGreen;
            }
            else{
                ax+=0;
                bx+=0;
                cx+=0;
                ay+=0;
                by+=0;
                cy+=0;

            }
            if(i>=0 && i<=height-1 && j+1>=0 && j+1<=width-1){
                ax+=2*(float)image[i][j+1].rgbtRed;
                bx+=2*(float)image[i][j+1].rgbtBlue;
                cx+=2*(float)image[i][j+1].rgbtGreen;
                ay+=0*(float)image[i][j+1].rgbtRed;
                by+=0*(float)image[i][j+1].rgbtBlue;
                cy+=0*(float)image[i][j+1].rgbtGreen;
            }
            else{
                ax+=0;
                bx+=0;
                cx+=0;
                ay+=0;
                by+=0;
                cy+=0;

            }
            if(i-1>=0 && i-1<=height-1 && j>=0 && j<=width-1){
                ax+=0*(float)image[i-1][j].rgbtRed;
                bx+=0*(float)image[i-1][j].rgbtBlue;
                cx+=0*(float)image[i-1][j].rgbtGreen;
                ay+=-2*(float)image[i-1][j].rgbtRed;
                by+=-2*(float)image[i-1][j].rgbtBlue;
                cy+=-2*(float)image[i-1][j].rgbtGreen;
            }
            else{
                ax+=0;
                bx+=0;
                cx+=0;
                ay+=0;
                by+=0;
                cy+=0;
            }
            if(i-1>=0 && i-1<=height-1 && j-1>=0 && j-1<=width-1){
                ax+=-1*(float)image[i-1][j-1].rgbtRed;
                bx+=-1*(float)image[i-1][j-1].rgbtBlue;
                cx+=-1*(float)image[i-1][j-1].rgbtGreen;
                ay+=-1*(float)image[i-1][j-1].rgbtRed;
                by+=-1*(float)image[i-1][j-1].rgbtBlue;
                cy+=-1*(float)image[i-1][j-1].rgbtGreen;
            }
            else{
                ax+=0;
                bx+=0;
                cx+=0;
                ay+=0;
                by+=0;
                cy+=0;
            }
            if(i-1>=0 && i-1<=height-1 && j+1>=0 && j+1<=width-1){
                ax+=1*(float)image[i-1][j+1].rgbtRed;
                bx+=1*(float)image[i-1][j+1].rgbtBlue;
                cx+=1*(float)image[i-1][j+1].rgbtGreen;
                ay+=-1*(float)image[i-1][j+1].rgbtRed;
                by+=-1*(float)image[i-1][j+1].rgbtBlue;
                cy+=-1*(float)image[i-1][j+1].rgbtGreen;
            }
            else{
                ax+=0;
                bx+=0;
                cx+=0;
                ay+=0;
                by+=0;
                cy+=0;

            }
            if(i+1>=0 && i+1<=height-1 && j>=0 && j<=width-1){
                ax+=0*(float)image[i+1][j].rgbtRed;
                bx+=0*(float)image[i+1][j].rgbtBlue;
                cx+=0*(float)image[i+1][j].rgbtGreen;
                ay+=2*(float)image[i+1][j].rgbtRed;
                by+=2*(float)image[i+1][j].rgbtBlue;
                cy+=2*(float)image[i+1][j].rgbtGreen;
            }
            else{
                ax+=0;
                bx+=0;
                cx+=0;
                ay+=0;
                by+=0;
                cy+=0;

            }
            if(i+1>=0 && i+1<=height-1 && j+1>=0 && j+1<=width-1){
                ax+=1*(float)image[i+1][j+1].rgbtRed;
                bx+=1*(float)image[i+1][j+1].rgbtBlue;
                cx+=1*(float)image[i+1][j+1].rgbtGreen;
                ay+=1*(float)image[i+1][j+1].rgbtRed;
                by+=1*(float)image[i+1][j+1].rgbtBlue;
                cy+=1*(float)image[i+1][j+1].rgbtGreen;
            }
            else{
                ax+=0;
                bx+=0;
                cx+=0;
                ay+=0;
                by+=0;
                cy+=0;

            }
            if(i+1>=0 && i+1<=height-1 && j-1>=0 && j-1<=width-1){
                ax+=-1*(float)image[i+1][j-1].rgbtRed;
                bx+=-1*(float)image[i+1][j-1].rgbtBlue;
                cx+=-1*(float)image[i+1][j-1].rgbtGreen;
                ay+=1*(float)image[i+1][j-1].rgbtRed;
                by+=1*(float)image[i+1][j-1].rgbtBlue;
                cy+=1*(float)image[i+1][j-1].rgbtGreen;
            }
            else{
                ax+=0;
                bx+=0;
                cx+=0;
                ay+=0;
                by+=0;
                cy+=0;
            }
            float p,q,r;
            p = (int)round(sqrt((ax*ax) + (ay*ay)));
            q = (int)round(sqrt((bx*bx) + (by*by)));
            r = (int)round(sqrt((cx*cx) + (cy*cy)));
            if(p>255){
                p=255;
            }
            else{}
            if(q>255){
                q=255;
            }
            else{}
            if(r>255){
                r=255;
            }
            Image[i][j].rgbtRed=(BYTE)(p);
            Image[i][j].rgbtBlue=(BYTE)(q);
            Image[i][j].rgbtGreen=(BYTE)(r);
        }
    }
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            image[i][j].rgbtRed=Image[i][j].rgbtRed;
            image[i][j].rgbtBlue=Image[i][j].rgbtBlue;
            image[i][j].rgbtGreen=Image[i][j].rgbtGreen;
        }
    }
    return;
}
