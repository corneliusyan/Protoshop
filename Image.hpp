#ifndef IMAGE_HPP
#define IMAGE_HPP

#define DEFAULT_HEIGHT 128
#define DEFAULT_WIDTH 128
enum ImageType
{
    BINARY,
    GRAYSCALE,
    COLOR
};

class Image
{
private:
    void resetImage();

public:
    ImageType type;
    int height;
    int width;

    unsigned char **r;
    unsigned char **g;
    unsigned char **b;
    unsigned char **in;

    // Default Image constructor return a DEFAULT_HEIGHT x DEFAULT_WIDTH Black Color Image
    Image();

    Image(ImageType imageType, int imageHeight, int imageWidth);

    void SetPixel(int x, int y, unsigned char red, unsigned char green, unsigned char blue, unsigned char intensity);

    void PrintImage();
};

#endif