#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include "colorwidget.h"

class GraphWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GraphWidget ( QRectF rec, QWidget *parent = 0 );

signals:

public slots:
    void colorChanged(DGtal::Z2i::Point point, ColorWidget *w);
};

#endif // GRAPHWIDGET_H
