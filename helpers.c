#include "helpers.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / (float) 3;
            image[i][j].rgbtBlue = round(average);
            image[i][j].rgbtGreen = round(average);
            image[i][j].rgbtRed = round(average);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalBlue = image[i][j].rgbtBlue;
            int originalGreen = image[i][j].rgbtGreen;
            int originalRed = image[i][j].rgbtRed;

            int newBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            int newGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int newRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);

            if (newBlue <= 255)
            {
                image[i][j].rgbtBlue = newBlue;
            }
            else
            {
                image[i][j].rgbtBlue = 255;
            }

            if (newGreen <= 255)
            {
                image[i][j].rgbtGreen = newGreen;
            }
            else
            {
                image[i][j].rgbtGreen = 255;
            }

            if (newRed <= 255)
            {
                image[i][j].rgbtRed = newRed;
            }
            else
            {
                image[i][j].rgbtRed = 255;
            }
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*imageCopy)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    memcpy(imageCopy, image, sizeof(RGBTRIPLE) * height * width);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Corner Cases
            if (i == 0 && j == 0)
            {
                float blur_avg_blue = (imageCopy[i][j].rgbtBlue + imageCopy[i][j + 1].rgbtBlue + imageCopy[i + 1][j].rgbtBlue + imageCopy[i + 1][j + 1].rgbtBlue) / (float) 4;
                float blur_avg_green = (imageCopy[i][j].rgbtGreen + imageCopy[i][j + 1].rgbtGreen + imageCopy[i + 1][j].rgbtGreen + imageCopy[i + 1][j + 1].rgbtGreen) / (float) 4;
                float blur_avg_red = (imageCopy[i][j].rgbtRed + imageCopy[i][j + 1].rgbtRed + imageCopy[i + 1][j].rgbtRed + imageCopy[i + 1][j + 1].rgbtRed) / (float) 4;

                image[i][j].rgbtBlue = round(blur_avg_blue);
                image[i][j].rgbtGreen = round(blur_avg_green);
                image[i][j].rgbtRed = round(blur_avg_red);

            }
            else if (i == 0 && j == width - 1)
            {
                float blur_avg_blue = (imageCopy[i][j].rgbtBlue + imageCopy[i][j - 1].rgbtBlue + imageCopy[i + 1][j - 1].rgbtBlue + imageCopy[i + 1][j].rgbtBlue) / (float) 4;
                float blur_avg_green = (imageCopy[i][j].rgbtGreen + imageCopy[i][j - 1].rgbtGreen + imageCopy[i + 1][j - 1].rgbtGreen + imageCopy[i + 1][j].rgbtGreen) / (float) 4;
                float blur_avg_red = (imageCopy[i][j].rgbtRed + imageCopy[i][j - 1].rgbtRed + imageCopy[i + 1][j - 1].rgbtRed + imageCopy[i + 1][j].rgbtRed) / (float) 4;

                image[i][j].rgbtBlue = round(blur_avg_blue);
                image[i][j].rgbtGreen = round(blur_avg_green);
                image[i][j].rgbtRed = round(blur_avg_red);

            }
            else if (i == height - 1 && j == 0)
            {
                float blur_avg_blue = (imageCopy[i][j].rgbtBlue + imageCopy[i][j + 1].rgbtBlue + imageCopy[i - 1][j].rgbtBlue + imageCopy[i - 1][j+1].rgbtBlue) / (float) 4;
                float blur_avg_green = (imageCopy[i][j].rgbtGreen + imageCopy[i][j + 1].rgbtGreen + imageCopy[i - 1][j].rgbtGreen + imageCopy[i - 1][j + 1].rgbtGreen) / (float) 4;
                float blur_avg_red = (imageCopy[i][j].rgbtRed + imageCopy[i][j + 1].rgbtRed + imageCopy[i - 1][j].rgbtRed + imageCopy[i - 1][j + 1].rgbtRed) / (float) 4;

                image[i][j].rgbtBlue = round(blur_avg_blue);
                image[i][j].rgbtGreen = round(blur_avg_green);
                image[i][j].rgbtRed = round(blur_avg_red);

            }
            else if (i == height - 1 && j == width - 1)
            {
                float blur_avg_blue = (imageCopy[i][j].rgbtBlue + imageCopy[i][j - 1].rgbtBlue + imageCopy[i - 1][j].rgbtBlue + imageCopy[i - 1][j - 1].rgbtBlue) / (float) 4;
                float blur_avg_green = (imageCopy[i][j].rgbtGreen + imageCopy[i][j - 1].rgbtGreen + imageCopy[i - 1][j].rgbtGreen + imageCopy[i - 1][j - 1].rgbtGreen) / (float) 4;
                float blur_avg_red = (imageCopy[i][j].rgbtRed + imageCopy[i][j - 1].rgbtRed + imageCopy[i - 1][j].rgbtRed + imageCopy[i - 1][j - 1].rgbtRed) / (float) 4;

                image[i][j].rgbtBlue = round(blur_avg_blue);
                image[i][j].rgbtGreen = round(blur_avg_green);
                image[i][j].rgbtRed = round(blur_avg_red);
            }
            // Edge Cases
            else if (i == 0)
            {
                float blur_avg_blue = (imageCopy[i][j - 1].rgbtBlue + imageCopy[i][j].rgbtBlue + imageCopy[i][j + 1].rgbtBlue + imageCopy[i + 1][j - 1].rgbtBlue + imageCopy[i + 1][j].rgbtBlue + imageCopy[i + 1][j + 1].rgbtBlue) / (float) 6;
                float blur_avg_green = (imageCopy[i][j - 1].rgbtGreen + imageCopy[i][j].rgbtGreen + imageCopy[i][j + 1].rgbtGreen + imageCopy[i + 1][j - 1].rgbtGreen + imageCopy[i + 1][j].rgbtGreen + imageCopy[i + 1][j + 1].rgbtGreen) / (float) 6;
                float blur_avg_red = (imageCopy[i][j - 1].rgbtRed + imageCopy[i][j].rgbtRed + imageCopy[i][j + 1].rgbtRed + imageCopy[i + 1][j - 1].rgbtRed + imageCopy[i + 1][j].rgbtRed + imageCopy[i + 1][j + 1].rgbtRed) / (float) 6;

                image[i][j].rgbtBlue = round(blur_avg_blue);
                image[i][j].rgbtGreen = round(blur_avg_green);
                image[i][j].rgbtRed = round(blur_avg_red);

            }
            else if (j == 0)
            {
                float blur_avg_blue = (imageCopy[i][j].rgbtBlue + imageCopy[i][j + 1].rgbtBlue + imageCopy[i - 1][j].rgbtBlue + imageCopy[i - 1][j + 1].rgbtBlue + imageCopy[i + 1][j].rgbtBlue + imageCopy[i + 1][j + 1].rgbtBlue) / (float) 6;
                float blur_avg_green = (imageCopy[i][j].rgbtGreen + imageCopy[i][j + 1].rgbtGreen + imageCopy[i - 1][j].rgbtGreen + imageCopy[i - 1][j + 1].rgbtGreen + imageCopy[i + 1][j].rgbtGreen + imageCopy[i + 1][j + 1].rgbtGreen) / (float) 6;
                float blur_avg_red = (imageCopy[i][j].rgbtRed + imageCopy[i][j + 1].rgbtRed + imageCopy[i - 1][j].rgbtRed + imageCopy[i - 1][j + 1].rgbtRed + imageCopy[i + 1][j].rgbtRed + imageCopy[i + 1][j + 1].rgbtRed) / (float) 6;

                image[i][j].rgbtBlue = round(blur_avg_blue);
                image[i][j].rgbtGreen = round(blur_avg_green);
                image[i][j].rgbtRed = round(blur_avg_red);
            }
            else if (j == width - 1)
            {
                float blur_avg_blue = (imageCopy[i][j].rgbtBlue + imageCopy[i][j - 1].rgbtBlue + imageCopy[i - 1][j].rgbtBlue + imageCopy[i - 1][j - 1].rgbtBlue + imageCopy[i + 1][j].rgbtBlue + imageCopy[i + 1][j - 1].rgbtBlue) / (float) 6;
                float blur_avg_green = (imageCopy[i][j].rgbtGreen + imageCopy[i][j - 1].rgbtGreen + imageCopy[i - 1][j].rgbtGreen + imageCopy[i - 1][j - 1].rgbtGreen + imageCopy[i + 1][j].rgbtGreen + imageCopy[i + 1][j - 1].rgbtGreen) / (float) 6;
                float blur_avg_red = (imageCopy[i][j].rgbtRed + imageCopy[i][j - 1].rgbtRed + imageCopy[i - 1][j].rgbtRed + imageCopy[i - 1][j - 1].rgbtRed +imageCopy[i + 1][j].rgbtRed + imageCopy[i + 1][j - 1].rgbtRed) / (float) 6;

                image[i][j].rgbtBlue = round(blur_avg_blue);
                image[i][j].rgbtGreen = round(blur_avg_green);
                image[i][j].rgbtRed = round(blur_avg_red);
            }
            else if (i == height - 1)
            {
                float blur_avg_blue = (imageCopy[i][j - 1].rgbtBlue + imageCopy[i][j].rgbtBlue + imageCopy[i][j + 1].rgbtBlue + imageCopy[i - 1][j - 1].rgbtBlue + imageCopy[i - 1][j].rgbtBlue + imageCopy[i - 1][j + 1].rgbtBlue) / (float) 6;
                float blur_avg_green = (imageCopy[i][j - 1].rgbtGreen + imageCopy[i][j].rgbtGreen + imageCopy[i][j + 1].rgbtGreen + imageCopy[i - 1][j - 1].rgbtGreen + imageCopy[i - 1][j].rgbtGreen + imageCopy[i - 1][j + 1].rgbtGreen) / (float) 6;
                float blur_avg_red = (imageCopy[i][j - 1].rgbtRed + imageCopy[i][j].rgbtRed + imageCopy[i][j + 1].rgbtRed + imageCopy[i - 1][j - 1].rgbtRed + imageCopy[i - 1][j].rgbtRed + imageCopy[i - 1][j + 1].rgbtRed) / (float) 6;

                image[i][j].rgbtBlue = round(blur_avg_blue);
                image[i][j].rgbtGreen = round(blur_avg_green);
                image[i][j].rgbtRed = round(blur_avg_red);
            }
            // All others
            else
            {
                float blur_avg_blue = (imageCopy[i][j - 1].rgbtBlue + imageCopy[i][j].rgbtBlue + imageCopy[i][j + 1].rgbtBlue + imageCopy[i - 1][j - 1].rgbtBlue + imageCopy[i - 1][j].rgbtBlue + imageCopy[i - 1][j + 1].rgbtBlue + imageCopy[i + 1][j - 1].rgbtBlue + imageCopy[i + 1][j].rgbtBlue + imageCopy[i + 1][j + 1].rgbtBlue) / (float) 9;
                float blur_avg_green = (imageCopy[i][j - 1].rgbtGreen + imageCopy[i][j].rgbtGreen + imageCopy[i][j + 1].rgbtGreen + imageCopy[i - 1][j - 1].rgbtGreen + imageCopy[i - 1][j].rgbtGreen + imageCopy[i - 1][j + 1].rgbtGreen + imageCopy[i + 1][j - 1].rgbtGreen + imageCopy[i + 1][j].rgbtGreen + imageCopy[i + 1][j + 1].rgbtGreen) / (float) 9;
                float blur_avg_red = (imageCopy[i][j - 1].rgbtRed + imageCopy[i][j].rgbtRed + imageCopy[i][j + 1].rgbtRed + imageCopy[i - 1][j - 1].rgbtRed + imageCopy[i - 1][j].rgbtRed + imageCopy[i - 1][j + 1].rgbtRed + imageCopy[i + 1][j - 1].rgbtRed + imageCopy[i+1][j].rgbtRed + imageCopy[i + 1][j + 1].rgbtRed) / (float) 9;

                image[i][j].rgbtBlue = round(blur_avg_blue);
                image[i][j].rgbtGreen = round(blur_avg_green);
                image[i][j].rgbtRed = round(blur_avg_red);
            }

        }
    }
    return;
}
