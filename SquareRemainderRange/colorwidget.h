#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QWidget>
#include <QString>
#include <DGtal/helpers/StdDefs.h>

using namespace DGtal;
using namespace Z2i;

class ColorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ColorWidget(QRectF rec, QWidget *parent = 0, const char * label = 0);

signals:

public slots:
    void colorChanged(std::vector<Point> & points);
    void labelTransformedPoint ( const char * label );


protected:
    void paintEvent(QPaintEvent *);

private:
    std::vector<Point> points;
    QString label, label2;
};

#endif // COLORWIDGET_H
