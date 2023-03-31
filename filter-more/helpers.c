#include "helpers.h"
#include <math.h>
#include <stdio.h>

typedef struct
{
int red;
int green;
int blue;
}
placeholder;


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++) //loop averaging
        {
            int avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width / 2; j++) //flipping around, kind of like sorting
        {
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;
            int red = image[i][j].rgbtRed;

            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;

            image[i][width - j - 1].rgbtBlue = blue;
            image[i][width - j - 1].rgbtGreen = green;
            image[i][width - j - 1].rgbtRed = red;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    placeholder blur[height][width];

    for (int i = 0; i < height; i++) //making a placeholder
    {
        for (int j = 0; j < width; j++)
        {
            blur[i][j].red = image[i][j].rgbtRed;
            blur[i][j].green = image[i][j].rgbtGreen;
            blur[i][j].blue = image[i][j].rgbtBlue;
        }
    }


    //everything except edges
    for(int i = 1; i < height - 1; i++)
    {
        for(int j = 1; j < width - 1; j++)
        {
            int sumb = 0;
            int sumg = 0;
            int sumr = 0;
            int avg;
            for(int x = -1; x < 2; x++)
            {
                for(int y = -1; y < 2; y++)
                {
                    sumb += blur[i + x][j + y].blue;
                    sumg += blur[i + x][j + y].green;
                    sumr += blur[i + x][j + y].red;
                }
            }
            avg = round(sumb / 9.0); //averaging and storing
            image[i][j].rgbtBlue = avg;
            avg = round(sumg / 9.0);
            image[i][j].rgbtGreen = avg;
            avg = round(sumr / 9.0);
            image[i][j].rgbtRed = avg;
        }
    }
    //left edge, top left and bottom left
    for (int i = 0; i < height; i++)
    {
        int j = 0;
        int sumb = 0;
        int sumg = 0;
        int sumr = 0;
        int avg;
        if(i == 0)
        {
            for(int x = 0; x < 2; x++)
            {
                for(int y = 0; y < 2; y++) //summing blurred values per color per pixel
                {
                    sumb += blur[i + x][j + y].blue;
                    sumg += blur[i + x][j + y].green;
                    sumr += blur[i + x][j + y].red;
                }
            }
            avg = round(sumb / 4.0); //averaging and storing
            image[i][j].rgbtBlue = avg;
            avg = round(sumg / 4.0);
            image[i][j].rgbtGreen = avg;
            avg = round(sumr / 4.0);
            image[i][j].rgbtRed = avg;
        }
        else if(i == (height - 1)) //for bottom corner
        {
            for(int x = -1; x < 1; x++)
            {
                for(int y = 0; y < 2; y++)
                {
                    sumb += blur[i + x][j + y].blue;
                    sumg += blur[i + x][j + y].green;
                    sumr += blur[i + x][j + y].red;
                }
            }
            avg = round(sumb / 4.0);
            image[i][j].rgbtBlue = avg;
            avg = round(sumg / 4.0);
            image[i][j].rgbtGreen = avg;
            avg = round(sumr / 4.0);
            image[i][j].rgbtRed = avg;
        }
        else
        {
            for(int x = -1; x < 2; x++)
            {
                for(int y = 0; y < 2; y++)
                {
                    sumb += blur[i + x][j + y].blue;
                    sumg += blur[i + x][j + y].green;
                    sumr += blur[i + x][j + y].red;
                }
            }
            avg = round(sumb / 6.0); //averaging and storing
            image[i][j].rgbtBlue = avg;
            avg = round(sumg / 6.0);
            image[i][j].rgbtGreen = avg;
            avg = round(sumr / 6.0);
            image[i][j].rgbtRed = avg;
        }
    }

    //TOP edge except top left
    for (int j = 1; j < width; j++)
    {
        int i = 0;
        int sumb = 0;
        int sumg = 0;
        int sumr = 0;
        int avg;
        if(j == (width - 1))
        {
            for(int x = 0; x < 2; x++)
            {
                for(int y = -1; y < 1; y++) //repeated, should really make a fxn
                {
                    sumb += blur[i + x][j + y].blue;
                    sumg += blur[i + x][j + y].green;
                    sumr += blur[i + x][j + y].red;
                }
            }
            avg = round(sumb / 4.0); //avg an store, should make a fxn
            image[i][j].rgbtBlue = avg;
            avg = round(sumg / 4.0);
            image[i][j].rgbtGreen = avg;
            avg = round(sumr / 4.0);
            image[i][j].rgbtRed = avg;
        }
        else
        {
            for(int x = 0; x < 2; x++)
            {
                for(int y = -1; y < 2; y++)
                {
                    sumb += blur[i + x][j + y].blue;
                    sumg += blur[i + x][j + y].green;
                    sumr += blur[i + x][j + y].red;
                }
            }
            avg = round(sumb / 6.0); //avg and store, should make a fxn
            image[i][j].rgbtBlue = avg;
            avg = round(sumg / 6.0);
            image[i][j].rgbtGreen = avg;
            avg = round(sumr / 6.0);
            image[i][j].rgbtRed = avg;
        }
    }

    //right edge except top right
    for (int i = 1; i < height; i++)
    {
        int j = width - 1;
        int sumb = 0;
        int sumg = 0;
        int sumr = 0;
        int avg;
        if(i == (height - 1))
        {
            for(int x = -1; x < 1; x++)
            {
                for(int y = -1; y < 1; y++)
                {
                    sumb += blur[i + x][j + y].blue;
                    sumg += blur[i + x][j + y].green;
                    sumr += blur[i + x][j + y].red;
                }
            }
            avg = round(sumb / 4.0); //avg and store, should make a fxn
            image[i][j].rgbtBlue = avg;
            avg = round(sumg / 4.0);
            image[i][j].rgbtGreen = avg;
            avg = round(sumr / 4.0);
            image[i][j].rgbtRed = avg;
        }
        else
        {
            for(int x = -1; x < 2; x++)
            {
                for(int y = -1; y < 1; y++)
                {
                    sumb += blur[i + x][j + y].blue;
                    sumg += blur[i + x][j + y].green;
                    sumr += blur[i + x][j + y].red;
                }
            }
            avg = round(sumb / 6.0);
            image[i][j].rgbtBlue = avg;
            avg = round(sumg / 6.0);
            image[i][j].rgbtGreen = avg;
            avg = round(sumr / 6.0);
            image[i][j].rgbtRed = avg;
        }
    }

    //bottom edge except bottom right and left
    for (int j = 1; j < width - 1; j++)
    {
        int i = height - 1;
        int sumb = 0;
        int sumg = 0;
        int sumr = 0;
        int avg;
            for(int x = -1; x < 1; x++)
            {
                for(int y = -1; y < 2; y++) //same stuff
                {
                    sumb += blur[i + x][j + y].blue;
                    sumg += blur[i + x][j + y].green;
                    sumr += blur[i + x][j + y].red;
                }
            }
            avg = round(sumb / 6.0);
            image[i][j].rgbtBlue = avg;
            avg = round(sumg / 6.0); //same
            image[i][j].rgbtGreen = avg;
            avg = round(sumr / 6.0);
            image[i][j].rgbtRed = avg;
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    placeholder blur[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++) //filling array again, should see how to declare earlier and once
        {
            blur[i][j].red = image[i][j].rgbtRed;
            blur[i][j].green = image[i][j].rgbtGreen;
            blur[i][j].blue = image[i][j].rgbtBlue;
        }
    }

    int gxbox[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}}; //setting up kernels
    int gybox[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};
    float gx;
    float gy;

    //everything except edges
    for(int i = 1; i < height - 1; i++)
    {
        for(int j = 1; j < width - 1; j++)
        {
            int sumbx = 0;
            int sumgx = 0;
            int sumrx = 0;
            int sumby = 0;
            int sumgy = 0;
            int sumry = 0;
            int avg;
            for(int x = -1; x < 2; x++)
            {
                for(int y = -1; y < 2; y++)
                {
                    sumbx += (blur[i + x][j + y].blue * gxbox[1 + x][1 + y]); //same
                    sumgx += (blur[i + x][j + y].green * gxbox[1 + x][1 + y]);
                    sumrx += (blur[i + x][j + y].red * gxbox[1 + x][1 + y]);
                    sumby += (blur[i + x][j + y].blue * gybox[1 + x][1 + y]);
                    sumgy += (blur[i + x][j + y].green * gybox[1 + x][1 + y]);
                    sumry += (blur[i + x][j + y].red * gybox[1 + x][1 + y]);
                }
            }
             avg = round(pow(sumbx, 2) + pow(sumby, 2)); //terrible design, make fxn
        if (round(sqrt(avg / 1.0)) > 255)
        {
            image[i][j].rgbtBlue = 255;
        }
        else
        {
            image[i][j].rgbtBlue = round(sqrt(avg / 1.0));
        }
        avg = round(pow(sumgx, 2) + pow(sumgy, 2));
        if (round(sqrt(avg / 1.0)) > 255)
        {
            image[i][j].rgbtGreen = 255;
        }
        else
        {
            image[i][j].rgbtGreen = round(sqrt(avg / 1.0));
        }
        avg = round(pow(sumrx, 2) + pow(sumry, 2));
        if (round(sqrt(avg / 1.0)) > 255)
        {
            image[i][j].rgbtRed = 255;
        }
        else
        {
            image[i][j].rgbtRed = round(sqrt(avg / 1.0));
        }
        }
    }
    //left edge, top left and bottom left
    for (int i = 0; i < height; i++)
    {
        int j = 0;
        int sumbx = 0;
        int sumgx = 0; //same
        int sumrx = 0;
        int sumby = 0;
        int sumgy = 0;
        int sumry = 0;
        int avg;
        if(i == 0)
        {
            for(int x = 0; x < 2; x++)
            {
                for(int y = 0; y < 2; y++)
                {
                    sumbx += (blur[i + x][j + y].blue * gxbox[1 + x][1 + y]);
                    sumgx += (blur[i + x][j + y].green * gxbox[1 + x][1 + y]);
                    sumrx += (blur[i + x][j + y].red * gxbox[1 + x][1 + y]);
                    sumby += (blur[i + x][j + y].blue * gybox[1 + x][1 + y]);
                    sumgy += (blur[i + x][j + y].green * gybox[1 + x][1 + y]);
                    sumry += (blur[i + x][j + y].red * gybox[1 + x][1 + y]);
                }
            }
            avg = round(pow(sumbx, 2) + pow(sumby, 2)); //same...
        if (round(sqrt(avg / 1.0)) > 255)
        {
            image[i][j].rgbtBlue = 255;
        }
        else
        {
            image[i][j].rgbtBlue = round(sqrt(avg / 1.0));
        }
        avg = round(pow(sumgx, 2) + pow(sumgy, 2));
        if (round(sqrt(avg / 1.0)) > 255)
        {
            image[i][j].rgbtGreen = 255;
        }
        else
        {
            image[i][j].rgbtGreen = round(sqrt(avg / 1.0));
        }
        avg = round(pow(sumrx, 2) + pow(sumry, 2));
        if (round(sqrt(avg / 1.0)) > 255)
        {
            image[i][j].rgbtRed = 255;
        }
        else
        {
            image[i][j].rgbtRed = round(sqrt(avg / 1.0));
        }
        }
        else if(i == (height - 1))
        {
            for(int x = -1; x < 1; x++)
            {
                for(int y = 0; y < 2; y++)
                {
                    sumbx += (blur[i + x][j + y].blue * gxbox[1 + x][1 + y]); //same...
                    sumgx += (blur[i + x][j + y].green * gxbox[1 + x][1 + y]);
                    sumrx += (blur[i + x][j + y].red * gxbox[1 + x][1 + y]);
                    sumby += (blur[i + x][j + y].blue * gybox[1 + x][1 + y]);
                    sumgy += (blur[i + x][j + y].green * gybox[1 + x][1 + y]);
                    sumry += (blur[i + x][j + y].red * gybox[1 + x][1 + y]);
                }
            }
            avg = round(pow(sumbx, 2) + pow(sumby, 2)); //ewww same
        if (round(sqrt(avg / 1.0)) > 255)
        {
            image[i][j].rgbtBlue = 255;
        }
        else
        {
            image[i][j].rgbtBlue = round(sqrt(avg / 1.0));
        }
        avg = round(pow(sumgx, 2) + pow(sumgy, 2));
        if (round(sqrt(avg / 1.0)) > 255)
        {
            image[i][j].rgbtGreen = 255;
        }
        else
        {
            image[i][j].rgbtGreen = round(sqrt(avg / 1.0));
        }
        avg = round(pow(sumrx, 2) + pow(sumry, 2));
        if (round(sqrt(avg / 1.0)) > 255)
        {
            image[i][j].rgbtRed = 255;
        }
        else
        {
            image[i][j].rgbtRed = round(sqrt(avg / 1.0));
        }
        }
        else
        {
            for(int x = -1; x < 2; x++)
            {
                for(int y = 0; y < 2; y++)
                {
                    sumbx += (blur[i + x][j + y].blue * gxbox[1 + x][1 + y]);
                    sumgx += (blur[i + x][j + y].green * gxbox[1 + x][1 + y]);
                    sumrx += (blur[i + x][j + y].red * gxbox[1 + x][1 + y]);
                    sumby += (blur[i + x][j + y].blue * gybox[1 + x][1 + y]);
                    sumgy += (blur[i + x][j + y].green * gybox[1 + x][1 + y]);
                    sumry += (blur[i + x][j + y].red * gybox[1 + x][1 + y]);
                }
            }
            avg = round(pow(sumbx, 2) + pow(sumby, 2)); //why hanan why
        if (round(sqrt(avg / 1.0)) > 255)
        {
            image[i][j].rgbtBlue = 255;
        }
        else
        {
            image[i][j].rgbtBlue = round(sqrt(avg / 1.0));
        }
        avg = round(pow(sumgx, 2) + pow(sumgy, 2));
        if (round(sqrt(avg / 1.0)) > 255)
        {
            image[i][j].rgbtGreen = 255;
        }
        else
        {
            image[i][j].rgbtGreen = round(sqrt(avg / 1.0));
        }
        avg = round(pow(sumrx, 2) + pow(sumry, 2));
        if (round(sqrt(avg / 1.0)) > 255)
        {
            image[i][j].rgbtRed = 255;
        }
        else
        {
            image[i][j].rgbtRed = round(sqrt(avg / 1.0));
        }
        }
    }

    //TOP edge except top left
    for (int j = 1; j < width; j++)
    {
        int i = 0;
        int sumbx = 0;
        int sumgx = 0;
        int sumrx = 0;
        int sumby = 0;
        int sumgy = 0;
        int sumry = 0;
        int avg;
        if(j == (width - 1))
        {
            for(int x = 0; x < 2; x++)
            {
                for(int y = -1; y < 1; y++)
                {
                    sumbx += (blur[i + x][j + y].blue * gxbox[1 + x][1 + y]);
                    sumgx += (blur[i + x][j + y].green * gxbox[1 + x][1 + y]); //repeat all day
                    sumrx += (blur[i + x][j + y].red * gxbox[1 + x][1 + y]);
                    sumby += (blur[i + x][j + y].blue * gybox[1 + x][1 + y]);
                    sumgy += (blur[i + x][j + y].green * gybox[1 + x][1 + y]);
                    sumry += (blur[i + x][j + y].red * gybox[1 + x][1 + y]);
                }
            }
            avg = round(pow(sumbx, 2) + pow(sumby, 2));
        if (round(sqrt(avg / 1.0)) > 255)
        {
            image[i][j].rgbtBlue = 255;
        }
        else
        {
            image[i][j].rgbtBlue = round(sqrt(avg / 1.0));
        }
        avg = round(pow(sumgx, 2) + pow(sumgy, 2));
        if (round(sqrt(avg / 1.0)) > 255)
        {
            image[i][j].rgbtGreen = 255;
        }
        else
        {
            image[i][j].rgbtGreen = round(sqrt(avg / 1.0));
        }
        avg = round(pow(sumrx, 2) + pow(sumry, 2));
        if (round(sqrt(avg / 1.0)) > 255)
        {
            image[i][j].rgbtRed = 255;
        }
        else
        {
            image[i][j].rgbtRed = round(sqrt(avg / 1.0));
        }
        }
        else //why hanan why
        {
            for(int x = 0; x < 2; x++)
            {
                for(int y = -1; y < 2; y++)
                {
                    sumbx += (blur[i + x][j + y].blue * gxbox[1 + x][1 + y]);
                    sumgx += (blur[i + x][j + y].green * gxbox[1 + x][1 + y]);
                    sumrx += (blur[i + x][j + y].red * gxbox[1 + x][1 + y]);
                    sumby += (blur[i + x][j + y].blue * gybox[1 + x][1 + y]);
                    sumgy += (blur[i + x][j + y].green * gybox[1 + x][1 + y]);
                    sumry += (blur[i + x][j + y].red * gybox[1 + x][1 + y]);
                }
            }
            avg = round(pow(sumbx, 2) + pow(sumby, 2));
        if (round(sqrt(avg / 1.0)) > 255)
        {
            image[i][j].rgbtBlue = 255;
        }
        else
        {
            image[i][j].rgbtBlue = round(sqrt(avg / 1.0));
        }
        avg = round(pow(sumgx, 2) + pow(sumgy, 2));
        if (round(sqrt(avg / 1.0)) > 255)
        {
            image[i][j].rgbtGreen = 255;
        }
        else
        {
            image[i][j].rgbtGreen = round(sqrt(avg / 1.0));
        }
        avg = round(pow(sumrx, 2) + pow(sumry, 2));
        if (round(sqrt(avg / 1.0)) > 255)
        {
            image[i][j].rgbtRed = 255;
        }
        else
        {
            image[i][j].rgbtRed = round(sqrt(avg / 1.0));
        }
        }
    }

    //right edge except top right
    for (int i = 1; i < height; i++) //almost there
    {
        int j = width - 1;
        int sumbx = 0;
        int sumgx = 0;
        int sumrx = 0;
        int sumby = 0;
        int sumgy = 0;
        int sumry = 0;
        int avg;
        if(i == (height - 1))
        {
            for(int x = -1; x < 1; x++)
            {
                for(int y = -1; y < 1; y++)
                {
                    sumbx += (blur[i + x][j + y].blue * gxbox[1 + x][1 + y]);
                    sumgx += (blur[i + x][j + y].green * gxbox[1 + x][1 + y]);
                    sumrx += (blur[i + x][j + y].red * gxbox[1 + x][1 + y]);
                    sumby += (blur[i + x][j + y].blue * gybox[1 + x][1 + y]);
                    sumgy += (blur[i + x][j + y].green * gybox[1 + x][1 + y]);
                    sumry += (blur[i + x][j + y].red * gybox[1 + x][1 + y]);
                }
            }
            avg = round(pow(sumbx, 2) + pow(sumby, 2));
        if (round(sqrt(avg / 1.0)) > 255)
        {
            image[i][j].rgbtBlue = 255;
        }
        else
        {
            image[i][j].rgbtBlue = round(sqrt(avg / 1.0));
        }
        avg = round(pow(sumgx, 2) + pow(sumgy, 2));
        if (round(sqrt(avg / 1.0)) > 255)
        {
            image[i][j].rgbtGreen = 255;
        }
        else
        {
            image[i][j].rgbtGreen = round(sqrt(avg / 1.0));
        }
        avg = round(pow(sumrx, 2) + pow(sumry, 2));
        if (round(sqrt(avg / 1.0)) > 255)
        {
            image[i][j].rgbtRed = 255;
        }
        else
        {
            image[i][j].rgbtRed = round(sqrt(avg / 1.0));
        }
        }
        else
        {
            for(int x = -1; x < 2; x++)
            {
                for(int y = -1; y < 1; y++)
                {
                    sumbx += (blur[i + x][j + y].blue * gxbox[1 + x][1 + y]);
                    sumgx += (blur[i + x][j + y].green * gxbox[1 + x][1 + y]);
                    sumrx += (blur[i + x][j + y].red * gxbox[1 + x][1 + y]);
                    sumby += (blur[i + x][j + y].blue * gybox[1 + x][1 + y]);
                    sumgy += (blur[i + x][j + y].green * gybox[1 + x][1 + y]);
                    sumry += (blur[i + x][j + y].red * gybox[1 + x][1 + y]);
                }
            }
            avg = round(pow(sumbx, 2) + pow(sumby, 2));
        if (round(sqrt(avg / 1.0)) > 255) //still not there
        {
            image[i][j].rgbtBlue = 255;
        }
        else
        {
            image[i][j].rgbtBlue = round(sqrt(avg / 1.0));
        }
        avg = round(pow(sumgx, 2) + pow(sumgy, 2));
        if (round(sqrt(avg / 1.0)) > 255)
        {
            image[i][j].rgbtGreen = 255;
        }
        else
        {
            image[i][j].rgbtGreen = round(sqrt(avg / 1.0));
        }
        avg = round(pow(sumrx, 2) + pow(sumry, 2));
        if (round(sqrt(avg / 1.0)) > 255)
        {
            image[i][j].rgbtRed = 255;
        }
        else
        {
            image[i][j].rgbtRed = round(sqrt(avg / 1.0));
        }
        }
    }

    //bottom edge except bottom right and left
    for (int j = 1; j < width - 1; j++)
    {
        int i = height - 1;
        int sumbx = 0;
        int sumgx = 0;
        int sumrx = 0;
        int sumby = 0;
        int sumgy = 0;
        int sumry = 0;
        int avg;
            for(int x = -1; x < 1; x++) //oh my this is long
            {
                for(int y = -1; y < 2; y++)
                {
                    sumbx += (blur[i + x][j + y].blue * gxbox[1 + x][1 + y]);
                    sumgx += (blur[i + x][j + y].green * gxbox[1 + x][1 + y]);
                    sumrx += (blur[i + x][j + y].red * gxbox[1 + x][1 + y]);
                    sumby += (blur[i + x][j + y].blue * gybox[1 + x][1 + y]);
                    sumgy += (blur[i + x][j + y].green * gybox[1 + x][1 + y]);
                    sumry += (blur[i + x][j + y].red * gybox[1 + x][1 + y]);
                }
            }
            avg = round(pow(sumbx, 2) + pow(sumby, 2));
        if (round(sqrt(avg / 1.0)) > 255)
        {
            image[i][j].rgbtBlue = 255;
        }
        else
        {
            image[i][j].rgbtBlue = round(sqrt(avg / 1.0));
        }
        avg = round(pow(sumgx, 2) + pow(sumgy, 2));
        if (round(sqrt(avg / 1.0)) > 255)
        {
            image[i][j].rgbtGreen = 255;
        }
        else
        {
            image[i][j].rgbtGreen = round(sqrt(avg / 1.0));
        }
        avg = round(pow(sumrx, 2) + pow(sumry, 2));
        if (round(sqrt(avg / 1.0)) > 255)
        {
            image[i][j].rgbtRed = 255;
        }
        else
        {
            image[i][j].rgbtRed = round(sqrt(avg / 1.0));
        }
    }
 //too many lines
    return;
}
