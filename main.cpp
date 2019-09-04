#include <iostream>

#include "Image.hpp"
using namespace std;

int main()
{
    printf("aaaaaaaaa");
    Image binary(BINARY, 5, 5);
    printf("bbbb");
    Image grayscale(GRAYSCALE, 5, 5);
    printf("cccc");
    Image color(COLOR, 5, 5);

    printf("adsfasdfasdf");
    binary.SetPixel(2, 2, 0, 0, 0, 1);
    grayscale.SetPixel(2, 2, 0, 0, 0, 255);
    color.SetPixel(2, 2, 255, 128, 0, 0);

    binary.PrintImage();
    grayscale.PrintImage();
    color.PrintImage();

    return 0;
}