#include "Pixel.hpp"
#include <iostream>
#include <stdio.h>
using namespace std;

Pixel::Pixel()
{
    type = COLOR;
    r = 0;
    g = 0;
    b = 0;
    intensity = 0;
}

Pixel::Pixel(PixelType pixelType, unsigned char red, unsigned char green, unsigned char blue, unsigned char intens)
{
    type = pixelType;
    r = red;
    g = green;
    b = blue;
    intensity = intens;
}

void Pixel::printPixel()
{
    string pixelType;
    switch (type)
    {
    case BINARY:
        pixelType = "BINARY";
        break;
    case GRAYSCALE:
        pixelType = "GRAYSCALE";
        break;
    default:
        pixelType = "COLOR";
    }

    printf("%s: r %u, g %u, b %u, i %u\n", pixelType.c_str(), r, g, b, intensity);
}