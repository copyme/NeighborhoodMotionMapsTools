#ifndef NMM3DPAINTER_H
#define NMM3DPAINTER_H

#include <QWidget>
#include "pixel.h"
#include <map>

namespace Ui {
class NMM3DPainter;
}

class NMM3DPainter : public QWidget
{
    Q_OBJECT

public:
    explicit NMM3DPainter(QWidget *parent = 0);
    ~NMM3DPainter();

private:
    Ui::NMM3DPainter *ui;
    std::map<QString, Pixel *> pixels;
    QPalette pm0m1pm0Pal;
    QPalette pm0pm0pm0Pal;
    QPalette pm0pm0m1Pal;
    QPalette pm0pm0p1Pal;
    QPalette m1pm0pm0Pal;
    QPalette p1pm0pm0Pal;
    QPalette pm0p1pm0Pal;

public slots:
    void draw3DNMM( QString N1, QString N2, QString N3, QString N4, QString N5, QString N6, QString N7 );
};

#endif // NMM3DPAINTER_H
