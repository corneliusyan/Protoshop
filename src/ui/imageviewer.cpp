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
  printAct->setEnabled(true);
  fitToWindowAct->setEnabled(true);
  updateActions();

  if (!fitToWindowAct->isChecked())
    imageLabel->adjustSize();
}

bool ImageViewer::saveFile(const QString &fileName) {
  QImageWriter writer(fileName);

  if (!writer.write(image)) {
    QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                       tr("Cannot write %1: %2")
                       .arg(QDir::toNativeSeparators(fileName)), writer.errorString());
    return false;
  }
  const QString message = tr("Wrote \"%1\"").arg(QDir::toNativeSeparators(fileName));
  statusBar()->showMessage(message);
  return true;
}

static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode) {
  static bool firstDialog = true;

  if (firstDialog) {
    firstDialog = false;
    const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
  }
}

void ImageViewer::open()
{
  QFileDialog dialog(this, tr("Open File"));
  initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

  while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}
}
//! [1]

void ImageViewer::saveAs()
{
  QFileDialog dialog(this, tr("Save File As"));
  initializeImageFileDialog(dialog, QFileDialog::AcceptSave);

  while (dialog.exec() == QDialog::Accepted && !saveFile(dialog.selectedFiles().first())) {}
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
  bool ok;
  int val = QInputDialog::getInt(this, tr("input value"),
                                tr("Scalar Value:"), 0, -255, 255, 1, &ok);
  if (ok) {
    AdjustmentTranslate::apply(img, val, val);
    const QImage newImage = img->getQImage();
    setImage(newImage);
    showMessage();
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

void ImageViewer::edgeDetectionGradient() { this->filterGeneral(GRADIENT); }
void ImageViewer::edgeDetection2ndDeriv() { this->filterGeneral(DERIV2); }
void ImageViewer::edgeDetectionLaplace() { this->filterGeneral(LAPLACE); }
void ImageViewer::edgeDetectionLoG() { this->filterGeneral(LOG); }
void ImageViewer::edgeDetectionSobel() { this->filterGeneral(SOBEL); }
void ImageViewer::edgeDetectionPrewitt() { this->filterGeneral(PREWITT); }
void ImageViewer::edgeDetectionRoberts() { this->filterGeneral(ROBERTS); }
void ImageViewer::edgeDetectionCanny() { this->filterGeneral(CANNY); }

void ImageViewer::about() {
  QMessageBox::about(this, tr("About Protoshop"),
          tr("<p>Protoshop by Yonas Adiel Wiguna, Cornelius Yan M., and Hafizh Budiman</p>"));
}

void ImageViewer::createActions() {
  QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

  QAction *openAct = fileMenu->addAction(tr("&Open..."), this, &ImageViewer::open);
  openAct->setShortcut(QKeySequence::Open);

  saveAsAct = fileMenu->addAction(tr("&Save As..."), this, &ImageViewer::saveAs);
  saveAsAct->setEnabled(false);

  printAct = fileMenu->addAction(tr("&Print..."), this, &ImageViewer::print);
  printAct->setShortcut(QKeySequence::Print);
  printAct->setEnabled(false);

  fileMenu->addSeparator();

  QAction *exitAct = fileMenu->addAction(tr("E&xit"), this, &QWidget::close);
  exitAct->setShortcut(tr("Ctrl+Q"));

  QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));

  copyAct = editMenu->addAction(tr("&Copy"), this, &ImageViewer::copy);
  copyAct->setShortcut(QKeySequence::Copy);
  copyAct->setEnabled(false);

  QAction *pasteAct = editMenu->addAction(tr("&Paste"), this, &ImageViewer::paste);
  pasteAct->setShortcut(QKeySequence::Paste);

  QMenu *imageOperator = editMenu->addMenu(tr("&Image Operator"));

  imageAddAct = imageOperator->addAction(tr("&Add"), this, &ImageViewer::imageAdd);
  imageAddAct->setEnabled(false);

  imageMultiplyAct = imageOperator->addAction(tr("&Multiply"), this, &ImageViewer::imageMultiply);
  imageMultiplyAct->setEnabled(false);

  imageAndAct = imageOperator->addAction(tr("&And"), this, &ImageViewer::imageAnd);
  imageAndAct->setEnabled(false);

  imageOrAct = imageOperator->addAction(tr("&Or"), this, &ImageViewer::imageOr);
  imageOrAct->setEnabled(false);

  QMenu *scalarOperator = editMenu->addMenu(tr("&Scalar Operator"));

  scalarAddAct = scalarOperator->addAction(tr("&Add"), this, &ImageViewer::scalarAdd);
  scalarAddAct->setEnabled(false);

  scalarSubstractAct = scalarOperator->addAction(tr("&Substract"), this, &ImageViewer::scalarSubstract);
  scalarSubstractAct->setEnabled(false);

  scalarMultiplyAct = scalarOperator->addAction(tr("&Multiply"), this, &ImageViewer::scalarMultiply);
  scalarMultiplyAct->setEnabled(false);

  scalarDivideAct = scalarOperator->addAction(tr("&Divide"), this, &ImageViewer::scalarDivide);
  scalarDivideAct->setEnabled(false);

  scalarNotAct = scalarOperator->addAction(tr("&Not"), this, &ImageViewer::scalarNot);
  scalarNotAct->setEnabled(false);

  brightenAct = editMenu->addAction(tr("&Brighten"), this, &ImageViewer::brighten);
  brightenAct->setEnabled(false);

  unbrightenAct = editMenu->addAction(tr("&Unbrighten"), this, &ImageViewer::unbrighten);
  unbrightenAct->setEnabled(false);

  rotate90CWAct = editMenu->addAction(tr("&Rotate 90CW"), this, &ImageViewer::rotate90CW);
  rotate90CWAct->setEnabled(false);

  rotate90CCWAct = editMenu->addAction(tr("&Rotate 90CCW"), this, &ImageViewer::rotate90CCW);
  rotate90CCWAct->setEnabled(false);

  translateAct = editMenu->addAction(tr("&Translate"), this, &ImageViewer::translate);
  translateAct->setEnabled(false);

  flipHorizontalAct = editMenu->addAction(tr("&Flip Horizontal"), this, &ImageViewer::flipHorizontal);
  flipHorizontalAct->setEnabled(false);

  flipVerticalAct = editMenu->addAction(tr("&Flip Vertical"), this, &ImageViewer::flipVertical);
  flipVerticalAct->setEnabled(false);

  zoom2InAct= editMenu->addAction(tr("&Zoom In 2"), this, &ImageViewer::zoom2In);
  zoom2InAct->setEnabled(false);

  zoom2OutAct= editMenu->addAction(tr("&Zoom Out 2"), this, &ImageViewer::zoom2Out);
  zoom2OutAct->setEnabled(false);

  QMenu *histogramMenu = editMenu->addMenu(tr("&Show Histogram"));

  redHistogramAct = histogramMenu->addAction(tr("&Red"), this, &ImageViewer::showHistogramRed);
  redHistogramAct->setEnabled(false);
  greenHistogramAct = histogramMenu->addAction(tr("&Green"), this, &ImageViewer::showHistogramGreen);
  greenHistogramAct->setEnabled(false);
  blueHistogramAct = histogramMenu->addAction(tr("&Blue"), this, &ImageViewer::showHistogramBlue);
  blueHistogramAct->setEnabled(false);

  QMenu *normalizedHistogramMenu = editMenu->addMenu(tr("&Show Normalized Histogram"));

  normalizedRedHistogramAct = normalizedHistogramMenu->addAction(tr("&Red"), this, &ImageViewer::showNormalizedHistogramRed);
  normalizedRedHistogramAct->setEnabled(false);
  normalizedGreenHistogramAct = normalizedHistogramMenu->addAction(tr("&Green"), this, &ImageViewer::showNormalizedHistogramGreen);
  normalizedGreenHistogramAct->setEnabled(false);
  normalizedBlueHistogramAct = normalizedHistogramMenu->addAction(tr("&Blue"), this, &ImageViewer::showNormalizedHistogramBlue);
  normalizedBlueHistogramAct->setEnabled(false);

  QMenu *viewMenu = menuBar()->addMenu(tr("&View"));

  zoomInAct = viewMenu->addAction(tr("Zoom &In (25%)"), this, &ImageViewer::zoomIn);
  zoomInAct->setShortcut(QKeySequence::ZoomIn);
  zoomInAct->setEnabled(false);

  zoomOutAct = viewMenu->addAction(tr("Zoom &Out (25%)"), this, &ImageViewer::zoomOut);
  zoomOutAct->setShortcut(QKeySequence::ZoomOut);
  zoomOutAct->setEnabled(false);

  normalSizeAct = viewMenu->addAction(tr("&Normal Size"), this, &ImageViewer::normalSize);
  normalSizeAct->setShortcut(tr("Ctrl+S"));
  normalSizeAct->setEnabled(false);

  viewMenu->addSeparator();

  fitToWindowAct = viewMenu->addAction(tr("&Fit to Window"), this, &ImageViewer::fitToWindow);
  fitToWindowAct->setEnabled(false);
  fitToWindowAct->setCheckable(true);
  fitToWindowAct->setShortcut(tr("Ctrl+F"));

  QMenu *filterMenu = menuBar()->addMenu(tr("Fil&ter"));
  QMenu *lowPassFilterMenu = filterMenu->addMenu(tr("&Low Pass"));
  QMenu *highPassFilterMenu = filterMenu->addMenu(tr("&High Pass"));
  QMenu *nonLinearFilterMenu = filterMenu->addMenu(tr("&Non Linear"));

  filtersAct.push_back(lowPassFilterMenu->addAction(tr("&Average"), this, &ImageViewer::filterAverage));
  filtersAct.push_back(lowPassFilterMenu->addAction(tr("&Gaussian 3"), this, &ImageViewer::filterGaussian));
  filtersAct.push_back(highPassFilterMenu->addAction(tr("High &A"), this, &ImageViewer::filterHighA));
  filtersAct.push_back(highPassFilterMenu->addAction(tr("High &B"), this, &ImageViewer::filterHighB));
  filtersAct.push_back(highPassFilterMenu->addAction(tr("High &C"), this, &ImageViewer::filterHighC));
  filtersAct.push_back(highPassFilterMenu->addAction(tr("High &D"), this, &ImageViewer::filterHighD));
  filtersAct.push_back(highPassFilterMenu->addAction(tr("High &E"), this, &ImageViewer::filterHighE));
  filtersAct.push_back(highPassFilterMenu->addAction(tr("High &F"), this, &ImageViewer::filterHighF));
  filtersAct.push_back(nonLinearFilterMenu->addAction(tr("M&edian"), this, &ImageViewer::filterMedian));
  filtersAct.push_back(nonLinearFilterMenu->addAction(tr("Ma&x"), this, &ImageViewer::filterMax));
  filtersAct.push_back(nonLinearFilterMenu->addAction(tr("Mi&n"), this, &ImageViewer::filterMin));
  for (auto act : filtersAct) { act->setEnabled(!image.isNull()); }

  QMenu *edgeDetectionMenu = menuBar()->addMenu(tr("Edge Detection"));
  edgeDetectionAct.push_back(edgeDetectionMenu->addAction(tr("Gradient"), this, &ImageViewer::edgeDetectionGradient));
  edgeDetectionAct.push_back(edgeDetectionMenu->addAction(tr("2nd Deriv"), this, &ImageViewer::edgeDetection2ndDeriv));
  edgeDetectionAct.push_back(edgeDetectionMenu->addAction(tr("Laplace"), this, &ImageViewer::edgeDetectionLaplace));
  edgeDetectionAct.push_back(edgeDetectionMenu->addAction(tr("LoG"), this, &ImageViewer::edgeDetectionLoG));
  edgeDetectionAct.push_back(edgeDetectionMenu->addAction(tr("Sobel"), this, &ImageViewer::edgeDetectionSobel));
  edgeDetectionAct.push_back(edgeDetectionMenu->addAction(tr("Prewitt"), this, &ImageViewer::edgeDetectionPrewitt));
  edgeDetectionAct.push_back(edgeDetectionMenu->addAction(tr("Roberts"), this, &ImageViewer::edgeDetectionRoberts));
  edgeDetectionAct.push_back(edgeDetectionMenu->addAction(tr("Canny"), this, &ImageViewer::edgeDetectionCanny));
  for (auto act : edgeDetectionAct) { act->setEnabled(!image.isNull()); }

  QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));

  helpMenu->addAction(tr("&About"), this, &ImageViewer::about);
}

void ImageViewer::updateActions() {
  saveAsAct->setEnabled(!image.isNull());
  copyAct->setEnabled(!image.isNull());

  imageAddAct->setEnabled(!image.isNull());
  imageMultiplyAct->setEnabled(!image.isNull());
  imageAndAct->setEnabled(!image.isNull());
  imageOrAct->setEnabled(!image.isNull());
  scalarAddAct->setEnabled(!image.isNull());
  scalarSubstractAct->setEnabled(!image.isNull());
  scalarMultiplyAct->setEnabled(!image.isNull());
  scalarDivideAct->setEnabled(!image.isNull());
  scalarNotAct->setEnabled(!image.isNull());
  brightenAct->setEnabled(!image.isNull());

  unbrightenAct->setEnabled(!image.isNull());
  rotate90CWAct->setEnabled(!image.isNull());
  rotate90CCWAct->setEnabled(!image.isNull());
  translateAct->setEnabled(!image.isNull());
  flipHorizontalAct->setEnabled(!image.isNull());
  flipVerticalAct->setEnabled(!image.isNull());
  zoom2InAct->setEnabled(!image.isNull());
  zoom2OutAct->setEnabled(!image.isNull());
  translateAct->setEnabled(!image.isNull());
  redHistogramAct->setEnabled(!image.isNull());
  greenHistogramAct->setEnabled(!image.isNull());
  blueHistogramAct->setEnabled(!image.isNull());
  normalizedRedHistogramAct->setEnabled(!image.isNull());
  normalizedGreenHistogramAct->setEnabled(!image.isNull());
  normalizedBlueHistogramAct->setEnabled(!image.isNull());

  zoomInAct->setEnabled(!fitToWindowAct->isChecked());
  zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
  normalSizeAct->setEnabled(!fitToWindowAct->isChecked());

  for (auto act : filtersAct) { act->setEnabled(!image.isNull()); }
  for (auto act : edgeDetectionAct) { act->setEnabled(!image.isNull()); }
}

void ImageViewer::scaleImage(double factor) {
  Q_ASSERT(imageLabel->pixmap());
  scaleFactor *= factor;
  imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

  adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
  adjustScrollBar(scrollArea->verticalScrollBar(), factor);

  zoomInAct->setEnabled(scaleFactor < 3.0);
  zoomOutAct->setEnabled(scaleFactor > 0.333);
}

void ImageViewer::adjustScrollBar(QScrollBar *scrollBar, double factor) {
  scrollBar->setValue(int(factor * scrollBar->value()
                          + ((factor - 1) * scrollBar->pageStep()/2)));
}
