#include <iostream>

#include "Pixel.hpp"
using namespace std;

int main()
{
    Pixel binary(BINARY, 0, 0, 0, 1);
    Pixel grayscale(GRAYSCALE, 0, 0, 0, 100);
    Pixel color(COLOR, 220, 170, 120, 20);

    binary.printPixel();
    grayscale.printPixel();
    color.printPixel();

    return 0;
}