/****************************************************************************
** Meta object code from reading C++ file 'imageviewer.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "src/ui/imageviewer.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imageviewer.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ImageViewer_t {
    QByteArrayData data[89];
    char stringdata0[1194];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ImageViewer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ImageViewer_t qt_meta_stringdata_ImageViewer = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ImageViewer"
QT_MOC_LITERAL(1, 12, 4), // "open"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 6), // "saveAs"
QT_MOC_LITERAL(4, 25, 5), // "print"
QT_MOC_LITERAL(5, 31, 8), // "imageAdd"
QT_MOC_LITERAL(6, 40, 13), // "imageMultiply"
QT_MOC_LITERAL(7, 54, 8), // "imageAnd"
QT_MOC_LITERAL(8, 63, 7), // "imageOr"
QT_MOC_LITERAL(9, 71, 14), // "loadSecondFile"
QT_MOC_LITERAL(10, 86, 9), // "operation"
QT_MOC_LITERAL(11, 96, 12), // "imageOperate"
QT_MOC_LITERAL(12, 109, 9), // "scalarAdd"
QT_MOC_LITERAL(13, 119, 15), // "scalarSubstract"
QT_MOC_LITERAL(14, 135, 14), // "scalarMultiply"
QT_MOC_LITERAL(15, 150, 12), // "scalarDivide"
QT_MOC_LITERAL(16, 163, 9), // "scalarNot"
QT_MOC_LITERAL(17, 173, 13), // "scalarOperate"
QT_MOC_LITERAL(18, 187, 5), // "char*"
QT_MOC_LITERAL(19, 193, 4), // "hint"
QT_MOC_LITERAL(20, 198, 12), // "scalarDialog"
QT_MOC_LITERAL(21, 211, 16), // "fourierTransform"
QT_MOC_LITERAL(22, 228, 23), // "inverseFourierTransform"
QT_MOC_LITERAL(23, 252, 7), // "inverse"
QT_MOC_LITERAL(24, 260, 9), // "grayScale"
QT_MOC_LITERAL(25, 270, 8), // "brighten"
QT_MOC_LITERAL(26, 279, 10), // "unbrighten"
QT_MOC_LITERAL(27, 290, 10), // "rotate90CW"
QT_MOC_LITERAL(28, 301, 11), // "rotate90CCW"
QT_MOC_LITERAL(29, 313, 9), // "translate"
QT_MOC_LITERAL(30, 323, 14), // "flipHorizontal"
QT_MOC_LITERAL(31, 338, 12), // "flipVertical"
QT_MOC_LITERAL(32, 351, 7), // "zoom2In"
QT_MOC_LITERAL(33, 359, 8), // "zoom2Out"
QT_MOC_LITERAL(34, 368, 17), // "histogramEqualize"
QT_MOC_LITERAL(35, 386, 22), // "histogramSpecification"
QT_MOC_LITERAL(36, 409, 13), // "brightenScale"
QT_MOC_LITERAL(37, 423, 15), // "contrastStretch"
QT_MOC_LITERAL(38, 439, 3), // "log"
QT_MOC_LITERAL(39, 443, 10), // "inverseLog"
QT_MOC_LITERAL(40, 454, 5), // "power"
QT_MOC_LITERAL(41, 460, 11), // "graySlicing"
QT_MOC_LITERAL(42, 472, 10), // "bitSlicing"
QT_MOC_LITERAL(43, 483, 16), // "showHistogramRed"
QT_MOC_LITERAL(44, 500, 18), // "showHistogramGreen"
QT_MOC_LITERAL(45, 519, 17), // "showHistogramBlue"
QT_MOC_LITERAL(46, 537, 26), // "showNormalizedHistogramRed"
QT_MOC_LITERAL(47, 564, 28), // "showNormalizedHistogramGreen"
QT_MOC_LITERAL(48, 593, 27), // "showNormalizedHistogramBlue"
QT_MOC_LITERAL(49, 621, 13), // "showHistogram"
QT_MOC_LITERAL(50, 635, 15), // "Qt::GlobalColor"
QT_MOC_LITERAL(51, 651, 9), // "colorCode"
QT_MOC_LITERAL(52, 661, 12), // "isNormalized"
QT_MOC_LITERAL(53, 674, 11), // "showMessage"
QT_MOC_LITERAL(54, 686, 4), // "copy"
QT_MOC_LITERAL(55, 691, 5), // "paste"
QT_MOC_LITERAL(56, 697, 6), // "zoomIn"
QT_MOC_LITERAL(57, 704, 7), // "zoomOut"
QT_MOC_LITERAL(58, 712, 10), // "normalSize"
QT_MOC_LITERAL(59, 723, 11), // "fitToWindow"
QT_MOC_LITERAL(60, 735, 13), // "filterGeneral"
QT_MOC_LITERAL(61, 749, 10), // "KernelType"
QT_MOC_LITERAL(62, 760, 10), // "kernelType"
QT_MOC_LITERAL(63, 771, 13), // "filterAverage"
QT_MOC_LITERAL(64, 785, 14), // "filterGaussian"
QT_MOC_LITERAL(65, 800, 12), // "filterMedian"
QT_MOC_LITERAL(66, 813, 9), // "filterMax"
QT_MOC_LITERAL(67, 823, 9), // "filterMin"
QT_MOC_LITERAL(68, 833, 11), // "filterHighA"
QT_MOC_LITERAL(69, 845, 11), // "filterHighB"
QT_MOC_LITERAL(70, 857, 11), // "filterHighC"
QT_MOC_LITERAL(71, 869, 11), // "filterHighD"
QT_MOC_LITERAL(72, 881, 11), // "filterHighE"
QT_MOC_LITERAL(73, 893, 11), // "filterHighF"
QT_MOC_LITERAL(74, 905, 13), // "filterUnsharp"
QT_MOC_LITERAL(75, 919, 15), // "filterHighboost"
QT_MOC_LITERAL(76, 935, 22), // "edgeDetectionGradientX"
QT_MOC_LITERAL(77, 958, 22), // "edgeDetectionGradientY"
QT_MOC_LITERAL(78, 981, 21), // "edgeDetection2ndDeriv"
QT_MOC_LITERAL(79, 1003, 20), // "edgeDetectionLaplace"
QT_MOC_LITERAL(80, 1024, 16), // "edgeDetectionLoG"
QT_MOC_LITERAL(81, 1041, 19), // "edgeDetectionSobelX"
QT_MOC_LITERAL(82, 1061, 19), // "edgeDetectionSobelY"
QT_MOC_LITERAL(83, 1081, 21), // "edgeDetectionPrewittX"
QT_MOC_LITERAL(84, 1103, 21), // "edgeDetectionPrewittY"
QT_MOC_LITERAL(85, 1125, 21), // "edgeDetectionRoberts1"
QT_MOC_LITERAL(86, 1147, 21), // "edgeDetectionRoberts2"
QT_MOC_LITERAL(87, 1169, 18), // "edgeDetectionCanny"
QT_MOC_LITERAL(88, 1188, 5) // "about"

    },
    "ImageViewer\0open\0\0saveAs\0print\0imageAdd\0"
    "imageMultiply\0imageAnd\0imageOr\0"
    "loadSecondFile\0operation\0imageOperate\0"
    "scalarAdd\0scalarSubstract\0scalarMultiply\0"
    "scalarDivide\0scalarNot\0scalarOperate\0"
    "char*\0hint\0scalarDialog\0fourierTransform\0"
    "inverseFourierTransform\0inverse\0"
    "grayScale\0brighten\0unbrighten\0rotate90CW\0"
    "rotate90CCW\0translate\0flipHorizontal\0"
    "flipVertical\0zoom2In\0zoom2Out\0"
    "histogramEqualize\0histogramSpecification\0"
    "brightenScale\0contrastStretch\0log\0"
    "inverseLog\0power\0graySlicing\0bitSlicing\0"
    "showHistogramRed\0showHistogramGreen\0"
    "showHistogramBlue\0showNormalizedHistogramRed\0"
    "showNormalizedHistogramGreen\0"
    "showNormalizedHistogramBlue\0showHistogram\0"
    "Qt::GlobalColor\0colorCode\0isNormalized\0"
    "showMessage\0copy\0paste\0zoomIn\0zoomOut\0"
    "normalSize\0fitToWindow\0filterGeneral\0"
    "KernelType\0kernelType\0filterAverage\0"
    "filterGaussian\0filterMedian\0filterMax\0"
    "filterMin\0filterHighA\0filterHighB\0"
    "filterHighC\0filterHighD\0filterHighE\0"
    "filterHighF\0filterUnsharp\0filterHighboost\0"
    "edgeDetectionGradientX\0edgeDetectionGradientY\0"
    "edgeDetection2ndDeriv\0edgeDetectionLaplace\0"
    "edgeDetectionLoG\0edgeDetectionSobelX\0"
    "edgeDetectionSobelY\0edgeDetectionPrewittX\0"
    "edgeDetectionPrewittY\0edgeDetectionRoberts1\0"
    "edgeDetectionRoberts2\0edgeDetectionCanny\0"
    "about"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ImageViewer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      79,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  409,    2, 0x08 /* Private */,
       3,    0,  410,    2, 0x08 /* Private */,
       4,    0,  411,    2, 0x08 /* Private */,
       5,    0,  412,    2, 0x08 /* Private */,
       6,    0,  413,    2, 0x08 /* Private */,
       7,    0,  414,    2, 0x08 /* Private */,
       8,    0,  415,    2, 0x08 /* Private */,
       9,    1,  416,    2, 0x08 /* Private */,
      11,    2,  419,    2, 0x08 /* Private */,
      12,    0,  424,    2, 0x08 /* Private */,
      13,    0,  425,    2, 0x08 /* Private */,
      14,    0,  426,    2, 0x08 /* Private */,
      15,    0,  427,    2, 0x08 /* Private */,
      16,    0,  428,    2, 0x08 /* Private */,
      17,    2,  429,    2, 0x08 /* Private */,
      20,    2,  434,    2, 0x08 /* Private */,
      21,    0,  439,    2, 0x08 /* Private */,
      22,    0,  440,    2, 0x08 /* Private */,
      23,    0,  441,    2, 0x08 /* Private */,
      24,    0,  442,    2, 0x08 /* Private */,
      25,    0,  443,    2, 0x08 /* Private */,
      26,    0,  444,    2, 0x08 /* Private */,
      27,    0,  445,    2, 0x08 /* Private */,
      28,    0,  446,    2, 0x08 /* Private */,
      29,    0,  447,    2, 0x08 /* Private */,
      30,    0,  448,    2, 0x08 /* Private */,
      31,    0,  449,    2, 0x08 /* Private */,
      32,    0,  450,    2, 0x08 /* Private */,
      33,    0,  451,    2, 0x08 /* Private */,
      34,    0,  452,    2, 0x08 /* Private */,
      35,    0,  453,    2, 0x08 /* Private */,
      36,    0,  454,    2, 0x08 /* Private */,
      37,    0,  455,    2, 0x08 /* Private */,
      38,    0,  456,    2, 0x08 /* Private */,
      39,    0,  457,    2, 0x08 /* Private */,
      40,    0,  458,    2, 0x08 /* Private */,
      41,    0,  459,    2, 0x08 /* Private */,
      42,    0,  460,    2, 0x08 /* Private */,
      43,    0,  461,    2, 0x08 /* Private */,
      44,    0,  462,    2, 0x08 /* Private */,
      45,    0,  463,    2, 0x08 /* Private */,
      46,    0,  464,    2, 0x08 /* Private */,
      47,    0,  465,    2, 0x08 /* Private */,
      48,    0,  466,    2, 0x08 /* Private */,
      49,    2,  467,    2, 0x08 /* Private */,
      53,    0,  472,    2, 0x08 /* Private */,
      54,    0,  473,    2, 0x08 /* Private */,
      55,    0,  474,    2, 0x08 /* Private */,
      56,    0,  475,    2, 0x08 /* Private */,
      57,    0,  476,    2, 0x08 /* Private */,
      58,    0,  477,    2, 0x08 /* Private */,
      59,    0,  478,    2, 0x08 /* Private */,
      60,    1,  479,    2, 0x08 /* Private */,
      63,    0,  482,    2, 0x08 /* Private */,
      64,    0,  483,    2, 0x08 /* Private */,
      65,    0,  484,    2, 0x08 /* Private */,
      66,    0,  485,    2, 0x08 /* Private */,
      67,    0,  486,    2, 0x08 /* Private */,
      68,    0,  487,    2, 0x08 /* Private */,
      69,    0,  488,    2, 0x08 /* Private */,
      70,    0,  489,    2, 0x08 /* Private */,
      71,    0,  490,    2, 0x08 /* Private */,
      72,    0,  491,    2, 0x08 /* Private */,
      73,    0,  492,    2, 0x08 /* Private */,
      74,    0,  493,    2, 0x08 /* Private */,
      75,    0,  494,    2, 0x08 /* Private */,
      76,    0,  495,    2, 0x08 /* Private */,
      77,    0,  496,    2, 0x08 /* Private */,
      78,    0,  497,    2, 0x08 /* Private */,
      79,    0,  498,    2, 0x08 /* Private */,
      80,    0,  499,    2, 0x08 /* Private */,
      81,    0,  500,    2, 0x08 /* Private */,
      82,    0,  501,    2, 0x08 /* Private */,
      83,    0,  502,    2, 0x08 /* Private */,
      84,    0,  503,    2, 0x08 /* Private */,
      85,    0,  504,    2, 0x08 /* Private */,
      86,    0,  505,    2, 0x08 /* Private */,
      87,    0,  506,    2, 0x08 /* Private */,
      88,    0,  507,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Bool, QMetaType::QString, QMetaType::Int,    2,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 18,   10,   19,
    QMetaType::Int, QMetaType::Int, 0x80000000 | 18,   10,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 50, QMetaType::Bool,   51,   52,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 61,   62,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ImageViewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ImageViewer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->open(); break;
        case 1: _t->saveAs(); break;
        case 2: _t->print(); break;
        case 3: _t->imageAdd(); break;
        case 4: _t->imageMultiply(); break;
        case 5: _t->imageAnd(); break;
        case 6: _t->imageOr(); break;
        case 7: _t->loadSecondFile((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: { bool _r = _t->imageOperate((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->scalarAdd(); break;
        case 10: _t->scalarSubstract(); break;
        case 11: _t->scalarMultiply(); break;
        case 12: _t->scalarDivide(); break;
        case 13: _t->scalarNot(); break;
        case 14: _t->scalarOperate((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2]))); break;
        case 15: { int _r = _t->scalarDialog((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 16: _t->fourierTransform(); break;
        case 17: _t->inverseFourierTransform(); break;
        case 18: _t->inverse(); break;
        case 19: _t->grayScale(); break;
        case 20: _t->brighten(); break;
        case 21: _t->unbrighten(); break;
        case 22: _t->rotate90CW(); break;
        case 23: _t->rotate90CCW(); break;
        case 24: _t->translate(); break;
        case 25: _t->flipHorizontal(); break;
        case 26: _t->flipVertical(); break;
        case 27: _t->zoom2In(); break;
        case 28: _t->zoom2Out(); break;
        case 29: _t->histogramEqualize(); break;
        case 30: _t->histogramSpecification(); break;
        case 31: _t->brightenScale(); break;
        case 32: _t->contrastStretch(); break;
        case 33: _t->log(); break;
        case 34: _t->inverseLog(); break;
        case 35: _t->power(); break;
        case 36: _t->graySlicing(); break;
        case 37: _t->bitSlicing(); break;
        case 38: _t->showHistogramRed(); break;
        case 39: _t->showHistogramGreen(); break;
        case 40: _t->showHistogramBlue(); break;
        case 41: _t->showNormalizedHistogramRed(); break;
        case 42: _t->showNormalizedHistogramGreen(); break;
        case 43: _t->showNormalizedHistogramBlue(); break;
        case 44: _t->showHistogram((*reinterpret_cast< Qt::GlobalColor(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 45: _t->showMessage(); break;
        case 46: _t->copy(); break;
        case 47: _t->paste(); break;
        case 48: _t->zoomIn(); break;
        case 49: _t->zoomOut(); break;
        case 50: _t->normalSize(); break;
        case 51: _t->fitToWindow(); break;
        case 52: _t->filterGeneral((*reinterpret_cast< KernelType(*)>(_a[1]))); break;
        case 53: _t->filterAverage(); break;
        case 54: _t->filterGaussian(); break;
        case 55: _t->filterMedian(); break;
        case 56: _t->filterMax(); break;
        case 57: _t->filterMin(); break;
        case 58: _t->filterHighA(); break;
        case 59: _t->filterHighB(); break;
        case 60: _t->filterHighC(); break;
        case 61: _t->filterHighD(); break;
        case 62: _t->filterHighE(); break;
        case 63: _t->filterHighF(); break;
        case 64: _t->filterUnsharp(); break;
        case 65: _t->filterHighboost(); break;
        case 66: _t->edgeDetectionGradientX(); break;
        case 67: _t->edgeDetectionGradientY(); break;
        case 68: _t->edgeDetection2ndDeriv(); break;
        case 69: _t->edgeDetectionLaplace(); break;
        case 70: _t->edgeDetectionLoG(); break;
        case 71: _t->edgeDetectionSobelX(); break;
        case 72: _t->edgeDetectionSobelY(); break;
        case 73: _t->edgeDetectionPrewittX(); break;
        case 74: _t->edgeDetectionPrewittY(); break;
        case 75: _t->edgeDetectionRoberts1(); break;
        case 76: _t->edgeDetectionRoberts2(); break;
        case 77: _t->edgeDetectionCanny(); break;
        case 78: _t->about(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ImageViewer::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_ImageViewer.data,
    qt_meta_data_ImageViewer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ImageViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ImageViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ImageViewer.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int ImageViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 79)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 79;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 79)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 79;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
