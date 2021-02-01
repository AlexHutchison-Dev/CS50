#include "helpers.h"
#include <math.h>
#include<stdio.h>




// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average = 0;

    for(int i =0 ; i < height; i++)
    {
        for(int j =0 ; j < width; j++)
        {
            // calculate average og RGB
            average = ((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            average = roundf((average * 100) / 100);
            // set RGB to average
            image[i][j].rgbtGreen = (int)average;
            image[i][j].rgbtBlue = (int)average;
            image[i][j].rgbtRed = (int)average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width,  RGBTRIPLE image[height][width])
{
    int original_rgb[3];

    for(int i =0 ; i < height; i++)
    {
        for(int j =0 ; j < width; j++)
        {
            // get current rgb values
            original_rgb[0] = image[i][j].rgbtGreen;
            original_rgb[1] = image[i][j].rgbtBlue;
            original_rgb[2] = image[i][j].rgbtRed;

            // apply sepia algorithm to rgb values
            float sepiaRed = roundf((.393 * original_rgb[2]) + (.769 * original_rgb[0]) + (.189 * original_rgb[1]));
            float sepiaGreen = roundf((.349 * original_rgb[2]) + (.686 * original_rgb[0]) + (.168 * original_rgb[1]));
            float sepiaBlue = roundf((.272 * original_rgb[2]) + (.534 * original_rgb[0]) + (.131 * original_rgb[1]));


            // check value within range 0 - 255
            sepiaRed =(sepiaRed > 255) ? sepiaRed = 255 : sepiaRed;
            sepiaRed = (sepiaRed < 0) ? sepiaRed = 0 : sepiaRed;
            sepiaGreen =(sepiaGreen > 255) ? sepiaGreen = 255 : sepiaGreen;
            sepiaGreen = (sepiaGreen < 0) ? sepiaGreen = 0 : sepiaGreen;
            sepiaBlue = (sepiaBlue > 255) ? sepiaBlue = 255 : sepiaBlue;
            sepiaBlue = (sepiaBlue < 0) ? sepiaBlue = 0 : sepiaBlue;

            //set new rgb values
            image[i][j].rgbtGreen = (int)sepiaGreen;
            image[i][j].rgbtBlue = (int)sepiaBlue;
            image[i][j].rgbtRed = (int)sepiaRed;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE buffer[width];

    // itterate over pixels
    for(int i =0 ; i < height; i++)
    {
        for(int j = width - 1, k = 0 ; k < width; --j, k++)
        {
            // read pixels into buffer in reverse
            buffer[k] = image[i][j];

        }

        for(int l = 0; l < width; l++)
        {
            // overwrite image with buffer
            image[i][l] = buffer[l];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE buffer[sizeof(height / sizeof(RGBTRIPLE))][sizeof(width / sizeof(RGBTRIPLE))];

    RGBTRIPLE totals[9];

    // itterate over pixels
    for(int i =0 ; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int count = 0;
            float new_RGB [3] ={0,0,0};

            // get average RGB for target pixel
            totals[count] = image[i][j];
            count ++;


            // gather target pixels rgb values
            if(i - 1 >= 0)
            {

                totals[count] = image[i - 1][j];
                count ++;

            }

            // evaluate if surrounding pixels relevant and if so gather rgb values
            if(i - 1 >= 0 && j - 1 >=0)
            {
                totals[count] = image[i - 1][j - 1];
                count ++;
            }
            if (i - 1 >= 0 && j + 1 <= width)
            {
               totals[count] = image[i - 1][j + 1];
                count ++;
            }
            if(i + 1 <= height)
            {
                totals[count] = image[i + 1][j];
                count ++;
            }
            if (i + 1 <= height && j + 1 <= width)
            {
                totals[count] = image[i + 1][j + 1];
                count ++;
            }
            if(i + 1 <= height && j - 1 >= 0)
            {
                totals[count] = image[i + 1][j - 1];
                count ++;
            }
            if(j - 1 >= 0)
            {

                    totals[count] = image[i][j - 1];
                    count ++;
            }
            if(j + 1 <= width)
            {

                    totals[count] = image[i][j + 1];
                    count ++;
            }
            // total clour values for the 9 pixels
            for(int m = 0; m < count; m++)
            {

                new_RGB[0] += totals[m].rgbtRed;
                new_RGB[1] += totals[m].rgbtGreen;
                new_RGB[2] += totals[m].rgbtBlue;
            }

            // average colour values for the 9 pixels
                new_RGB[0] = roundf(new_RGB[0] / count);
                new_RGB[1] = roundf(new_RGB[1] / count);
                new_RGB[2] = roundf(new_RGB[2] / count);



            //set new rgb values
            buffer[i][j].rgbtRed = (int)new_RGB[0];
            buffer[i][j].rgbtGreen = (int)new_RGB[1];
            buffer[i][j].rgbtBlue = (int)new_RGB[2];

            count =0;
        }


    }

    // itterate over pixels
    for(int i =0 ; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            // set image pixel to buffer pixel
            image[i][j].rgbtRed = buffer[i][j].rgbtRed;
            image[i][j].rgbtGreen = buffer[i][j].rgbtGreen;
            image[i][j].rgbtBlue = buffer[i][j].rgbtBlue;
        }
    }

    return;
}

