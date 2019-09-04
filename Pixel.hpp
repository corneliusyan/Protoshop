#ifndef PIXEL_HPP
#define PIXEL_HPP
enum PixelType
{
    BINARY,
    GRAYSCALE,
    COLOR
};
class Pixel
{
public:
    PixelType type;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char intensity;

    // Default Pixel constructor return a black color pixel
    Pixel();

    Pixel(PixelType pixelType, unsigned char red, unsigned char green, unsigned char blue, unsigned char intens);

    void printPixel();
};

#endif