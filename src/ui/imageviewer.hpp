#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QMainWindow>
#include <QImage>
#ifndef QT_NO_PRINTER
  #include <QPrinter>
#endif

#include "src/image/image.hpp"
#include "src/image/exception.hpp"
#include "src/adjustment/adjustment.hpp"
#include "src/filter/filter.hpp"
#include "src/frequency/fourier.hpp"
#include "src/anpr/anpr.hpp"
#include <iostream>

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
QT_END_NAMESPACE

class ImageViewer : public QMainWindow
{
  Q_OBJECT

public:
  ImageViewer();
  bool loadFile(const QString &);
  void setImage(const QImage &newImage);
  void showMessage();

private slots:
  void open();
  void print();

  void imageAdd();
  void imageMultiply();
  void imageAnd();
  void imageOr();
  void loadSecondFile(int operation);
  bool imageOperate(const QString &, int operation);

  void scalarAdd();
  void scalarSubstract();
  void scalarMultiply();
  void scalarDivide();
  void scalarNot();
  void scalarOperate(int operation, char *hint);
  int scalarDialog(int operation, char *hint);

  void fourierTransform();
  void inverseFourierTransform();

  void inverse();
  void grayScale();
  void brighten();
  void unbrighten();
  void rotate90CW();
  void rotate90CCW();
  void translate();
  void flipHorizontal();
  void flipVertical();
  void zoom2In();
  void zoom2Out();
  void histogramEqualize();
  void histogramSpecification();

  void brightenScale();
  void contrastStretch();
  void log();
  void inverseLog();
  void power();
  void graySlicing();
  void bitSlicing();
  void binarize();
  void binarizeAverage();

  void showHistogramRed();
  void showHistogramGreen();
  void showHistogramBlue();
  void showNormalizedHistogramRed();
  void showNormalizedHistogramGreen();
  void showNormalizedHistogramBlue();
  void showHistogram(Qt::GlobalColor colorCode, bool isNormalized);

  void copy();
  void paste();
  void zoomIn();
  void zoomOut();
  void normalSize();
  void fitToWindow();

  void filterGeneral(KernelType kernelType);
  void filterAverage();
  void filterGaussian();
  void filterMedian();
  void filterMax();
  void filterMin();
  void filterHighA();
  void filterHighB();
  void filterHighC();
  void filterHighD();
  void filterHighE();
  void filterHighF();
  void filterUnsharp();
  void filterHighboost();

  void edgeDetectionGradientX();
  void edgeDetectionGradientY();
  void edgeDetection2ndDeriv();
  void edgeDetectionLaplace();
  void edgeDetectionLoG();
  void edgeDetectionSobelX();
  void edgeDetectionSobelY();
  void edgeDetectionPrewittX();
  void edgeDetectionPrewittY();
  void edgeDetectionRoberts1();
  void edgeDetectionRoberts2();
  void edgeDetectionCanny();

  void sandboxNumberRecognition();
  void thinning();

  void about();

private:
  void createActions();
  void createMenus();
  void updateActions();
  bool saveFile();
  void scaleImage(double factor);
  void adjustScrollBar(QScrollBar *scrollBar, double factor);

  QImage image;
  Image* img;
  QString filename;
  QLabel *imageLabel;
  QScrollArea *scrollArea;
  double scaleFactor;

#ifndef QT_NO_PRINTER
  QPrinter printer;
#endif

  QAction *fitToWindowAct;
  std::vector<QAction*> imageActions;
  std::vector<QAction*> unfitToWindowActions;
};

#endif
