#include <iostream>

#include "ui/imageviewer.hpp"

#include <QApplication>
#include <QCommandLineParser>

// #include "image/image.hpp"
// #include "image/exception.hpp"
// #include "adjustment/adjustment.hpp"

int main(int argc, char *argv[]) {

//  try {
//    // Image* img_lena = Image::load("./res/lena.bmp");
//    // Image* img_baboon = Image::load("./res/lena.bmp");
//    // Image* img = *img_lena + *img_baboon;
//    // img->show();
//    Image* img = Image::load("./res/lena.bmp");
//    // AdjustmentTranslate::apply(img, 30, 25);
//    AdjustmentRotate::rotate90CCW(img);
//    img->show();
//    // Image* img2 = *img + *img;
//    // img2->show();
//  } catch (ImageLoadException e) {
//    std::cout << e.get_message() << std::endl;
//  }

  QApplication app(argc, argv);
  QGuiApplication::setApplicationDisplayName(ImageViewer::tr("Image Viewer"));
  QCommandLineParser commandLineParser;
  commandLineParser.addHelpOption();
  commandLineParser.addPositionalArgument(ImageViewer::tr("[file]"), ImageViewer::tr("Image file to open."));
  commandLineParser.process(QCoreApplication::arguments());
  ImageViewer imageViewer;
  if (!commandLineParser.positionalArguments().isEmpty()
      && !imageViewer.loadFile(commandLineParser.positionalArguments().front())) {
      return -1;
  }
  imageViewer.show();
  return app.exec();
}
