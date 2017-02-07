#include <QVector>
#include <QPainter>
#include "tilingwidget.h"
#include "hextools.h"

TilingWidget::TilingWidget (QRectF rec, QWidget *parent , const char *p_label) :
    QWidget(parent), label(p_label)
{
    setGeometry ( rec.x(), rec.y(), rec.width(), rec.height() );
    QPalette pal( palette() );
    pal.setColor( QPalette::Background, Qt::transparent );
    setAutoFillBackground ( true );
    setPalette ( pal );

    QPointF center( width()/2., height()/2.);
    int L = 10;
    float dist_v = 3./4. * L;
    float dist_h2 = 1./2. * L;

    // 6 nieghbourhood
    tilings.push_back ( new Frame ( center, L, this ) );
    tilings.push_back ( new Frame ( QPointF( center.x() + L, center.y() ), L, this ) );
    tilings.push_back ( new Frame ( QPointF( center.x() + dist_h2, center.y() - dist_v ), L, this ) );
    tilings.push_back ( new Frame ( QPointF( center.x() + dist_h2, center.y() + dist_v ), L, this ) );
    tilings.push_back ( new Frame ( QPointF( center.x() - dist_h2, center.y() + dist_v ), L, this ) );
    tilings.push_back ( new Frame ( QPointF( center.x() - L, center.y() ), L, this ) );
    tilings.push_back ( new Frame ( QPointF( center.x() - dist_h2, center.y() - dist_v ), L, this ) );

    // another from N 18
    tilings.push_back ( new Frame ( QPointF( center.x() - L - dist_h2, center.y() - dist_v ), L, this ) );
    tilings.push_back ( new Frame ( QPointF( center.x() - 2 * L, center.y() ), L, this ) );
    tilings.push_back ( new Frame ( QPointF( center.x() - L - dist_h2, center.y() + dist_v ), L, this ) );
    tilings.push_back ( new Frame ( QPointF( center.x() - L, center.y() + 2 * dist_v ), L, this ) );
    tilings.push_back ( new Frame ( QPointF( center.x(), center.y() + 2 * dist_v ), L, this ) );
    tilings.push_back ( new Frame ( QPointF( center.x() + L, center.y() + 2 * dist_v ), L, this ) );
    tilings.push_back ( new Frame ( QPointF( center.x() + L + dist_h2, center.y() + dist_v ), L, this ) );
    tilings.push_back ( new Frame ( QPointF( center.x() + 2 * L, center.y() ), L, this ) );
    tilings.push_back ( new Frame ( QPointF( center.x() + L + dist_h2, center.y() - dist_v ), L, this ) );
    tilings.push_back ( new Frame ( QPointF( center.x() + L, center.y() - 2 * dist_v ), L, this ) );
    tilings.push_back ( new Frame ( QPointF( center.x(), center.y() - 2 * dist_v ), L, this ) );
    tilings.push_back ( new Frame ( QPointF( center.x() - L, center.y() - 2 * dist_v ), L, this ) );

    tilings.at ( 0 )->setVisible ( true );
    tilings.at ( 1 )->setVisible ( true );
    tilings.at ( 2 )->setVisible ( true );
    tilings.at ( 3 )->setVisible ( true );
    tilings.at ( 4 )->setVisible ( true );
    tilings.at ( 5 )->setVisible ( true );
    tilings.at ( 6 )->setVisible ( true );
    tilings.at ( 7 )->setVisible ( true );
    tilings.at ( 8 )->setVisible ( true );
    tilings.at ( 9 )->setVisible ( true );
    tilings.at ( 9 )->setVisible ( true );
    tilings.at ( 10 )->setVisible ( true );
    tilings.at ( 11 )->setVisible ( true );
    tilings.at ( 12 )->setVisible ( true );
    tilings.at ( 13 )->setVisible ( true );
    tilings.at ( 14 )->setVisible ( true );
    tilings.at ( 15 )->setVisible ( true );
    tilings.at ( 16 )->setVisible ( true );
    tilings.at ( 17 )->setVisible ( true );
    tilings.at ( 18 )->setVisible ( true );

    colorMap.push_back ( Qt::cyan );
    colorMap.push_back ( Qt::magenta );
    colorMap.push_back ( QColor ( 255, 165, 0 ) ); // orange
    colorMap.push_back ( Qt::yellow );
    colorMap.push_back ( Qt::green );
    colorMap.push_back ( Qt::red );
    colorMap.push_back ( Qt::blue );
    colorMap.push_back ( Qt::black );
}

void TilingWidget::paintEvent(QPaintEvent *)
{

    for ( QVector<Frame *>::const_iterator it = tilings.begin(); it != tilings.end(); ++it )
        (*it)->clear();
    tilings.at ( 0 )->addColor ( colorMap[7] );

    for ( unsigned int i = 0; i < points.size(); i++ )
    {
        if( points.at ( i )[0] == 1 && points.at ( i )[1] == -1 && points.at ( i )[2] == 0)
            tilings.at ( 1 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == 1 && points.at ( i )[1] == 0 && points.at ( i )[2] == -1)
            tilings.at ( 2 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == 0 && points.at ( i )[1] == -1 && points.at ( i )[2] == 1)
            tilings.at ( 3 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == -1 && points.at ( i )[1] == 0 && points.at ( i )[2] == 1)
            tilings.at ( 4 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == -1 && points.at ( i )[1] == 1 && points.at ( i )[2] == 0)
            tilings.at ( 5 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == 0 && points.at ( i )[1] == 1 && points.at ( i )[2] == -1)
            tilings.at ( 6 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == -1 && points.at ( i )[1] == 2 && points.at ( i )[2] == -1)
            tilings.at ( 7 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == -2 && points.at ( i )[1] == 2 && points.at ( i )[2] == 0)
            tilings.at ( 8 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == -2 && points.at ( i )[1] == 1 && points.at ( i )[2] == 1)
            tilings.at ( 9 )->addColor ( colorMap[i] );
       else if( points.at ( i )[0] == -2 && points.at ( i )[1] == 0 && points.at ( i )[2] == 2)
            tilings.at ( 10 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == -1 && points.at ( i )[1] == -1 && points.at ( i )[2] == 2)
            tilings.at ( 11 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == 0 && points.at ( i )[1] == -2 && points.at ( i )[2] == 2)
            tilings.at ( 12 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == 1 && points.at ( i )[1] == -2 && points.at ( i )[2] == 1)
            tilings.at ( 13 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == 2 && points.at ( i )[1] == -2 && points.at ( i )[2] == 0)
            tilings.at ( 14 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == 2 && points.at ( i )[1] == -1 && points.at ( i )[2] == -1)
            tilings.at ( 15 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == 2 && points.at ( i )[1] == 0 && points.at ( i )[2] == -2)
            tilings.at ( 16 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == 1 && points.at ( i )[1] == 1 && points.at ( i )[2] == -2)
            tilings.at ( 17 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == 0 && points.at ( i )[1] == 2 && points.at ( i )[2] == -2)
            tilings.at ( 18 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == 0 && points.at ( i )[1] == 0 && points.at ( i )[2] == 0)
            tilings.at ( 0 )->addColor ( colorMap[i] );
        else
            throw std::runtime_error("Point outside of N_18!");
    }
    QPainter painter(this);
    painter.setRenderHints(QPainter::TextAntialiasing);
    QFont font;
    font.setPointSize(6);
    painter.setFont(font);
    painter.setPen(QPen(Qt::black, 2));
    painter.drawText(QPoint(0,height()),label);
}

void TilingWidget::colorChanged(std::vector<Z3i::Point> &points)
{
    this->points = points;
    update();
}

Frame::Frame (QPointF center, float L, QWidget *parent) : QWidget ( parent )
{
    setGeometry ( center.x() - L/2., center.y() - L/2., L+0.5, L+0.5 );
    QPalette pal( palette() );
    pal.setColor( QPalette::Background, Qt::transparent );
    setAutoFillBackground ( true );
    setPalette ( pal );
}

void Frame::addColor (const QColor &color)
{
    if ( first == Qt::transparent )
        first = color;
    else
        second = color;
}

void Frame::paintEvent ( QPaintEvent * )
{
    float x = width()/2.;
    float y = height()/2.;
    float L = y - 0.25;
    QPainter painter ( this );
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    QPolygonF poly;
    QPen pen(Qt::black, 0.5);
    QBrush brush;

    if ( second == Qt::transparent )
    {
        poly << hexCorners ( QPointF(x, y), L, 0 ) << hexCorners ( QPointF(x, y), L, 1 )
             << hexCorners ( QPointF(x, y), L, 2 ) << hexCorners ( QPointF(x, y), L, 3 )
             << hexCorners ( QPointF(x, y), L, 4 ) << hexCorners ( QPointF(x, y), L, 5 );

        painter.setPen(pen);
        painter.drawPolygon(poly);

        brush.setColor(first);
        brush.setStyle(Qt::SolidPattern);
        QPainterPath path;
        path.addPolygon(poly);
        painter.fillPath(path, brush);
    }
    else
    {
         poly << hexCorners ( QPointF(x, y), L, 0 ) << hexCorners ( QPointF(x, y), L, 1 )
             << hexCorners ( QPointF(x, y), L, 2 ) << hexCorners ( QPointF(x, y), L, 3 );

         QPolygonF poly2;
         poly2  << hexCorners ( QPointF(x, y), L, 0 ) << hexCorners ( QPointF(x, y), L, 3 )
                << hexCorners ( QPointF(x, y), L, 4 ) << hexCorners ( QPointF(x, y), L, 5 );

        painter.setPen(pen);
        painter.drawPolygon(poly);
        painter.drawPolygon(poly2);

        brush.setStyle(Qt::SolidPattern);
        QPainterPath path;
        QPainterPath path2;
        brush.setColor(first);
        path.addPolygon(poly);
        painter.fillPath(path, brush);
        brush.setColor(second);
        path2.addPolygon(poly2);
        painter.fillPath(path2, brush);

    }
}

QPointF Frame::hexCorners(const QPointF &center, float size, uint index)
{
    DGtal::Z2i::RealPoint p = HexTools::HexCorners(DGtal::Z2i::RealPoint(center.x(), center.y()), size, index );
    return QPointF(p[0], p[1]);
}
