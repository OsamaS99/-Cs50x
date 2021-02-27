#include "helpers.h"
#include <math.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0 ; i < height ; i ++) {
        for (int j  =0  ; j < width ; j++) {
            int avg_channel = (int)(round(((float)(image[i][j].rgbtRed+image[i][j].rgbtGreen+image[i][j].rgbtBlue))/3.0));
            image[i][j].rgbtRed = avg_channel;
            image[i][j].rgbtGreen = avg_channel;
            image[i][j].rgbtBlue = avg_channel;
        }
    }
    return;
}
void swap(RGBTRIPLE * x , RGBTRIPLE *y) {
    RGBTRIPLE temp = *x ;
    *x = *y ;
    *y = temp;
}
// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0 ; i < height  ; i++) {
        for (int j = 0 ; j < width/2 ; j++) {
            int redtemp = image[i][j].rgbtRed;
            int greentemp = image[i][j].rgbtGreen;
            int bluetemp = image[i][j].rgbtBlue;
            image[i][j].rgbtRed = image[i][width-1-j].rgbtRed;
            image[i][j].rgbtGreen = image[i][width-1-j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width-1-j].rgbtBlue;
            image[i][width-1-j].rgbtRed = redtemp;
            image[i][width-1-j].rgbtGreen = greentemp;
            image[i][width-1-j].rgbtBlue = bluetemp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE cpy [height][width] ;
    for (int i = 0 ; i < height ; i++) {
        for (int j = 0 ; j < width ; j++) {
            if(i == 0 || i == height-1 || j == 0 ||j == width-1 ) {
                double sum_red = 0.0 ;
                double sum_green = 0.0 ;
                double sum_blue = 0.0 ;
                double divider = 0.0;
                int x_start= i-1 , x_end = i+2 , y_start=j-1 , y_end = j+2;
                if (i == 0){
                    x_start = i ;
                    divider = 6.0;
                    if(j == 0 ) {
                        y_start = j;
                        divider = 4.0;
                    }else if(j == width-1) {
                        y_end = j+1;
                        divider = 4.0;
                    }
                }else if(i == height-1) {
                    x_end = i+1;
                    divider = 6.0;
                    if(j == 0 ) {
                        y_start = j;
                        divider = 4.0;
                    }else if(j == width-1) {
                        y_end = j+1;
                        divider = 4.0;
                    }
                }else if(j == 0 ) {
                    y_start = j;
                    divider = 6.0;
                    if(i == 0 ) {
                        x_start = i;
                        divider = 4.0;
                    }else if(i == height-1) {
                        x_end = i+1;
                        divider = 4.0;
                    }
                }else if(j == width-1) {
                    y_end = j+1;
                    divider = 6.0;
                    if(i == 0 ) {
                        x_start = i;
                        divider = 4.0;
                    }else if(i == height-1) {
                        x_end = j+1;
                        divider = 4.0;
                    }
                }
                for (int x = x_start ; x  < x_end ; x++ ) {
                    for (int y = y_start ; y < y_end ; y++) {
                        sum_red += image[x][y].rgbtRed;
                        sum_green += image[x][y].rgbtGreen;
                        sum_blue += image[x][y].rgbtBlue;
                    }
                }
                cpy[i][j].rgbtRed = (int)(round(sum_red/divider));
                cpy[i][j].rgbtBlue = (int)(round(sum_blue/divider));
                cpy[i][j].rgbtGreen = (int)(round(sum_green/divider));

            }else {
                double sum_red = 0 ;
                double sum_green = 0 ;
                double sum_blue = 0;
                for (int x = i-1 ; x  < i+2 ; x++ ) {
                    for (int y = j-1 ; y < j+2 ; y++) {
                        sum_red += image[x][y].rgbtRed;
                        sum_green += image[x][y].rgbtGreen;
                        sum_blue += image[x][y].rgbtBlue;
                    }
                }
                cpy[i][j].rgbtRed = (int)(round(sum_red/(double)9.0));
                cpy[i][j].rgbtBlue = (int)(round(sum_blue/(double)9.0));
                cpy[i][j].rgbtGreen = (int)(round(sum_green/(double)9.0));

            }

        }
    }
    for (int i  =0 ; i < height ; i++) {
        for (int j = 0 ; j < width ; j++) {
            image[i][j] = cpy[i][j];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
