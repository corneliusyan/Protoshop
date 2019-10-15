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

void ImageViewer::brighten() {
  AdjustmentBrighten::apply(img,25);
  const QImage newImage = img->getQImage();
  setImage(newImage);
  showMessage();
}

void ImageViewer::unbrighten() {
  AdjustmentBrighten::apply(img,-25);
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

void ImageViewer::showHistogramRed() {
  showHistogram(Qt::red);
}

void ImageViewer::showHistogramGreen() {
  showHistogram(Qt::green);
}

void ImageViewer::showHistogramBlue() {
  showHistogram(Qt::blue);
}

void ImageViewer::showHistogram(Qt::GlobalColor colorCode) {
  int hist[256] = {0};
  int height = image.height();
  int width = image.width();
  int max = 0;

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

  brightenAct = editMenu->addAction(tr("&brighten"), this, &ImageViewer::brighten);
  brightenAct->setEnabled(false);

  unbrightenAct = editMenu->addAction(tr("&unbrighten"), this, &ImageViewer::unbrighten);
  unbrightenAct->setEnabled(false);

  rotate90CWAct = editMenu->addAction(tr("&Rotate 90CW"), this, &ImageViewer::rotate90CW);
  rotate90CWAct->setEnabled(false);

  rotate90CCWAct = editMenu->addAction(tr("&Rotate 90CCW"), this, &ImageViewer::rotate90CCW);
  rotate90CCWAct->setEnabled(false);

  QMenu *histogramMenu = editMenu->addMenu(tr("&Show Histogram"));

  redHistogramAct = histogramMenu->addAction(tr("&Red"), this, &ImageViewer::showHistogramRed);
  redHistogramAct->setEnabled(false);
  greenHistogramAct = histogramMenu->addAction(tr("&Green"), this, &ImageViewer::showHistogramGreen);
  greenHistogramAct->setEnabled(false);
  blueHistogramAct = histogramMenu->addAction(tr("&Blue"), this, &ImageViewer::showHistogramBlue);
  blueHistogramAct->setEnabled(false);

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

  QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));

  helpMenu->addAction(tr("&About"), this, &ImageViewer::about);
}

void ImageViewer::updateActions() {
  saveAsAct->setEnabled(!image.isNull());
  copyAct->setEnabled(!image.isNull());
  brightenAct->setEnabled(!image.isNull());
  unbrightenAct->setEnabled(!image.isNull());
  rotate90CWAct->setEnabled(!image.isNull());
  rotate90CCWAct->setEnabled(!image.isNull());
  redHistogramAct->setEnabled(!image.isNull());
  greenHistogramAct->setEnabled(!image.isNull());
  blueHistogramAct->setEnabled(!image.isNull());
  zoomInAct->setEnabled(!fitToWindowAct->isChecked());
  zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
  normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
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
