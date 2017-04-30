#ifndef TORUS2D_H
#define TORUS2D_H

#include <QWidget>
#include <QPoint>
#include <vector>
#include <colorwidget.h>
#include <tilingwidget.h>
#include <DGtal/helpers/StdDefs.h>
#include "tikzexport.h"

class Torus2D : public QWidget
{
    Q_OBJECT
public:
    Torus2D(QRectF rec, QWidget *parent = 0);
    void exportToTikz ( QTikzPicture & tikz );

signals:

public slots:
    void angleChanged(double angle);
    void translationChanged(double x, double y);
    //! \todo generalization of type colorwidget
    void colorChanged(DGtal::Z2i::RealPoint & point, TilingWidget * w);

protected:
    void paintEvent(QPaintEvent *);
private:
    double m_cos, m_sin;
    double m_x, m_y;
};

#endif // TORUS2D_H
