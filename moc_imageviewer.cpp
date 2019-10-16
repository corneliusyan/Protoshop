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
    QByteArrayData data[88];
    char stringdata0[1187];
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
QT_MOC_LITERAL(3, 18, 5), // "print"
QT_MOC_LITERAL(4, 24, 8), // "imageAdd"
QT_MOC_LITERAL(5, 33, 13), // "imageMultiply"
QT_MOC_LITERAL(6, 47, 8), // "imageAnd"
QT_MOC_LITERAL(7, 56, 7), // "imageOr"
QT_MOC_LITERAL(8, 64, 14), // "loadSecondFile"
QT_MOC_LITERAL(9, 79, 9), // "operation"
QT_MOC_LITERAL(10, 89, 12), // "imageOperate"
QT_MOC_LITERAL(11, 102, 9), // "scalarAdd"
QT_MOC_LITERAL(12, 112, 15), // "scalarSubstract"
QT_MOC_LITERAL(13, 128, 14), // "scalarMultiply"
QT_MOC_LITERAL(14, 143, 12), // "scalarDivide"
QT_MOC_LITERAL(15, 156, 9), // "scalarNot"
QT_MOC_LITERAL(16, 166, 13), // "scalarOperate"
QT_MOC_LITERAL(17, 180, 5), // "char*"
QT_MOC_LITERAL(18, 186, 4), // "hint"
QT_MOC_LITERAL(19, 191, 12), // "scalarDialog"
QT_MOC_LITERAL(20, 204, 16), // "fourierTransform"
QT_MOC_LITERAL(21, 221, 23), // "inverseFourierTransform"
QT_MOC_LITERAL(22, 245, 7), // "inverse"
QT_MOC_LITERAL(23, 253, 9), // "grayScale"
QT_MOC_LITERAL(24, 263, 8), // "brighten"
QT_MOC_LITERAL(25, 272, 10), // "unbrighten"
QT_MOC_LITERAL(26, 283, 10), // "rotate90CW"
QT_MOC_LITERAL(27, 294, 11), // "rotate90CCW"
QT_MOC_LITERAL(28, 306, 9), // "translate"
QT_MOC_LITERAL(29, 316, 14), // "flipHorizontal"
QT_MOC_LITERAL(30, 331, 12), // "flipVertical"
QT_MOC_LITERAL(31, 344, 7), // "zoom2In"
QT_MOC_LITERAL(32, 352, 8), // "zoom2Out"
QT_MOC_LITERAL(33, 361, 17), // "histogramEqualize"
QT_MOC_LITERAL(34, 379, 22), // "histogramSpecification"
QT_MOC_LITERAL(35, 402, 13), // "brightenScale"
QT_MOC_LITERAL(36, 416, 15), // "contrastStretch"
QT_MOC_LITERAL(37, 432, 3), // "log"
QT_MOC_LITERAL(38, 436, 10), // "inverseLog"
QT_MOC_LITERAL(39, 447, 5), // "power"
QT_MOC_LITERAL(40, 453, 11), // "graySlicing"
QT_MOC_LITERAL(41, 465, 10), // "bitSlicing"
QT_MOC_LITERAL(42, 476, 16), // "showHistogramRed"
QT_MOC_LITERAL(43, 493, 18), // "showHistogramGreen"
QT_MOC_LITERAL(44, 512, 17), // "showHistogramBlue"
QT_MOC_LITERAL(45, 530, 26), // "showNormalizedHistogramRed"
QT_MOC_LITERAL(46, 557, 28), // "showNormalizedHistogramGreen"
QT_MOC_LITERAL(47, 586, 27), // "showNormalizedHistogramBlue"
QT_MOC_LITERAL(48, 614, 13), // "showHistogram"
QT_MOC_LITERAL(49, 628, 15), // "Qt::GlobalColor"
QT_MOC_LITERAL(50, 644, 9), // "colorCode"
QT_MOC_LITERAL(51, 654, 12), // "isNormalized"
QT_MOC_LITERAL(52, 667, 11), // "showMessage"
QT_MOC_LITERAL(53, 679, 4), // "copy"
QT_MOC_LITERAL(54, 684, 5), // "paste"
QT_MOC_LITERAL(55, 690, 6), // "zoomIn"
QT_MOC_LITERAL(56, 697, 7), // "zoomOut"
QT_MOC_LITERAL(57, 705, 10), // "normalSize"
QT_MOC_LITERAL(58, 716, 11), // "fitToWindow"
QT_MOC_LITERAL(59, 728, 13), // "filterGeneral"
QT_MOC_LITERAL(60, 742, 10), // "KernelType"
QT_MOC_LITERAL(61, 753, 10), // "kernelType"
QT_MOC_LITERAL(62, 764, 13), // "filterAverage"
QT_MOC_LITERAL(63, 778, 14), // "filterGaussian"
QT_MOC_LITERAL(64, 793, 12), // "filterMedian"
QT_MOC_LITERAL(65, 806, 9), // "filterMax"
QT_MOC_LITERAL(66, 816, 9), // "filterMin"
QT_MOC_LITERAL(67, 826, 11), // "filterHighA"
QT_MOC_LITERAL(68, 838, 11), // "filterHighB"
QT_MOC_LITERAL(69, 850, 11), // "filterHighC"
QT_MOC_LITERAL(70, 862, 11), // "filterHighD"
QT_MOC_LITERAL(71, 874, 11), // "filterHighE"
QT_MOC_LITERAL(72, 886, 11), // "filterHighF"
QT_MOC_LITERAL(73, 898, 13), // "filterUnsharp"
QT_MOC_LITERAL(74, 912, 15), // "filterHighboost"
QT_MOC_LITERAL(75, 928, 22), // "edgeDetectionGradientX"
QT_MOC_LITERAL(76, 951, 22), // "edgeDetectionGradientY"
QT_MOC_LITERAL(77, 974, 21), // "edgeDetection2ndDeriv"
QT_MOC_LITERAL(78, 996, 20), // "edgeDetectionLaplace"
QT_MOC_LITERAL(79, 1017, 16), // "edgeDetectionLoG"
QT_MOC_LITERAL(80, 1034, 19), // "edgeDetectionSobelX"
QT_MOC_LITERAL(81, 1054, 19), // "edgeDetectionSobelY"
QT_MOC_LITERAL(82, 1074, 21), // "edgeDetectionPrewittX"
QT_MOC_LITERAL(83, 1096, 21), // "edgeDetectionPrewittY"
QT_MOC_LITERAL(84, 1118, 21), // "edgeDetectionRoberts1"
QT_MOC_LITERAL(85, 1140, 21), // "edgeDetectionRoberts2"
QT_MOC_LITERAL(86, 1162, 18), // "edgeDetectionCanny"
QT_MOC_LITERAL(87, 1181, 5) // "about"

    },
    "ImageViewer\0open\0\0print\0imageAdd\0"
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
      78,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  404,    2, 0x08 /* Private */,
       3,    0,  405,    2, 0x08 /* Private */,
       4,    0,  406,    2, 0x08 /* Private */,
       5,    0,  407,    2, 0x08 /* Private */,
       6,    0,  408,    2, 0x08 /* Private */,
       7,    0,  409,    2, 0x08 /* Private */,
       8,    1,  410,    2, 0x08 /* Private */,
      10,    2,  413,    2, 0x08 /* Private */,
      11,    0,  418,    2, 0x08 /* Private */,
      12,    0,  419,    2, 0x08 /* Private */,
      13,    0,  420,    2, 0x08 /* Private */,
      14,    0,  421,    2, 0x08 /* Private */,
      15,    0,  422,    2, 0x08 /* Private */,
      16,    2,  423,    2, 0x08 /* Private */,
      19,    2,  428,    2, 0x08 /* Private */,
      20,    0,  433,    2, 0x08 /* Private */,
      21,    0,  434,    2, 0x08 /* Private */,
      22,    0,  435,    2, 0x08 /* Private */,
      23,    0,  436,    2, 0x08 /* Private */,
      24,    0,  437,    2, 0x08 /* Private */,
      25,    0,  438,    2, 0x08 /* Private */,
      26,    0,  439,    2, 0x08 /* Private */,
      27,    0,  440,    2, 0x08 /* Private */,
      28,    0,  441,    2, 0x08 /* Private */,
      29,    0,  442,    2, 0x08 /* Private */,
      30,    0,  443,    2, 0x08 /* Private */,
      31,    0,  444,    2, 0x08 /* Private */,
      32,    0,  445,    2, 0x08 /* Private */,
      33,    0,  446,    2, 0x08 /* Private */,
      34,    0,  447,    2, 0x08 /* Private */,
      35,    0,  448,    2, 0x08 /* Private */,
      36,    0,  449,    2, 0x08 /* Private */,
      37,    0,  450,    2, 0x08 /* Private */,
      38,    0,  451,    2, 0x08 /* Private */,
      39,    0,  452,    2, 0x08 /* Private */,
      40,    0,  453,    2, 0x08 /* Private */,
      41,    0,  454,    2, 0x08 /* Private */,
      42,    0,  455,    2, 0x08 /* Private */,
      43,    0,  456,    2, 0x08 /* Private */,
      44,    0,  457,    2, 0x08 /* Private */,
      45,    0,  458,    2, 0x08 /* Private */,
      46,    0,  459,    2, 0x08 /* Private */,
      47,    0,  460,    2, 0x08 /* Private */,
      48,    2,  461,    2, 0x08 /* Private */,
      52,    0,  466,    2, 0x08 /* Private */,
      53,    0,  467,    2, 0x08 /* Private */,
      54,    0,  468,    2, 0x08 /* Private */,
      55,    0,  469,    2, 0x08 /* Private */,
      56,    0,  470,    2, 0x08 /* Private */,
      57,    0,  471,    2, 0x08 /* Private */,
      58,    0,  472,    2, 0x08 /* Private */,
      59,    1,  473,    2, 0x08 /* Private */,
      62,    0,  476,    2, 0x08 /* Private */,
      63,    0,  477,    2, 0x08 /* Private */,
      64,    0,  478,    2, 0x08 /* Private */,
      65,    0,  479,    2, 0x08 /* Private */,
      66,    0,  480,    2, 0x08 /* Private */,
      67,    0,  481,    2, 0x08 /* Private */,
      68,    0,  482,    2, 0x08 /* Private */,
      69,    0,  483,    2, 0x08 /* Private */,
      70,    0,  484,    2, 0x08 /* Private */,
      71,    0,  485,    2, 0x08 /* Private */,
      72,    0,  486,    2, 0x08 /* Private */,
      73,    0,  487,    2, 0x08 /* Private */,
      74,    0,  488,    2, 0x08 /* Private */,
      75,    0,  489,    2, 0x08 /* Private */,
      76,    0,  490,    2, 0x08 /* Private */,
      77,    0,  491,    2, 0x08 /* Private */,
      78,    0,  492,    2, 0x08 /* Private */,
      79,    0,  493,    2, 0x08 /* Private */,
      80,    0,  494,    2, 0x08 /* Private */,
      81,    0,  495,    2, 0x08 /* Private */,
      82,    0,  496,    2, 0x08 /* Private */,
      83,    0,  497,    2, 0x08 /* Private */,
      84,    0,  498,    2, 0x08 /* Private */,
      85,    0,  499,    2, 0x08 /* Private */,
      86,    0,  500,    2, 0x08 /* Private */,
      87,    0,  501,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Bool, QMetaType::QString, QMetaType::Int,    2,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 17,    9,   18,
    QMetaType::Int, QMetaType::Int, 0x80000000 | 17,    9,   18,
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
    QMetaType::Void, 0x80000000 | 49, QMetaType::Bool,   50,   51,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 60,   61,
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
        case 1: _t->print(); break;
        case 2: _t->imageAdd(); break;
        case 3: _t->imageMultiply(); break;
        case 4: _t->imageAnd(); break;
        case 5: _t->imageOr(); break;
        case 6: _t->loadSecondFile((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: { bool _r = _t->imageOperate((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->scalarAdd(); break;
        case 9: _t->scalarSubstract(); break;
        case 10: _t->scalarMultiply(); break;
        case 11: _t->scalarDivide(); break;
        case 12: _t->scalarNot(); break;
        case 13: _t->scalarOperate((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2]))); break;
        case 14: { int _r = _t->scalarDialog((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 15: _t->fourierTransform(); break;
        case 16: _t->inverseFourierTransform(); break;
        case 17: _t->inverse(); break;
        case 18: _t->grayScale(); break;
        case 19: _t->brighten(); break;
        case 20: _t->unbrighten(); break;
        case 21: _t->rotate90CW(); break;
        case 22: _t->rotate90CCW(); break;
        case 23: _t->translate(); break;
        case 24: _t->flipHorizontal(); break;
        case 25: _t->flipVertical(); break;
        case 26: _t->zoom2In(); break;
        case 27: _t->zoom2Out(); break;
        case 28: _t->histogramEqualize(); break;
        case 29: _t->histogramSpecification(); break;
        case 30: _t->brightenScale(); break;
        case 31: _t->contrastStretch(); break;
        case 32: _t->log(); break;
        case 33: _t->inverseLog(); break;
        case 34: _t->power(); break;
        case 35: _t->graySlicing(); break;
        case 36: _t->bitSlicing(); break;
        case 37: _t->showHistogramRed(); break;
        case 38: _t->showHistogramGreen(); break;
        case 39: _t->showHistogramBlue(); break;
        case 40: _t->showNormalizedHistogramRed(); break;
        case 41: _t->showNormalizedHistogramGreen(); break;
        case 42: _t->showNormalizedHistogramBlue(); break;
        case 43: _t->showHistogram((*reinterpret_cast< Qt::GlobalColor(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 44: _t->showMessage(); break;
        case 45: _t->copy(); break;
        case 46: _t->paste(); break;
        case 47: _t->zoomIn(); break;
        case 48: _t->zoomOut(); break;
        case 49: _t->normalSize(); break;
        case 50: _t->fitToWindow(); break;
        case 51: _t->filterGeneral((*reinterpret_cast< KernelType(*)>(_a[1]))); break;
        case 52: _t->filterAverage(); break;
        case 53: _t->filterGaussian(); break;
        case 54: _t->filterMedian(); break;
        case 55: _t->filterMax(); break;
        case 56: _t->filterMin(); break;
        case 57: _t->filterHighA(); break;
        case 58: _t->filterHighB(); break;
        case 59: _t->filterHighC(); break;
        case 60: _t->filterHighD(); break;
        case 61: _t->filterHighE(); break;
        case 62: _t->filterHighF(); break;
        case 63: _t->filterUnsharp(); break;
        case 64: _t->filterHighboost(); break;
        case 65: _t->edgeDetectionGradientX(); break;
        case 66: _t->edgeDetectionGradientY(); break;
        case 67: _t->edgeDetection2ndDeriv(); break;
        case 68: _t->edgeDetectionLaplace(); break;
        case 69: _t->edgeDetectionLoG(); break;
        case 70: _t->edgeDetectionSobelX(); break;
        case 71: _t->edgeDetectionSobelY(); break;
        case 72: _t->edgeDetectionPrewittX(); break;
        case 73: _t->edgeDetectionPrewittY(); break;
        case 74: _t->edgeDetectionRoberts1(); break;
        case 75: _t->edgeDetectionRoberts2(); break;
        case 76: _t->edgeDetectionCanny(); break;
        case 77: _t->about(); break;
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
        if (_id < 78)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 78;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 78)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 78;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
