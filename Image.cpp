#include "Image.hpp"
#include <iostream>
#include <stdio.h>
#include <cstdlib>
using namespace std;

Image::Image()
{
    type = COLOR;
    height = DEFAULT_HEIGHT;
    width = DEFAULT_WIDTH;
    resetImage();
}

Image::Image(ImageType imageType, int imageHeight, int imageWidth)
{
    type = imageType;
    height = imageHeight;
    width = imageWidth;

    resetImage();
}

void Image::resetImage()
{
    switch (type)
    {
    case BINARY:
        in = (unsigned char **)malloc(height * sizeof(unsigned char *));
        for (int i = 0; i < height; i++)
        {
            in[i] = (unsigned char *)malloc(width * sizeof(unsigned char));
            for (int j = 0; j < width; j++)
            {
                in[i][j] = 0;
            }
        }
        break;
    case GRAYSCALE:
        in = (unsigned char **)malloc(height * sizeof(unsigned char *));
        for (int i = 0; i < height; i++)
        {
            in[i] = (unsigned char *)malloc(width * sizeof(unsigned char));
            for (int j = 0; j < width; j++)
            {
                in[i][j] = 0;
            }
        }
        break;
    default:
        r = (unsigned char **)malloc(height * sizeof(unsigned char *));
        g = (unsigned char **)malloc(height * sizeof(unsigned char *));
        b = (unsigned char **)malloc(height * sizeof(unsigned char *));
        for (int i = 0; i < height; i++)
        {
            r[i] = (unsigned char *)malloc(width * sizeof(unsigned char));
            g[i] = (unsigned char *)malloc(width * sizeof(unsigned char));
            b[i] = (unsigned char *)malloc(width * sizeof(unsigned char));
            for (int j = 0; j < width; j++)
            {
                r[i][j] = 0;
                g[i][j] = 0;
                b[i][j] = 0;
            }
        }
    }
}

void Image::SetPixel(int x, int y, unsigned char red, unsigned char green, unsigned char blue, unsigned char intensity)
{
    switch (type)
    {
    case BINARY:
        in[x][y] = intensity;
        break;
    case GRAYSCALE:
        in[x][y] = intensity;
        break;
    default:
        r[x][y] = red;
        g[x][y] = green;
        b[x][y] = blue;
    }
}

void Image::PrintImage()
{
    switch (type)
    {
    case BINARY:
        printf("Image Type: BINARY\n");
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                printf("%u ", in[i][j]);
            }
            printf("\n");
        }
        break;
    case GRAYSCALE:
        printf("Image Type: GRAYSCALE\n");
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                printf("%u ", in[i][j]);
            }
            printf("\n");
        }
        break;
    default:
        printf("Image Type: COLOR\n");
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                printf("%u,%u,%u ", r[i][j], g[i][j], b[i][j]);
            }
            printf("\n");
        }
    }
}