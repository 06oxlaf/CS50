#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE Pix =  image[i][j];
            double Avg_Pix = (Pix.rgbtBlue + Pix.rgbtGreen + Pix.rgbtRed)/3.0;
            int AvgPix = round(Avg_Pix);
            image[i][j].rgbtBlue = AvgPix;
            image[i][j].rgbtGreen = AvgPix;
            image[i][j].rgbtRed = AvgPix;
        }
    }
return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE reflect[height][width];
    for (int i = 0; i < height; i++)
    {
    int x = width-1;
        for (int j = 0; j < width; j++)
        {
            reflect[i][j] =  image[i][x];
            x = x-1;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] =  reflect[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
RGBTRIPLE blur[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
        double AvgBlue = 0;
        double AvgGreen = 0;
        double AvgRed = 0;
        float n = 0.0;
                for (int x = i-1; x <= i+1; x++)
                {
                    if (-1 < x && x < height)
                    {
                        for (int y = j-1; y <= j+1; y++)
                        {
                            if (-1 < y && y < width)
                            {
                                AvgBlue = AvgBlue+ image[x][y].rgbtBlue;
                                AvgGreen = AvgGreen + image[x][y].rgbtGreen;
                                AvgRed = AvgRed + image[x][y].rgbtRed;
                                n = n+1;
                            }
                        }
                    }
                }
        int AvgBlue2 = round(AvgBlue/n);
        int AvgGreen2 = round(AvgGreen/n);
        int AvgRed2 = round(AvgRed/n);
        blur[i][j].rgbtBlue = AvgBlue2;
        blur[i][j].rgbtGreen = AvgGreen2;
        blur[i][j].rgbtRed = AvgRed2;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] =  blur[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
printf("%i\n", image[0][0].rgbtBlue);
printf("%i\n", image[0][1].rgbtBlue);
printf("%i\n", image[0][2].rgbtBlue);
printf("%i\n", image[1][0].rgbtBlue);
printf("%i\n", image[1][1].rgbtBlue);
printf("%i\n", image[1][2].rgbtBlue);
printf("%i\n", image[2][0].rgbtBlue);
printf("%i\n", image[2][1].rgbtBlue);
printf("%i\n", image[2][2].rgbtBlue);
    //GX
RGBTRIPLE GX[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
        int GXBlue = 0;
        int GXGreen = 0;
        int GXRed = 0;
            for (int y = i-1; y <= i+1; y++)
            {
                if (-1 < y && y < height)
                {
                int n = -1;
                    for (int x = j-1; x <= j+1; x++)
                    {
                        if (-1 < x && x < width)
                        {
                            if(i == y)
                            {
                                GXBlue = GXBlue + (image[x][y].rgbtBlue*(n*2));
                                GXGreen = GXGreen + (image[x][y].rgbtGreen*(n*2));
                                GXRed = GXRed + (image[x][y].rgbtRed*(n*2));
                                n = n + 1;
                            }
                            else
                            {
                                GXBlue = GXBlue + (image[x][y].rgbtBlue*(n));
                                GXGreen = GXGreen + (image[x][y].rgbtGreen*(n));
                                GXRed = GXRed + (image[x][y].rgbtRed*(n));
                                n = n + 1;
                            }
                        }

                    }
                }
            }
        GX[i][j].rgbtBlue = GXBlue;
        GX[i][j].rgbtGreen = GXGreen;
        GX[i][j].rgbtRed = GXRed;
        }
    }
printf("%i\n", GX[1][1].rgbtBlue);
    //GY
RGBTRIPLE GY[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
        int GYBlue = 0;
        int GYGreen = 0;
        int GYRed = 0;
            for (int y = i-1; y <= i+1; y++)
            {
                if (-1 < y && y < height)
                {
                    for (int x = j-1; x <= j+1; x++)
                    {
                        if (-1 < x && x < width)
                        {
                            if(j == x)
                            {
                                GYBlue = GYBlue + (image[x][y].rgbtBlue*(y*2));
                                GYGreen = GYGreen + (image[x][y].rgbtGreen*(y*2));
                                GYRed = GYRed + (image[x][y].rgbtRed*(y*2));
                            }
                            else
                            {
                                GYBlue = GYBlue + (image[x][y].rgbtBlue*(y));
                                GYGreen = GYGreen + (image[x][y].rgbtGreen*(y));
                                GYRed = GYRed + (image[x][y].rgbtRed*(y));
                                }
                        }
                        }
                    }
                }
        GY[i][j].rgbtBlue = GYBlue;
        GY[i][j].rgbtGreen = GYGreen;
        GY[i][j].rgbtRed = GYRed;
        }
    }
printf("%i\n", GY[1][1].rgbtBlue);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int Blue = round(sqrt((pow(GX[i][j].rgbtBlue, 2) + pow(GY[i][j].rgbtBlue, 2))));
            int Green = round(sqrt((pow(GX[i][j].rgbtGreen, 2) + pow(GY[i][j].rgbtGreen, 2))));
            int Red = round(sqrt((pow(GX[i][j].rgbtRed, 2) + pow(GY[i][j].rgbtRed,2))));
            if (Blue > 255) Blue = 255;
            if (Green > 255) Green = 255;
            if (Red > 255) Red = 255;
            image[i][j].rgbtBlue = Blue;
            image[i][j].rgbtGreen = Green;
            image[i][j].rgbtRed = Red;
        }
    }

    return;
}
