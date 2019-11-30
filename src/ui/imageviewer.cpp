#include <QtWidgets>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
  #include <QPrintDialog>
#endif
#endif

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

#include "imageviewer.hpp"

#include <iostream>
#include <math.h>

ImageViewer::ImageViewer()
 : imageLabel(new QLabel)
 , scrollArea(new QScrollArea)
 , scaleFactor(1)
{
  imageLabel->setBackgroundRole(QPalette::Base);
  imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  imageLabel->setScaledContents(true);

  scrollArea->setBackgroundRole(QPalette::Dark);
  scrollArea->setWidget(imageLabel);
  scrollArea->setVisible(false);
  setCentralWidget(scrollArea);

  createActions();

  resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
}

bool ImageViewer::loadFile(const QString &fileName) {

  filename = fileName;
  std::string rawFileName = fileName.toStdString();

  try {
    img = Image::load(rawFileName);
  } catch (ImageLoadException e) {
    std::cout << e.get_message() << std::endl;
    return false;
  }

  const QImage newImage = img->getQImage();
  if (newImage.isNull()) {
    QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                             tr("Cannot load %1")
                             .arg(QDir::toNativeSeparators(fileName)));
    return false;
  }

  setImage(newImage);
  setWindowFilePath(fileName);
  showMessage();
  return true;
}

void ImageViewer::setImage(const QImage &newImage) {
  image = newImage;
  imageLabel->setPixmap(QPixmap::fromImage(image));
  scaleFactor = 1.0;
  scrollArea->setVisible(true);
  updateActions();

  if (!fitToWindowAct->isChecked())
    imageLabel->adjustSize();
}

bool ImageViewer::saveFile() {
  QImageWriter writer(filename);

  if (!writer.write(image)) {
    QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                       tr("Cannot write %1: %2")
                       .arg(QDir::toNativeSeparators(filename)), writer.errorString());
    return false;
  }
  const QString message = tr("Wrote \"%1\"").arg(QDir::toNativeSeparators(filename));
  statusBar()->showMessage(message);
  return true;
}

static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode) {
  const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
  dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
}

void ImageViewer::open()
{
  QFileDialog dialog(this, tr("Open File"));
  initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

  while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}
}

void ImageViewer::print() {
  Q_ASSERT(imageLabel->pixmap());
#if QT_CONFIG(printdialog)
  QPrintDialog dialog(&printer, this);
  if (dialog.exec()) {
    QPainter painter(&printer);
    QRect rect = painter.viewport();
    QSize size = imageLabel->pixmap()->size();
    size.scale(rect.size(), Qt::KeepAspectRatio);
    painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
    painter.setWindow(imageLabel->pixmap()->rect());
    painter.drawPixmap(0, 0, *imageLabel->pixmap());
  }
#endif
}

void ImageViewer::copy() {
#ifndef QT_NO_CLIPBOARD
  QGuiApplication::clipboard()->setImage(image);
#endif // !QT_NO_CLIPBOARD
}

#ifndef QT_NO_CLIPBOARD
static QImage clipboardImage() {
  if (const QMimeData *mimeData = QGuiApplication::clipboard()->mimeData()) {
    if (mimeData->hasImage()) {
      const QImage image = qvariant_cast<QImage>(mimeData->imageData());
      if (!image.isNull())
          return image;
    }
  }
  return QImage();
}
#endif // !QT_NO_CLIPBOARD

void ImageViewer::paste() {
#ifndef QT_NO_CLIPBOARD
  const QImage newImage = clipboardImage();
  if (newImage.isNull()) {
    statusBar()->showMessage(tr("No image in clipboard"));
  } else {
    setImage(newImage);
    setWindowFilePath(QString());
    const QString message = tr("Obtained image from clipboard, %1x%2, Depth: %3")
        .arg(newImage.width()).arg(newImage.height()).arg(newImage.depth());
    statusBar()->showMessage(message);
  }
#endif // !QT_NO_CLIPBOARD
}

void ImageViewer::showMessage() {

  int height = image.height();
  int width = image.width();
  int dim = height * width;

  double red = 0;
  double green = 0;
  double blue = 0;

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      QColor qc = image.pixelColor(i,j);
      red += qc.red();
      green += qc.green();
      blue += qc.blue();
    }
  }

  double r_mean = red / dim;
  double g_mean = green / dim;
  double b_mean = blue / dim;

  double red_var = 0;
  double green_var = 0;
  double blue_var = 0;

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      QColor qc = image.pixelColor(i,j);
      red_var += pow((qc.red() - r_mean),2);
      green_var += pow((qc.green() - g_mean),2);
      blue_var += pow((qc.blue() - b_mean),2);
    }
  }

  red_var /= dim;
  green_var /= dim;
  blue_var /= dim;

  double red_std = sqrt(red_var);
  double green_std = sqrt(green_var);
  double blue_std = sqrt(blue_var);

  const QString message = tr("Opened \"%1\", %2x%3, Depth: %4, Mean: R:%5 G:%6 B:%7, Var: R:%8 G:%9 B:%10, Std: R:%11 G:%12 B:%13")
      .arg(QDir::toNativeSeparators(filename)).arg(image.width()).arg(image.height()).arg(image.depth())
      .arg(r_mean).arg(g_mean).arg(b_mean)
      .arg(red_var).arg(green_var).arg(blue_var)
      .arg(red_std).arg(green_std).arg(blue_std);
  statusBar()->showMessage(message);
}

int ImageViewer::scalarDialog(int operation, char *hint) {
  bool ok;
  int i = QInputDialog::getInt(this, tr(hint),
                                tr("Scalar Value:"), 0, -255, 255, 1, &ok);
  if (ok)
    return i;
  else {
    if (operation < 2)
      return 0;
    return 1;
  }
}

void ImageViewer::scalarAdd() {
  scalarOperate(0, "Scalar Add Operation");
}

void ImageViewer::scalarSubstract() {
  scalarOperate(1, "Scalar Substract Operation");
}

void ImageViewer::scalarMultiply() {
  scalarOperate(2, "Scalar Multiply Operation");
}

void ImageViewer::scalarDivide() {
  scalarOperate(3, "Scalar Divide Operation");
}

void ImageViewer::scalarNot() {
  scalarOperate(4, "Scalar Not Operation");
}

void ImageViewer::scalarOperate(int operation, char *hint) {
  int value = 0;
  if (operation != 4)
    value = scalarDialog(operation, hint);

  if (operation == 0) {
    img = *img + value;
  } else if (operation == 1) {
    img = *img - value;
  } else if (operation == 2) {
    img = *img * value;
  } else if (operation == 3) {
    img  = *img / value;
  } else if (operation == 4) {
    img = !(*img);
  }

  const QImage newImage = img->getQImage();
  setImage(newImage);
  showMessage();
}

void ImageViewer::imageAdd() {
  loadSecondFile(0);
}

void ImageViewer::imageMultiply() {
  loadSecondFile(1);
}

void ImageViewer::imageAnd() {
  loadSecondFile(2);
}

void ImageViewer::imageOr() {
  loadSecondFile(3);
}

void ImageViewer::loadSecondFile(int operation) {
  QFileDialog dialog(this, tr("Open File"));
  initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);
  while (dialog.exec() == QDialog::Accepted && !imageOperate(dialog.selectedFiles().first(), operation)) {}
}

bool ImageViewer::imageOperate(const QString &fileName, int operation) {

  Image *secondImg;
  std::string rawFileName = fileName.toStdString();

  try {
    secondImg = Image::load(rawFileName);
  } catch (ImageLoadException e) {
    std::cout << e.get_message() << std::endl;
    return false;
  }

  if (operation == 0) {
    // operator+
    Image *temp = *img + *secondImg;
    img = temp;
  } else if (operation == 1) {
    // operator*
    Image *temp = *img * *secondImg;
    img = temp;
  } else if (operation == 2) {
    // operator&
    Image *temp = *img & *secondImg;
    img = temp;
  } else if (operation == 3) {
    // operator|
    Image *temp = *img | *secondImg;
    img = temp;
  } else {
    return false;
  }

  const QImage newImage = img->getQImage();
  if (newImage.isNull()) {
    return false;
  }

  setImage(newImage);
  showMessage();
  return true;
}

void ImageViewer::inverse() {
  AdjustmentInverse::apply(img);
  const QImage newImage = img->getQImage();
  setImage(newImage);
  showMessage();
}

void ImageViewer::grayScale() {
  AdjustmentGrayscale::apply(img);
  const QImage newImage = img->getQImage();
  setImage(newImage);
  showMessage();
}

void ImageViewer::brighten() {
  bool ok;
  int val = QInputDialog::getInt(this, tr("input value"),
                                tr("Scalar Value:"), 0, -255, 255, 1, &ok);
  if (ok) {
    AdjustmentBrighten::apply(img, val);
    const QImage newImage = img->getQImage();
    setImage(newImage);
    showMessage();
  }
}

void ImageViewer::unbrighten() {
  bool ok;
  int val = QInputDialog::getInt(this, tr("input value"),
                                tr("Scalar Value:"), 0, -255, 255, 1, &ok);
  if (ok) {
    AdjustmentBrighten::apply(img,-val);
    const QImage newImage = img->getQImage();
    setImage(newImage);
    showMessage();
  }
}

void ImageViewer::fourierTransform() {
  Fourier::transform(img);
  const QImage newImage = img->getQImage();
  setImage(newImage);
  showMessage();
}

void ImageViewer::inverseFourierTransform() {
  Fourier::inverse(img);
  const QImage newImage = img->getQImage();
  setImage(newImage);
  showMessage();
}

void ImageViewer::rotate90CW() {
  AdjustmentRotate::rotate90CW(img);
  const QImage newImage = img->getQImage();
  setImage(newImage);
  showMessage();
}

void ImageViewer::rotate90CCW() {
  AdjustmentRotate::rotate90CCW(img);
  const QImage newImage = img->getQImage();
  setImage(newImage);
  showMessage();
}

void ImageViewer::translate() {
  bool ok_x;
  int val_x = QInputDialog::getInt(this, tr("Input Value"),
                                tr("X Value:"), 0, -255, 255, 1, &ok_x);
  if (ok_x) {
    bool ok_y;
    int val_y = QInputDialog::getInt(this, tr("Input Value"),
                                  tr("Y Value:"), 0, -255, 255, 1, &ok_y);
    if (ok_y) {
      AdjustmentTranslate::apply(img, val_x, val_y);
      const QImage newImage = img->getQImage();
      setImage(newImage);
      showMessage();
    }
  }
}

void ImageViewer::flipHorizontal() {
  AdjustmentFlip::horizontalFlip(img);
  const QImage newImage = img->getQImage();
  setImage(newImage);
  showMessage();
}

void ImageViewer::flipVertical() {
  AdjustmentFlip::verticalFlip(img);
  const QImage newImage = img->getQImage();
  setImage(newImage);
  showMessage();
}

void ImageViewer::zoom2In() {
  AdjustmentZoom::zoomIn(img);
  const QImage newImage = img->getQImage();
  setImage(newImage);
  showMessage();
}

void ImageViewer::zoom2Out() {
  AdjustmentZoom::zoomOut(img);
  const QImage newImage = img->getQImage();
  setImage(newImage);
  showMessage();
}

void ImageViewer::histogramEqualize() {
  AdjustmentHistogramEqualize::apply(img);
  const QImage newImage = img->getQImage();
  setImage(newImage);
  showMessage();
}

void ImageViewer::histogramSpecification() {
  QFileDialog dialog(this, tr("Open File"));
  initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

  while (dialog.exec() == QDialog::Accepted) {}
  const QString qfilename = dialog.selectedFiles().first();
  std::string filename = qfilename.toStdString();

  Image* newImg;
  try {
    newImg = Image::load(filename);
  } catch (ImageLoadException e) {
    std::cerr << e.get_message() << std::endl;
    return;
  }

  const QImage newQImg = newImg->getQImage();
  if (newQImg.isNull()) {
    QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                             tr("Cannot load %1")
                             .arg(QDir::toNativeSeparators(qfilename)));
  }

  AdjustmentHistogramSpecification::apply(img, newImg);
  const QImage newImage = img->getQImage();
  setImage(newImage);
  showMessage();

  delete newImg;
}

void ImageViewer::brightenScale() {
  bool ok;
  double val = QInputDialog::getDouble(this, tr("input value"),
                                tr("Scalar Value:"), 0, -255, 255, 1, &ok);
  if (ok) {
    AdjustmentEnhancement::brighten(img, val);
    const QImage newImage = img->getQImage();
    setImage(newImage);
    showMessage();
  }
}

void ImageViewer::contrastStretch() {
  bool ok;
  int rMin = QInputDialog::getInt(this, tr("input value"),
                                tr("rMin:"), 0, -255, 255, 1, &ok);
  int rMax = QInputDialog::getInt(this, tr("input value"),
                                tr("rMax:"), 0, -255, 255, 1, &ok);
  if (ok) {
    AdjustmentEnhancement::contrastStretch(img, rMin, rMax);
    const QImage newImage = img->getQImage();
    setImage(newImage);
    showMessage();
  }
}

void ImageViewer::log() {
  bool ok;
  double val = QInputDialog::getDouble(this, tr("input value"),
                                tr("Scalar Value:"), 0, -255, 255, 1, &ok);
  if (ok) {
    AdjustmentEnhancement::logTransform(img, val);
    const QImage newImage = img->getQImage();
    setImage(newImage);
    showMessage();
  }
}

void ImageViewer::inverseLog() {
  bool ok;
  double val = QInputDialog::getDouble(this, tr("input value"),
                                tr("Scalar Value:"), 0, -255, 255, 1, &ok);
  if (ok) {
    AdjustmentEnhancement::inverseLog(img, val);
    const QImage newImage = img->getQImage();
    setImage(newImage);
    showMessage();
  }
}

void ImageViewer::power() {
  bool ok;
  double val = QInputDialog::getDouble(this, tr("input value"),
                                tr("Scalar Value:"), 0, -255, 255, 1, &ok);
  if (ok) {
    AdjustmentEnhancement::power(img, val);
    const QImage newImage = img->getQImage();
    setImage(newImage);
    showMessage();
  }
}

void ImageViewer::graySlicing() {
  bool ok;
  int rMin = QInputDialog::getInt(this, tr("input value"),
                                tr("rMin:"), 0, -255, 255, 1, &ok);
  int rMax = QInputDialog::getInt(this, tr("input value"),
                                tr("rMax:"), 0, -255, 255, 1, &ok);
  if (ok) {
    AdjustmentEnhancement::graySlicing(img, rMin, rMax);
    const QImage newImage = img->getQImage();
    setImage(newImage);
    showMessage();
  }
}

void ImageViewer::bitSlicing() {
  bool ok;
  int val = QInputDialog::getInt(this, tr("input value"),
                                tr("Bit-plane:"), 0, -255, 255, 1, &ok);
  if (ok) {
    AdjustmentEnhancement::bitSlicing(img, val);
    const QImage newImage = img->getQImage();
    setImage(newImage);
    showMessage();
  }
}

void ImageViewer::showHistogramRed() {
  showHistogram(Qt::red, false);
}

void ImageViewer::showHistogramGreen() {
  showHistogram(Qt::green, false);
}

void ImageViewer::showHistogramBlue() {
  showHistogram(Qt::blue, false);
}

void ImageViewer::showNormalizedHistogramRed() {
  showHistogram(Qt::red, true);
}

void ImageViewer::showNormalizedHistogramGreen() {
  showHistogram(Qt::green, true);
}

void ImageViewer::showNormalizedHistogramBlue() {
  showHistogram(Qt::blue, true);
}

void ImageViewer::showHistogram(Qt::GlobalColor colorCode, bool isNormalized) {
  double hist[256] = {0};
  int height = image.height();
  int width = image.width();
  double max = 0;

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      int value;
      QColor qc = image.pixelColor(i,j);

      if (colorCode == Qt::red) value = qc.red();
      else if (colorCode == Qt::green) value = qc.green();
      else value = qc.blue();

      hist[value]++;
      if (hist[value] > max) max = hist[value];
    }
  }

  if (isNormalized) {
    max = 0;
    for (int i = 0; i < 256; i++) {
      hist[i] /= (width * height);
      if (hist[i] > max) max = hist[i];
    }
  }

  QStringList categories;
  QtCharts::QBarSet *set0 = new QtCharts::QBarSet("Histogram");
  set0->setColor(colorCode);

  for (int i = 0; i < 256; i++) {
    *set0 << hist[i];
    categories << QString::number(i);
  }

  QtCharts::QBarSeries *series = new QtCharts::QBarSeries();
  series->append(set0);

  QtCharts::QChart *chart = new QtCharts::QChart();
  chart->addSeries(series);
  chart->setTitle("Histogram");

  QtCharts::QBarCategoryAxis *axisX = new QtCharts::QBarCategoryAxis();
  axisX->append(categories);
  chart->addAxis(axisX, Qt::AlignBottom);
  series->attachAxis(axisX);

  QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
  axisY->setRange(0,max);
  chart->addAxis(axisY, Qt::AlignLeft);
  series->attachAxis(axisY);

  chart->legend()->setVisible(true);
  chart->legend()->setAlignment(Qt::AlignBottom);

  QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  chartView->resize(1000,500);
  chartView->show();
}

void ImageViewer::zoomIn() {
  scaleImage(1.25);
}

void ImageViewer::zoomOut() {
  scaleImage(0.8);
}

void ImageViewer::normalSize() {
  imageLabel->adjustSize();
  scaleFactor = 1.0;
}

void ImageViewer::fitToWindow() {
  bool fitToWindow = fitToWindowAct->isChecked();
  scrollArea->setWidgetResizable(fitToWindow);
  if (!fitToWindow)
    normalSize();
  updateActions();
}

void ImageViewer::filterGeneral(KernelType kernelType) {
  Filter* filter = new Filter(kernelType);
  filter->apply(img);
  const QImage newImage = img->getQImage();
  setImage(newImage);
  showMessage();
}

void ImageViewer::filterAverage() { this->filterGeneral(AVERAGE); }
void ImageViewer::filterGaussian() { this->filterGeneral(GAUSSIAN3); }
void ImageViewer::filterMedian() { this->filterGeneral(MEDIAN); }
void ImageViewer::filterMax() { this->filterGeneral(MAX); }
void ImageViewer::filterMin() { this->filterGeneral(MIN); }
void ImageViewer::filterHighA() { this->filterGeneral(HIGH_A); }
void ImageViewer::filterHighB() { this->filterGeneral(HIGH_B); }
void ImageViewer::filterHighC() { this->filterGeneral(HIGH_C); }
void ImageViewer::filterHighD() { this->filterGeneral(HIGH_D); }
void ImageViewer::filterHighE() { this->filterGeneral(HIGH_E); }
void ImageViewer::filterHighF() { this->filterGeneral(HIGH_F); }
void ImageViewer::filterUnsharp() { this->filterGeneral(UNSHARP); }
void ImageViewer::filterHighboost() { this->filterGeneral(HIGHBOOST); }

void ImageViewer::edgeDetectionGradientX() { this->filterGeneral(GRADIENT_X); }
void ImageViewer::edgeDetectionGradientY() { this->filterGeneral(GRADIENT_Y); }
void ImageViewer::edgeDetection2ndDeriv() { this->filterGeneral(DERIV2); }
void ImageViewer::edgeDetectionLaplace() { this->filterGeneral(LAPLACE); }
void ImageViewer::edgeDetectionLoG() { this->filterGeneral(LOG); }
void ImageViewer::edgeDetectionSobelX() { this->filterGeneral(SOBEL_X); }
void ImageViewer::edgeDetectionSobelY() { this->filterGeneral(SOBEL_Y); }
void ImageViewer::edgeDetectionPrewittX() { this->filterGeneral(PREWITT_X); }
void ImageViewer::edgeDetectionPrewittY() { this->filterGeneral(PREWITT_Y); }
void ImageViewer::edgeDetectionRoberts1() { this->filterGeneral(ROBERTS_1); }
void ImageViewer::edgeDetectionRoberts2() { this->filterGeneral(ROBERTS_2); }
void ImageViewer::edgeDetectionCanny() { this->filterGeneral(CANNY); }

void ImageViewer::sandboxNumberRecognition() {
  BWImage* bwImage = dynamic_cast<BWImage*>(this->img);
  std::string result = numberRecognition(bwImage);
  QMessageBox::information(this, QGuiApplication::applicationDisplayName(), tr(result.c_str()));
  delete bwImage;
}

void ImageViewer::thinning() {
  AdjustmentThinning::apply(this->img);
  const QImage newImage = this->img->getQImage();
  setImage(newImage);
  showMessage();
}

void ImageViewer::about() {
  QMessageBox::about(this, tr("About Protoshop"),
          tr("<p>Protoshop by Yonas Adiel Wiguna, Cornelius Yan M., and Hafizh Budiman</p>"));
}

void ImageViewer::createActions() {
  QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

  QAction* openAct = fileMenu->addAction(tr("&Open..."), this, &ImageViewer::open);
  openAct->setShortcut(QKeySequence::Open);
  imageActions.push_back(fileMenu->addAction(tr("&Save Image"), this, &ImageViewer::saveFile));
  imageActions.back()->setShortcut(QKeySequence::Save);
  imageActions.push_back(fileMenu->addAction(tr("&Print..."), this, &ImageViewer::print));
  imageActions.back()->setShortcut(QKeySequence::Print);

  fileMenu->addSeparator();

  QAction *exitAct = fileMenu->addAction(tr("E&xit"), this, &QWidget::close);
  exitAct->setShortcut(tr("Ctrl+Q"));

  QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));

  imageActions.push_back(editMenu->addAction(tr("&Copy"), this, &ImageViewer::copy));
  imageActions.back()->setShortcut(QKeySequence::Copy);
  imageActions.push_back(editMenu->addAction(tr("&Paste"), this, &ImageViewer::paste));
  imageActions.back()->setShortcut(QKeySequence::Paste);

  QMenu *imageOperator = editMenu->addMenu(tr("&Image Operator"));
  imageActions.push_back(imageOperator->addAction(tr("&Add"), this, &ImageViewer::imageAdd));
  imageActions.push_back(imageOperator->addAction(tr("&Multiply"), this, &ImageViewer::imageMultiply));
  imageActions.push_back(imageOperator->addAction(tr("&And"), this, &ImageViewer::imageAnd));
  imageActions.push_back(imageOperator->addAction(tr("&Or"), this, &ImageViewer::imageOr));

  QMenu *scalarOperator = editMenu->addMenu(tr("&Scalar Operator"));
  imageActions.push_back(scalarOperator->addAction(tr("&Add"), this, &ImageViewer::scalarAdd));
  imageActions.push_back(scalarOperator->addAction(tr("&Substract"), this, &ImageViewer::scalarSubstract));
  imageActions.push_back(scalarOperator->addAction(tr("&Multiply"), this, &ImageViewer::scalarMultiply));
  imageActions.push_back(scalarOperator->addAction(tr("&Divide"), this, &ImageViewer::scalarDivide));
  imageActions.push_back(scalarOperator->addAction(tr("&Not"), this, &ImageViewer::scalarNot));

  imageActions.push_back(editMenu->addAction(tr("&Inverse"), this, &ImageViewer::inverse));
  imageActions.push_back(editMenu->addAction(tr("&Gray Scale"), this, &ImageViewer::grayScale));
  imageActions.push_back(editMenu->addAction(tr("&Brighten"), this, &ImageViewer::brighten));
  imageActions.push_back(editMenu->addAction(tr("&Unbrighten"), this, &ImageViewer::unbrighten));
  imageActions.push_back(editMenu->addAction(tr("&Rotate 90CW"), this, &ImageViewer::rotate90CW));
  imageActions.push_back(editMenu->addAction(tr("&Rotate 90CCW"), this, &ImageViewer::rotate90CCW));
  imageActions.push_back(editMenu->addAction(tr("&Translate"), this, &ImageViewer::translate));
  imageActions.push_back(editMenu->addAction(tr("&Flip Horizontal"), this, &ImageViewer::flipHorizontal));
  imageActions.push_back(editMenu->addAction(tr("&Flip Vertical"), this, &ImageViewer::flipVertical));
  imageActions.push_back(editMenu->addAction(tr("&Zoom In 2"), this, &ImageViewer::zoom2In));
  imageActions.push_back(editMenu->addAction(tr("&Zoom Out 2"), this, &ImageViewer::zoom2Out));
  imageActions.push_back(editMenu->addAction(tr("&Histogram Equalize"), this, &ImageViewer::histogramEqualize));
  imageActions.push_back(editMenu->addAction(tr("&Histogram Spaceification"), this, &ImageViewer::histogramSpecification));

  imageActions.push_back(editMenu->addAction(tr("&Brighten Scale"), this, &ImageViewer::brightenScale));
  imageActions.push_back(editMenu->addAction(tr("&Contrast Stretch"), this, &ImageViewer::contrastStretch));
  imageActions.push_back(editMenu->addAction(tr("&Log"), this, &ImageViewer::log));
  imageActions.push_back(editMenu->addAction(tr("&Inverse Log"), this, &ImageViewer::inverseLog));
  imageActions.push_back(editMenu->addAction(tr("&Power"), this, &ImageViewer::power));
  imageActions.push_back(editMenu->addAction(tr("&Gray Slicing"), this, &ImageViewer::graySlicing));
  imageActions.push_back(editMenu->addAction(tr("&Bit Slicing"), this, &ImageViewer::bitSlicing));

  imageActions.push_back(editMenu->addAction(tr("&Fourier Transform"), this, &ImageViewer::fourierTransform));
  imageActions.push_back(editMenu->addAction(tr("&Inverse Fourier Transform"), this, &ImageViewer::inverseFourierTransform));

  QMenu *histogramMenu = editMenu->addMenu(tr("&Show Histogram"));
  imageActions.push_back(histogramMenu->addAction(tr("&Red"), this, &ImageViewer::showHistogramRed));
  imageActions.push_back(histogramMenu->addAction(tr("&Green"), this, &ImageViewer::showHistogramGreen));
  imageActions.push_back(histogramMenu->addAction(tr("&Blue"), this, &ImageViewer::showHistogramBlue));

  QMenu *normalizedHistogramMenu = editMenu->addMenu(tr("&Show Normalized Histogram"));

  imageActions.push_back(normalizedHistogramMenu->addAction(tr("&Red"), this, &ImageViewer::showNormalizedHistogramRed));
  imageActions.push_back(normalizedHistogramMenu->addAction(tr("&Green"), this, &ImageViewer::showNormalizedHistogramGreen));
  imageActions.push_back(normalizedHistogramMenu->addAction(tr("&Blue"), this, &ImageViewer::showNormalizedHistogramBlue));

  QMenu *viewMenu = menuBar()->addMenu(tr("&View"));

  unfitToWindowActions.push_back(viewMenu->addAction(tr("Zoom &In (25%)"), this, &ImageViewer::zoomIn));
  unfitToWindowActions.back()->setShortcut(QKeySequence::ZoomIn);
  unfitToWindowActions.push_back(viewMenu->addAction(tr("Zoom &Out (25%)"), this, &ImageViewer::zoomOut));
  unfitToWindowActions.back()->setShortcut(QKeySequence::ZoomOut);
  unfitToWindowActions.push_back(viewMenu->addAction(tr("&Normal Size"), this, &ImageViewer::normalSize));
  unfitToWindowActions.back()->setShortcut(tr("Ctrl+S"));

  viewMenu->addSeparator();

  fitToWindowAct = viewMenu->addAction(tr("&Fit to Window"), this, &ImageViewer::fitToWindow);
  imageActions.push_back(fitToWindowAct);
  imageActions.back()->setCheckable(true);
  imageActions.back()->setShortcut(tr("Ctrl+F"));

  QMenu *filterMenu = menuBar()->addMenu(tr("Fil&ter"));
  QMenu *lowPassFilterMenu = filterMenu->addMenu(tr("&Low Pass"));
  QMenu *highPassFilterMenu = filterMenu->addMenu(tr("&High Pass"));
  QMenu *nonLinearFilterMenu = filterMenu->addMenu(tr("&Non Linear"));

  imageActions.push_back(lowPassFilterMenu->addAction(tr("&Average"), this, &ImageViewer::filterAverage));
  imageActions.push_back(lowPassFilterMenu->addAction(tr("&Gaussian 3"), this, &ImageViewer::filterGaussian));
  imageActions.push_back(highPassFilterMenu->addAction(tr("High &A"), this, &ImageViewer::filterHighA));
  imageActions.push_back(highPassFilterMenu->addAction(tr("High &B"), this, &ImageViewer::filterHighB));
  imageActions.push_back(highPassFilterMenu->addAction(tr("High &C"), this, &ImageViewer::filterHighC));
  imageActions.push_back(highPassFilterMenu->addAction(tr("High &D"), this, &ImageViewer::filterHighD));
  imageActions.push_back(highPassFilterMenu->addAction(tr("High &E"), this, &ImageViewer::filterHighE));
  imageActions.push_back(highPassFilterMenu->addAction(tr("High &F"), this, &ImageViewer::filterHighF));
  imageActions.push_back(nonLinearFilterMenu->addAction(tr("M&edian"), this, &ImageViewer::filterMedian));
  imageActions.push_back(nonLinearFilterMenu->addAction(tr("Ma&x"), this, &ImageViewer::filterMax));
  imageActions.push_back(nonLinearFilterMenu->addAction(tr("Mi&n"), this, &ImageViewer::filterMin));
  imageActions.push_back(filterMenu->addAction(tr("&Unsharp Masking"), this, &ImageViewer::filterUnsharp));
  imageActions.push_back(filterMenu->addAction(tr("&Highboost"), this, &ImageViewer::filterHighboost));

  QMenu *edgeDetectionMenu = menuBar()->addMenu(tr("Edge Detection"));
  imageActions.push_back(edgeDetectionMenu->addAction(tr("Gradient X"), this, &ImageViewer::edgeDetectionGradientX));
  imageActions.push_back(edgeDetectionMenu->addAction(tr("Gradient Y"), this, &ImageViewer::edgeDetectionGradientY));
  imageActions.push_back(edgeDetectionMenu->addAction(tr("2nd Deriv"), this, &ImageViewer::edgeDetection2ndDeriv));
  imageActions.push_back(edgeDetectionMenu->addAction(tr("Laplace"), this, &ImageViewer::edgeDetectionLaplace));
  imageActions.push_back(edgeDetectionMenu->addAction(tr("LoG"), this, &ImageViewer::edgeDetectionLoG));
  imageActions.push_back(edgeDetectionMenu->addAction(tr("Sobel X"), this, &ImageViewer::edgeDetectionSobelX));
  imageActions.push_back(edgeDetectionMenu->addAction(tr("Sobel Y"), this, &ImageViewer::edgeDetectionSobelY));
  imageActions.push_back(edgeDetectionMenu->addAction(tr("Prewitt X"), this, &ImageViewer::edgeDetectionPrewittX));
  imageActions.push_back(edgeDetectionMenu->addAction(tr("Prewitt Y"), this, &ImageViewer::edgeDetectionPrewittY));
  imageActions.push_back(edgeDetectionMenu->addAction(tr("Roberts 1"), this, &ImageViewer::edgeDetectionRoberts1));
  imageActions.push_back(edgeDetectionMenu->addAction(tr("Roberts 2"), this, &ImageViewer::edgeDetectionRoberts2));
  imageActions.push_back(edgeDetectionMenu->addAction(tr("Canny"), this, &ImageViewer::edgeDetectionCanny));

  QMenu *sandboxMenu = menuBar()->addMenu(tr("Sandbox"));
  imageActions.push_back(sandboxMenu->addAction(tr("NumberRecognition"), this, &ImageViewer::sandboxNumberRecognition));
  imageActions.push_back(sandboxMenu->addAction(tr("Thinning"), this, &ImageViewer::thinning));

  QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
  helpMenu->addAction(tr("&About"), this, &ImageViewer::about);

  this->updateActions();
}

void ImageViewer::updateActions() {
  for (auto act : imageActions) { act->setEnabled(!image.isNull()); }
  for (auto act : unfitToWindowActions) { act->setEnabled(!fitToWindowAct->isChecked()); }
}

void ImageViewer::scaleImage(double factor) {
  Q_ASSERT(imageLabel->pixmap());
  scaleFactor *= factor;
  imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

  adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
  adjustScrollBar(scrollArea->verticalScrollBar(), factor);

  if (unfitToWindowActions.size() > 1) {
    unfitToWindowActions[0]->setEnabled(scaleFactor < 3.0); // ZOOM IN
    unfitToWindowActions[1]->setEnabled(scaleFactor > 0.333); // ZOOM OUT
  }
}

void ImageViewer::adjustScrollBar(QScrollBar *scrollBar, double factor) {
  scrollBar->setValue(int(factor * scrollBar->value()
                          + ((factor - 1) * scrollBar->pageStep()/2)));
}
