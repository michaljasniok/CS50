#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // takes average form all colors and sets it to all colors
    int avg;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            avg = round(((float)image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3);
            if (avg < 0 || avg > 255)
            {
                return;
            }
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // swaps first pixel with last
    int Red;
    int Green;
    int Blue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            Red = image[i][j].rgbtRed;
            Blue = image[i][j].rgbtBlue;
            Green = image[i][j].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j -1].rgbtGreen;
            image[i][width - j -1].rgbtRed = Red;
            image[i][width - j -1].rgbtBlue = Blue;
            image[i][width - j -1].rgbtGreen = Green;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float red;
    float green;
    float blue;
    int counter;
    RGBTRIPLE copy[height][width];
    for (int p = 0; p < height; p++)
    {
        for (int ff = 0; ff < width; ff++)
        {
            copy[p][ff] = image[p][ff];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red = 0;
            green = 0;
            blue = 0;
            counter = 0;
            for ( int z = 0; z < 3; z++)
            {
                for (int h = 0; h < 3; h++)
                {
                    if (i - 1 + z >= 0 && i - 1 + z < height && j - 1 + h >= 0 && j - 1 + h < width)
                    {
                    red = copy[i - 1 + z][j - 1 + h].rgbtRed + red;
                    green = copy[i - 1 + z][j - 1 + h].rgbtGreen + green;
                    blue = copy[i - 1 + z][j - 1 + h].rgbtBlue + blue;
                    counter++;
                    }
                }

            }
            image[i][j].rgbtRed = round(red / counter);
            image[i][j].rgbtGreen = round(green / counter);
            image[i][j].rgbtBlue = round(blue / counter);
        }
    }
    return;

}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // variables
    int color_red;
    int color_green;
    int color_blue;
    float gx_red;
    float gx_green;
    float gx_blue;
    float gy_red;
    float gy_green;
    float gy_blue;
    // arrays for multiplayers grid
    int gx_multiplayer[3][3];
    gx_multiplayer[0][0] = -1;
    gx_multiplayer[0][1] = 0;
    gx_multiplayer[0][2] = 1;
    gx_multiplayer[1][0] = -2;
    gx_multiplayer[1][1] = 0;
    gx_multiplayer[1][2] = 2;
    gx_multiplayer[2][0] = -1;
    gx_multiplayer[2][1] = 0;
    gx_multiplayer[2][2] = 1;

    int gy_multiplayer[3][3];
    gy_multiplayer[0][0] = -1;
    gy_multiplayer[0][1] = -2;
    gy_multiplayer[0][2] = -1;
    gy_multiplayer[1][0] = 0;
    gy_multiplayer[1][1] = 0;
    gy_multiplayer[1][2] = 0;
    gy_multiplayer[2][0] = 1;
    gy_multiplayer[2][1] = 2;
    gy_multiplayer[2][2] = 1;
    // copy of image
    RGBTRIPLE copy[height][width];
    // edge lords
    for (int c = 0; c < height; c++)
    {
        for (int cc = 0; cc < width; cc++)
        {
            copy[c][cc] = image[c][cc];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            gx_red = 0;
            gx_green = 0;
            gx_blue = 0;
            gy_red = 0;
            gy_green = 0;
            gy_blue = 0;
            for ( int row = 0; row < 3; row++)
            {
                for (int pixel = 0; pixel < 3; pixel++)
                {
                    if (i - 1 + row >= 0 && i - 1 + row < height && j - 1 + pixel >= 0 && j - 1 + pixel < width)
                    {
                        gx_red = gx_red + copy[i - 1 + row][j - 1 + pixel].rgbtRed * gx_multiplayer[row][pixel];
                        gx_green = gx_green + copy[i - 1 + row][j - 1 + pixel].rgbtGreen * gx_multiplayer[row][pixel];
                        gx_blue = gx_blue + copy[i - 1 + row][j - 1 + pixel].rgbtBlue * gx_multiplayer[row][pixel];
                        gy_red = gy_red + copy[i - 1 + row][j - 1 + pixel].rgbtRed * gy_multiplayer[row][pixel];
                        gy_green = gy_green + copy[i - 1 + row][j - 1 + pixel].rgbtGreen * gy_multiplayer[row][pixel];
                        gy_blue = gy_blue + copy[i - 1 + row][j - 1 + pixel].rgbtBlue * gy_multiplayer[row][pixel];
                    }
                }
            }
            color_red = round(sqrt(gx_red * gx_red + gy_red * gy_red));
            if(color_red > 255)
            {
                color_red = 255;
            }
            color_green = round(sqrt(gx_green * gx_green + gy_green * gy_green));
            if (color_green > 255)
            {
                color_green = 255;
            }
            color_blue = round(sqrt(gx_blue * gx_blue + gy_blue * gy_blue));
            if (color_blue > 255)
            {
                color_blue = 255;
            }
            image[i][j].rgbtRed = color_red;
            image[i][j].rgbtBlue = color_blue;
            image[i][j].rgbtGreen = color_green;
        }
    }
}
