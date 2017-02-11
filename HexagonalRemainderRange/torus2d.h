#ifndef TORUS2D_H
#define TORUS2D_H

#include <QWidget>
#include <QPoint>
#include <vector>
#include <colorwidget.h>
#include <tilingwidget.h>
#include <DGtal/helpers/StdDefs.h>

class Torus2D : public QWidget
{
    Q_OBJECT
public:
    Torus2D(QRectF rec, QWidget *parent = 0);

signals:

public slots:
    void angleChanged(double angle);
    //! \todo generalization of type colorwidget
    void colorChanged(DGtal::Z2i::RealPoint & point, TilingWidget * w);

protected:
    void paintEvent(QPaintEvent *);
private:
    double m_cos, m_sin, m_sqrt3, m_angle;
    std::vector<QPointF> pointsD;
    // This method uses idea in which we consider different hexagons.
    void paintCriticalLinesHexes(const QPointF &center, QPainter &painter);
    QPointF hexCorners(const QPointF & center, float size, uint index, bool pointTopped = true);
};

#endif // TORUS2D_H
