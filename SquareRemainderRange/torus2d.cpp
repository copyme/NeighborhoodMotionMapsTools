#include "torus2d.h"
#include <QPainter>
#include <cmath>

Torus2D::Torus2D(QRectF rec, QWidget *parent):
    QWidget(parent)
{
    setGeometry ( rec.x(), rec.y(), rec.width(), rec.height() );
    QPalette pal( palette() );
    pal.setColor( QPalette::Background, Qt::white );
    setAutoFillBackground ( true );
    setPalette ( pal );
    m_cos = 0.99500417; //0.1 rad
    m_sin = 0.09983341; //0.1 rad
    m_x = 0.f;
    m_y = 0.f;
}

void Torus2D::exportToTikz(QTikzPicture &tikz)
{
    //Corners
    QPointF bottomLeft (0,0);
    QPointF bottomRight (1,0);
    QPointF topLeft (0,1);
    QPoint topRight (1,1);

    //generator for 4-conn
    QPointF p0 (1- m_cos, 1 - m_sin);
    QPointF p1 (m_cos, m_sin);
    QPointF p2 (1-m_sin, m_cos);
    QPointF p3 (m_sin,1 - m_cos);

    tikz.beginScope("color=blue");
        //border lines
        tikz.path ( QRectF ( bottomLeft, topRight ) );
        //vertical
        tikz.line ( QPointF ( p0.x(), 0 ), QPointF ( p0.x(), 1 ) );
        tikz.line ( QPointF ( p1.x(), 0 ), QPointF ( p1.x(), 1 ) );
        //horizontal
        tikz.line ( QPointF ( 0, p0.y() ), QPointF ( 1, p0.y() ) );
        tikz.line ( QPointF ( 0, p1.y() ), QPointF ( 1, p1.y() ) );
        //vertical
        tikz.line ( QPointF ( 0, p2.y() ), QPointF ( 1, p2.y() ) );
        tikz.line ( QPointF ( 0, p3.y() ), QPointF ( 1, p3.y() ) );
        //horizontal
        tikz.line ( QPointF ( p2.x(), 0 ), QPointF ( p2.x(), 1 ) );
        tikz.line ( QPointF ( p3.x(), 0 ), QPointF ( p3.x(), 1 ) );
    tikz.endScope();

    tikz.beginScope("color=red");
        tikz.line ( topRight, p0 );
        tikz.line ( bottomLeft, p1 );
        tikz.line ( bottomRight, p2 );
        tikz.line ( topLeft, p3 );
    tikz.endScope();

    tikz.beginScope("fill=black,draw=red");
        tikz.drawCircle(p0,0.005);
        tikz.drawCircle(p1,0.005);
        tikz.drawCircle(p2,0.005);
        tikz.drawCircle(p3,0.005);

        tikz.fillCircle(p0,0.005);
        tikz.fillCircle(p1,0.005);
        tikz.fillCircle(p2,0.005);
        tikz.fillCircle(p3,0.005);
    tikz.endScope();

    tikz.node ( p0, "\\tiny$(\\frac{1}{2}-\\cos\\alpha,\\frac{1}{2}-\\sin\\alpha)$", "above" );
    tikz.node ( p1, "\\tiny$(\\cos\\alpha-\\frac{1}{2},\\sin\\alpha-\\frac{1}{2})$", "above" );
    tikz.node ( p2, "\\tiny$(\\frac{1}{2}-\\sin\\alpha,\\cos\\alpha-\\frac{1}{2})$", "above" );
    tikz.node ( p3, "\\tiny$(\\sin\\alpha-\\frac{1}{2},\\frac{1}{2}-\\cos\\alpha)$", "below" );

    tikz.comment ( "Frames' indexes" );
    //range indexes -- horizontal
    tikz.node ( QPointF ( p0.x() / 2., topLeft.y()), "\\tiny-2", "above" );
    tikz.node ( QPointF ( p3.x() / 2., topLeft.y()), "\\tiny-1", "above" );
    tikz.node ( QPointF ( topRight.x() / 2., topLeft.y() ), "\\tiny0", "above" );
    tikz.node ( QPointF ( topRight.x() - p3.x() / 2., topLeft.y()), "\\tiny1", "above" );
    tikz.node ( QPointF ( topRight.x() - p0.x() / 2. , topLeft.y()), "\\tiny2", "above" );

    //range indexes -- vertical
    tikz.node ( QPointF (topLeft.x(), topLeft.y() - p3.y() / 2. ), "\\tiny2", "left" );
    tikz.node ( QPointF (topLeft.x(), topRight.y() - p1.y() / 2. ), "\\tiny1", "left" );
    tikz.node ( QPointF (topLeft.x(), topLeft.y() / 2. ), "\\tiny0", "left" );
    tikz.node ( QPointF (topLeft.x(), p1.y() / 2. ), "\\tiny-1", "left" );
    tikz.node ( QPointF (topLeft.x(), p3.y() / 2. ), "\\tiny-2", "left" );

    tikz.comment( "Some 8-adj lines -- others" );
    tikz.beginScope("color=blue");
            QPointF p0ii ( 1. - (m_cos - m_sin), 1. - (m_cos - m_sin) );
            tikz.line ( QPointF ( p0ii.x(), 0. ), QPointF ( p0ii.x(), 1. ) );
            tikz.line ( QPointF ( 0., p0ii.y() ), QPointF ( 1., p0ii.y() ) );
            QPointF p1ii ( m_cos - m_sin, m_cos - m_sin );
            tikz.line ( QPointF ( p1ii.x(), 0. ), QPointF ( p1ii.x(), 1. ) );
            tikz.line ( QPointF ( 0., p1ii.y() ), QPointF ( 1., p1ii.y() ) );

            QPointF p1iii ( ( m_cos + m_sin ) - 1., ( m_cos + m_sin ) - 1.);
            tikz.line ( QPointF ( p1iii.x(), 0. ), QPointF ( p1iii.x(), 1. ) );
            tikz.line ( QPointF ( 0., p1iii.y() ), QPointF ( 1., p1iii.y() ) );

            QPointF p1iv ( 2. - ( m_cos + m_sin ), 2. - ( m_cos + m_sin ) );
            tikz.line ( QPointF ( p1iv.x(), 0. ), QPointF ( p1iv.x(), 1. ) );
            tikz.line ( QPointF ( 0., p1iv.y() ), QPointF ( 1., p1iv.y() ) );

    tikz.endScope();
}

void Torus2D::angleChanged(double angle)
{
    m_cos = std::cos(angle);
    m_sin = std::sin(angle);
    update();
}

void Torus2D::translationChanged(double x, double y)
{
    m_x = x;
    m_y = y;
    update();
}

void Torus2D::colorChanged(RealPoint & point, TilingWidget *w)
{
    QPoint p ((point[0] * width() + width()/2), height() - (point[1] * height() + height()/2));
    w->setGeometry( QRect( p.x() - w->width()/2 , p.y() - w->height()/2 , w->width(), w->height()) );
    update();
}

void Torus2D::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::blue);
    painter.drawRect ( QRectF ( 0, 0, size().width() - 1, size().height() - 1 ) );
    painter.setPen(Qt::red);
    QPointF p0 (m_cos * width(), height() - m_sin * height());
    QPointF p1 (width() - m_cos * width(), m_sin * height());

    QPointF p2 (m_sin * width(), m_cos * height());
    QPointF p3 (width() - m_sin * width(), height() - m_cos * height());

    painter.drawLine ( QLineF ( QPointF(0,height()), p0 ) );
    painter.drawLine ( QLineF ( QPointF(width(),0), p1 ) );
    painter.drawLine ( QLineF ( QPointF(0,0), p2 ) );
    painter.drawLine ( QLineF ( QPointF(width(),height()), p3 ) );

    painter.setPen(Qt::blue);
    //vertical
    painter.drawLine ( QLineF ( p0.x(), 0, p0.x(), height() ) );
    painter.drawLine ( QLineF ( p1.x(), 0, p1.x(), height() ) );
    //horizontal
    painter.drawLine ( QLineF ( 0, p0.y(), width(), p0.y() ) );
    painter.drawLine ( QLineF ( 0, p1.y(), width(), p1.y() ) );

    //vertical
    painter.drawLine ( QLineF ( 0, p2.y(), width(), p2.y() ) );
    painter.drawLine ( QLineF ( 0, p3.y(), width(), p3.y() ) );
    //horizontal
    painter.drawLine ( QLineF ( p2.x(), 0, p2.x(), height() ) );
    painter.drawLine ( QLineF ( p3.x(), 0, p3.x(), height() ) );

    // additional 8-conn
    // these ones which are going in
    painter.setPen(Qt::darkGreen);
    //horizontal
    QPointF p0i ( m_sin * width() + m_cos * height(), m_cos * width() - m_sin * height() );
    QPointF p1i ( width() -(m_sin * width() + m_cos * height()), height() -(m_cos * width() - m_sin * height()) );
    painter.drawLine ( QLineF ( 0, p0i.y(), width(), p0i.y() ) );
    painter.drawLine ( QLineF ( width(), p1i.y(), -width(), p1i.y() ) );
//    //diagonal -- horizontal movment
    painter.drawLine ( QLineF ( p1i.x(), p1i.y(), p0i.x(), p0i.y() ) );

//    //vertical
    QPointF p2i ( width() -(m_cos * width() - m_sin * height()), m_sin * width() + m_cos * height() );
    QPointF p3i ( m_cos * width() - m_sin * height(), height() - ( m_sin * width() + m_cos * height() ) );

    painter.drawLine ( QLineF ( p2i.x(), p2i.y(), p2i.x(), 0 ) );
//    //diagonal vertical
    painter.drawLine ( QLineF ( p3i.x(), p3i.y(), p2i.x(), p2i.y() ) );
    painter.drawLine ( QLineF ( p3i.x(), p3i.y(), p3i.x(), height() ) );

//    // inverted x or y -- these ones which are going out
    painter.setPen(Qt::darkMagenta);
    QPointF p0c ( p3i.x(), -p3i.y() );
    painter.drawLine ( QLineF ( width(), p0c.y(), 0, p0c.y() ) );

    QPointF p1c ( p2i.x(), height() - (p2i.y() - height()) );
    painter.drawLine ( QLineF ( 0, p1c.y(), width(), p1c.y() ) );

    QPointF p2c ( -p1i.x(), p1i.y() );
    painter.drawLine ( QLineF ( p2c.x(), 0, p2c.x(), height() ) );

    QPointF p3c ( width() - ( p0i.x() - width() ), p0i.y() );
    painter.drawLine ( QLineF ( p3c.x(), height(), p3c.x(), 0 ) );



//    // merge lines -- verticals

    painter.setPen ( QPen ( Qt::magenta, 1, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin ));
    QPointF vector1 ( p1.x() - width(), p1.y() );

    painter.drawLine ( QLineF(vector1 + QPointF ( p0.x(), p3.y() ), QPointF ( p0.x(), p3.y() ) ) );
    painter.drawLine ( QLineF(vector1 + QPointF ( width(), p3.y() ), QPointF ( width(), p3.y() ) ) );

    painter.drawLine ( QLineF(vector1 + QPointF ( p0.x(), p1.y() ), QPointF ( p0.x(), p1.y() ) ) );
    painter.drawLine ( QLineF(vector1 + QPointF ( width(), p1.y() ), QPointF ( width(), p1.y() ) ) );

    painter.drawLine ( QLineF(vector1 + QPointF ( p0.x(), p0.y() ), QPointF ( p0.x(), p0.y() ) ) );
    painter.drawLine ( QLineF(vector1 + QPointF ( width(), p0.y() ), QPointF ( width(), p0.y() ) ) );


    QPointF vector2 ( p0.x(), p0.y() - height() );

    painter.drawLine ( QLineF(vector2 + QPointF ( p1.x(), p2.y() ), QPointF ( p1.x(), p2.y() ) ) );
    painter.drawLine ( QLineF(vector2 + QPointF ( 0, p2.y() ), QPointF ( 0, p2.y() ) ) );


    painter.drawLine ( QLineF(vector2 + QPointF ( p1.x(), p0.y() ), QPointF ( p1.x(), p0.y() ) ) );
    painter.drawLine ( QLineF(vector2 + QPointF ( 0, p0.y() ), QPointF ( 0, p0.y() ) ) );

    painter.drawLine ( QLineF(vector2 + QPointF ( p1.x(), p1.y() ), QPointF ( p1.x(), p1.y() ) ) );
    painter.drawLine ( QLineF(vector2 + QPointF ( 0, p1.y() ), QPointF ( 0, p1.y() ) ) );


//    non-injective frames
    QPen pen1(Qt::red, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen1);
    painter.setBrush(Qt::Dense5Pattern);
    painter.drawRect ( QRectF ( QPointF(0, 0), QPointF(p3.x(), p3.y()) ) );
    painter.drawRect ( QRectF ( QPointF(p0.x(), 0), QPointF(size().width() - 1, p0.y()) ) );
    painter.drawRect ( QRectF ( QPointF(0, p1.y()), QPointF(p1.x(), size().height() - 1) ) );
    painter.drawRect ( QRectF ( QPointF(p2.x(), p2.y()), QPointF(size().width() - 1, size().height() - 1) ) );

    //non-surjective frames
    QPen pen2(Qt::red, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen2);
    painter.setBrush(Qt::Dense5Pattern);
    painter.drawRect ( QRectF ( QPointF(p1.x(), 0), QPointF(p2.x(), p0c.y()) ) );
    painter.drawRect ( QRectF ( QPointF(p3c.x(), p3.y()), QPointF(size().width() - 1, p1.y()) ) );
    painter.drawRect ( QRectF ( QPointF(0, p0.y()), QPointF(p2c.x(), p2.y()) ) );
    painter.drawRect ( QRectF ( QPointF(p3.x(), p1c.y()), QPointF(p0.x(), size().height() - 1) ) );

}
