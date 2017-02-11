#include "torus2d.h"
#include <QPainter>
#include <cmath>
#include <QPolygon>
#include <QPoint>
#include "hextools.h"

Torus2D::Torus2D(QRectF rec, QWidget *parent):
    QWidget(parent)
{
    setGeometry ( rec.x(), rec.y(), rec.width(), rec.height() );
    QPalette pal( palette() );
    pal.setColor( QPalette::Background, Qt::transparent );
    setAutoFillBackground ( true );
    setPalette ( pal );
    m_cos = 0.99500417; //0.1 rad
    m_sin = 0.09983341; //0.1 rad
    m_sqrt3 = std::sqrt(3.);
    m_angle = 0.1;
}

void Torus2D::angleChanged(double angle)
{
    m_cos = std::cos(angle);
    m_sin = std::sin(angle);
    m_angle = angle;
    update();
}

void Torus2D::colorChanged(RealPoint & point, TilingWidget *w)
{
    float L = width()/2.;
    QPointF p ( std::round(point[0] * L + width()/2.), std::round(height() - (point[1] * L + height()/2. ) ) );
    w->setGeometry( QRect( std::round(p.x() - w->width()/2.) ,
                           std::round(p.y() - w->height()/2.) , w->width(),  w->height()) );
    update();
}

void Torus2D::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    QPolygonF poly;

    uint L = round(size().width()/2.);
    uint x = round(size().width()/2.);
    uint y = round(size().height()/2.);

    poly << hexCorners ( QPointF(x, y), L, 0 ) << hexCorners ( QPointF(x, y), L, 1 )
         << hexCorners ( QPointF(x, y), L, 2 ) << hexCorners ( QPointF(x, y), L, 3 )
         << hexCorners ( QPointF(x, y), L, 4 ) << hexCorners ( QPointF(x, y), L, 5 );

    QPen pen(Qt::black, 2);
    painter.setPen(pen);
    painter.drawPolygon(poly);

    QBrush brush;
    brush.setColor(Qt::white);
    brush.setStyle(Qt::SolidPattern);
    QPainterPath path;
    path.addPolygon(poly);
    painter.fillPath(path, brush);

    pen = QPen(Qt::red, 2);
    painter.setPen ( pen );
    paintCriticalLinesHexes ( QPointF ( size().width() / 2. - m_cos * m_sqrt3 * size().width() / 2.,
                                        size().height() / 2. - m_sin * m_sqrt3 * size().width() / 2. ), painter );

    pen = QPen(QColor(255, 165, 0), 2);
    painter.setPen ( pen );
    paintCriticalLinesHexes ( QPointF ( size().width() / 2. + m_cos * m_sqrt3 * size().width() / 2.,
                                        size().height() / 2. + m_sin * m_sqrt3 * size().width() / 2. ), painter );

    pen = QPen(Qt::yellow, 2);
    painter.setPen ( pen );
    paintCriticalLinesHexes ( QPointF ( size().width() / 2. + ( m_cos * m_sqrt3 / 2. - 3. / 2. * m_sin ) * size().width() / 2.,
                                        size().height() / 2. + ( m_sin * m_sqrt3 / 2. + 3. / 2. * m_cos ) * size().height() / 2. ),
                              painter );

    pen = QPen(Qt::green, 2);
    painter.setPen ( pen );
    paintCriticalLinesHexes ( QPointF ( size().width() / 2. + ( -m_cos * m_sqrt3 / 2. - 3. / 2. * m_sin ) * size().width() / 2.,
                                        size().height() / 2. + ( -m_sin * m_sqrt3 / 2. + 3. / 2. * m_cos ) * size().height() / 2. ),
                              painter );

    pen = QPen(Qt::magenta, 2);
    painter.setPen ( pen );
    paintCriticalLinesHexes ( QPointF ( size().width() / 2. + ( m_cos * m_sqrt3 / 2. + 3. / 2. * m_sin ) * size().width() / 2.,
                                        size().height() / 2. + ( m_sin * m_sqrt3 / 2. - 3. / 2. * m_cos ) * size().height() / 2. ),
                              painter );

    pen = QPen(Qt::cyan, 2);
    painter.setPen ( pen );
    paintCriticalLinesHexes ( QPointF ( size().width() / 2. + ( -m_cos * m_sqrt3 / 2. + 3. / 2. * m_sin ) * size().width() / 2.,
                                        size().height() / 2. + ( -m_sin * m_sqrt3 / 2. - 3. / 2. * m_cos ) * size().height() / 2. ),
                              painter );
}

QPointF Torus2D::hexCorners(const QPointF &center, float size, uint index, bool pointTopped)
{
    DGtal::Z2i::RealPoint p = HexTools::HexCorners(DGtal::Z2i::RealPoint(center.x(), center.y()), size, index, pointTopped );
    return QPointF(p[0], p[1]);
}

void Torus2D::paintCriticalLinesHexes(const QPointF &c, QPainter &painter)
{
    // (1, -1, 0) -- green
    QPolygonF poly[19];

    uint L = round ( size().width() / 2. );

    float x = c.x() + m_sqrt3 * size().width() / 2.;
    float y = c.y();

    poly[0] << hexCorners ( QPointF(x, y), L, 0 ) << hexCorners ( QPointF(x, y), L, 1 )
         << hexCorners ( QPointF(x, y), L, 2 ) << hexCorners ( QPointF(x, y), L, 3 )
         << hexCorners ( QPointF(x, y), L, 4 ) << hexCorners ( QPointF(x, y), L, 5 );

    painter.drawPolygon ( poly[0] );

    // (1, 0, -1) -- yellow
    x = c.x() + m_sqrt3 / 2. * size().width() / 2.;
    y = c.y() + 3. / 2. * size().width() / 2.;

    poly[1] << hexCorners ( QPointF(x, y), L, 0 ) << hexCorners ( QPointF(x, y), L, 1 )
         << hexCorners ( QPointF(x, y), L, 2 ) << hexCorners ( QPointF(x, y), L, 3 )
         << hexCorners ( QPointF(x, y), L, 4 ) << hexCorners ( QPointF(x, y), L, 5 );

    painter.drawPolygon ( poly[1] );


    // (0, 1, -1) -- red
    x = c.x() - m_sqrt3 / 2. * size().width() / 2.;
    y = c.y() + 3. / 2. * size().width() / 2.;

    poly[2] << hexCorners ( QPointF(x, y), L, 0 ) << hexCorners ( QPointF(x, y), L, 1 )
         << hexCorners ( QPointF(x, y), L, 2 ) << hexCorners ( QPointF(x, y), L, 3 )
         << hexCorners ( QPointF(x, y), L, 4 ) << hexCorners ( QPointF(x, y), L, 5 );

    painter.drawPolygon ( poly[2] );

    // (-1, 1, 0) -- magenta
    x = c.x() - m_sqrt3 * size().width() / 2.;
    y = c.y();


    poly[3] << hexCorners ( QPointF(x, y), L, 0 ) << hexCorners ( QPointF(x, y), L, 1 )
         << hexCorners ( QPointF(x, y), L, 2 ) << hexCorners ( QPointF(x, y), L, 3 )
         << hexCorners ( QPointF(x, y), L, 4 ) << hexCorners ( QPointF(x, y), L, 5 );

    painter.drawPolygon ( poly[3] );

    // (0, -1, 1) -- cyan
    x = c.x() + m_sqrt3 / 2. * size().width() / 2.;
    y = c.y() - 3. / 2. * size().width() / 2.;

    poly[4] << hexCorners ( QPointF(x, y), L, 0 ) << hexCorners ( QPointF(x, y), L, 1 )
         << hexCorners ( QPointF(x, y), L, 2 ) << hexCorners ( QPointF(x, y), L, 3 )
         << hexCorners ( QPointF(x, y), L, 4 ) << hexCorners ( QPointF(x, y), L, 5 );

    painter.drawPolygon ( poly[4] );

    x = c.x() - m_sqrt3 / 2. * size().width() / 2.;
    y = c.y() - 3. / 2. * size().width() / 2.;

    poly[5] << hexCorners ( QPointF(x, y), L, 0 ) << hexCorners ( QPointF(x, y), L, 1 )
         << hexCorners ( QPointF(x, y), L, 2 ) << hexCorners ( QPointF(x, y), L, 3 )
         << hexCorners ( QPointF(x, y), L, 4 ) << hexCorners ( QPointF(x, y), L, 5 );

    painter.drawPolygon ( poly[5] );

    // center of the neighborhood
    x = c.x();
    y = c.y();

    poly[6] << hexCorners ( QPointF(x, y), L, 0 ) << hexCorners ( QPointF(x, y), L, 1 )
         << hexCorners ( QPointF(x, y), L, 2 ) << hexCorners ( QPointF(x, y), L, 3 )
         << hexCorners ( QPointF(x, y), L, 4 ) << hexCorners ( QPointF(x, y), L, 5 );

    painter.drawPolygon ( poly[6] );

}
