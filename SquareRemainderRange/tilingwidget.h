#ifndef TILINGWIDGET_H
#define TILINGWIDGET_H

#include <QWidget>
#include <DGtal/helpers/StdDefs.h>

using namespace DGtal;
using namespace Z2i;

class Frame : public QWidget
{
    Q_OBJECT
public:
    explicit Frame (QRectF rec, QWidget *parent = 0 );
    void clear() { first = second = Qt::transparent; }
    void addColor (const QColor & color );
private:
    QColor first, second;
protected:
    void paintEvent ( QPaintEvent * );
};


class TilingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TilingWidget (QRectF rec, QWidget *parent = 0, const char * p_label = 0 );

private:
    QVector < Frame * > tilings;
    std::vector<Point> points;
    std::vector < QColor > colorMap;
    QString label;
protected:
    void paintEvent ( QPaintEvent * );

signals:

public slots:
    void colorChanged ( std::vector<Point> & points );
    void setAdjacency (int state);
};

#endif // TILINGWIDGET_H
