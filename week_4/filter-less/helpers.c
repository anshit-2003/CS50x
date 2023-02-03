#include "helpers.h"
#include<math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            float avg = (image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0;
            int grey = round(avg);
            image[i][j].rgbtBlue = round(grey);
            image[i][j].rgbtRed = round(grey);
            image[i][j].rgbtGreen = round(grey);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            float R = image[i][j].rgbtRed;
            float G = image[i][j].rgbtGreen;
            float B = image[i][j].rgbtBlue;

            float sepiared = (0.393 * R) + (0.769 * G) + (0.189 * B);
            float sepiagreen = (0.349 * R) + (0.686 * G) + (0.168 * B);
            float sepiablue  = (0.272 * R) + (0.534 * G) + (0.131 * B);

            if (round(sepiared) > 255)
            {
                sepiared = 255;
            }
            if (round(sepiagreen) > 255)
            {
                sepiagreen = 255;
            }
            if (round(sepiablue) > 255)
            {
                sepiablue = 255;

            }
            image[i][j].rgbtRed = round(sepiared);
            image[i][j].rgbtBlue = round(sepiablue);
            image[i][j].rgbtGreen = round(sepiagreen);

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width / 2 ; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            int R, G, B;
            R = 0;
            G = 0;
            B = 0;
            float pixel_count = 0;
            for (int m = - 1 ; m < 2 ; m++)
            {
                for (int n = -1 ; n < 2 ; n++)
                {
                    int pos_m = i + m;
                    int pos_n = j + n;
                    if (pos_m  < 0 || pos_m > (height - 1) || pos_n < 0 || pos_n > (width - 1))
                    {
                        continue;
                    }
                    R = R + image[pos_m][pos_n].rgbtRed;
                    G = G + image[pos_m][pos_n].rgbtGreen;
                    B = B + image[pos_m][pos_n].rgbtBlue;
                    pixel_count++;

                }
            }
            temp[i][j].rgbtBlue = round(B / pixel_count);
            temp[i][j].rgbtRed = round(R / pixel_count);
            temp[i][j].rgbtGreen = round(G / pixel_count);
        }
    }
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }
    return;
}
