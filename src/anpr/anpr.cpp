#include <iostream>
#include "../image/image.hpp"
#include "./auto_threshold.hpp"
#include "./corner_warp.hpp"
#include "./number_recognition.hpp"
#include "./plate_detection.hpp"
#include "./t_corner.hpp"

std::string ANPR(Image* img) {
  t_corner corner = plateDetection(img);
  Image* wrappedImage = warpByCorner(img, corner);
  BWImage* thresholdImage = autoThreshold(wrappedImage);
  std::string result =  numberRecognition(wrappedImage)
  delete wrappedImage;
  delete thresholdImage;
  return result;
}
