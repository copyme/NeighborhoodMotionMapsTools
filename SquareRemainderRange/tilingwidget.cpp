#include <QVector>
#include <QPainter>
#include <QPainterPath>
#include "tilingwidget.h"

TilingWidget::TilingWidget (QRectF rec, QWidget *parent , const char *p_label) :
    QWidget(parent), label(p_label)
{
    setGeometry ( rec.x(), rec.y(), rec.width(), rec.height() );
    QPalette pal( palette() );
    pal.setColor( QPalette::Window, Qt::transparent );
    setAutoFillBackground ( true );
    setPalette ( pal );


    // this has to give us bigger N.

    // first row
    tilings.push_back ( new Frame ( QRect ( 9, 0, 10, 10 ), this ) );
    tilings.push_back ( new Frame ( QRect ( 18, 0, 10, 10 ), this ) );
    tilings.push_back ( new Frame ( QRect ( 27, 0, 10, 10 ), this ) );

    // sec row
    tilings.push_back ( new Frame ( QRect ( 0, 9, 10, 10 ), this ) );
    tilings.push_back ( new Frame ( QRect ( 9, 9, 10, 10 ), this ) );
    tilings.push_back ( new Frame ( QRect ( 18, 9, 10, 10 ), this ) );
    tilings.push_back ( new Frame ( QRect ( 27, 9, 10, 10 ), this ) );
    tilings.push_back ( new Frame ( QRect ( 36, 9, 10, 10 ), this ) );

    // third row
    tilings.push_back ( new Frame ( QRect ( 0, 18, 10, 10 ), this ) );
    tilings.push_back ( new Frame ( QRect ( 9, 18, 10, 10 ), this ) );
    tilings.push_back ( new Frame ( QRect ( 18, 18, 10, 10 ), this ) );
    tilings.push_back ( new Frame ( QRect ( 27, 18, 10, 10 ), this ) );
    tilings.push_back ( new Frame ( QRect ( 36, 18, 10, 10 ), this ) );

    // 4th row
    tilings.push_back ( new Frame ( QRect ( 0, 27, 10, 10 ), this ) );
    tilings.push_back ( new Frame ( QRect ( 9, 27, 10, 10 ), this ) );
    tilings.push_back ( new Frame ( QRect ( 18, 27, 10, 10 ), this ) );
    tilings.push_back ( new Frame ( QRect ( 27, 27, 10, 10 ), this ) );
    tilings.push_back ( new Frame ( QRect ( 36, 27, 10, 10 ), this ) );

    // 5th row
    tilings.push_back ( new Frame ( QRect ( 9, 36, 10, 10 ), this ) );
    tilings.push_back ( new Frame ( QRect ( 18, 36, 10, 10 ), this ) );
    tilings.push_back ( new Frame ( QRect ( 27, 36, 10, 10 ), this ) );


    tilings.at ( 0 )->setVisible ( false );
    tilings.at ( 1 )->setVisible ( false );
    tilings.at ( 2 )->setVisible ( false );
    tilings.at ( 3 )->setVisible ( false );
    tilings.at ( 7 )->setVisible ( false );
    tilings.at ( 8 )->setVisible ( false );
    tilings.at ( 12 )->setVisible ( false );
    tilings.at ( 13 )->setVisible ( false );
    tilings.at ( 17 )->setVisible ( false );
    tilings.at ( 18 )->setVisible ( false );
    tilings.at ( 19 )->setVisible ( false );
    tilings.at ( 20 )->setVisible ( false );

    colorMap.push_back ( QColor ( 141, 182, 0 ) ); // YellowGreen
    colorMap.push_back ( Qt::cyan );
    colorMap.push_back ( Qt::magenta );
    colorMap.push_back ( QColor ( 255, 165, 0 ) ); // orange
    colorMap.push_back ( Qt::yellow );
    colorMap.push_back ( Qt::green );
    colorMap.push_back ( Qt::red );
    colorMap.push_back ( Qt::blue );
    colorMap.push_back ( Qt::black );
}

void TilingWidget::setAdjacency ( int state )
{
    if ( state == Qt::Unchecked )
    {
        tilings.at ( 0 )->setVisible ( false );
        tilings.at ( 1 )->setVisible ( false );
        tilings.at ( 2 )->setVisible ( false );
        tilings.at ( 3 )->setVisible ( false );
        tilings.at ( 7 )->setVisible ( false );
        tilings.at ( 8 )->setVisible ( false );
        tilings.at ( 12 )->setVisible ( false );
        tilings.at ( 13 )->setVisible ( false );
        tilings.at ( 17 )->setVisible ( false );
        tilings.at ( 18 )->setVisible ( false );
        tilings.at ( 19 )->setVisible ( false );
        tilings.at ( 20 )->setVisible ( false );
    }
    else if ( Qt::Checked )
    {
        tilings.at ( 0 )->setVisible ( true );
        tilings.at ( 1 )->setVisible ( true );
        tilings.at ( 2 )->setVisible ( true );
        tilings.at ( 3 )->setVisible ( true );
        tilings.at ( 7 )->setVisible ( true );
        tilings.at ( 8 )->setVisible ( true );
        tilings.at ( 12 )->setVisible ( true );
        tilings.at ( 13 )->setVisible ( true );
        tilings.at ( 17 )->setVisible ( true );
        tilings.at ( 18 )->setVisible ( true );
        tilings.at ( 19 )->setVisible ( true );
        tilings.at ( 20 )->setVisible ( true );
    }
}

void TilingWidget::paintEvent(QPaintEvent *)
{

    for ( QVector<Frame *>::const_iterator it = tilings.begin(); it != tilings.end(); ++it )
        (*it)->clear();
    tilings.at ( 10 )->addColor ( colorMap[8] );

    for ( unsigned int i = 0; i < points.size(); i++ )
    {
        //4-conn
        if( points.at ( i )[0] == 1 &&  points.at ( i )[1] == 1 )
            tilings.at ( 6 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == 0 && points.at ( i )[1] == 1 )
            tilings.at ( 5 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == -1 && points.at ( i )[1] == 1 )
            tilings.at ( 4 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == -1 && points.at ( i )[1] == 0 )
            tilings.at ( 9 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == -1 && points.at ( i )[1] == -1 )
            tilings.at ( 14 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == 0 && points.at ( i )[1] == -1 )
            tilings.at ( 15 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == 1 && points.at ( i )[1] == -1 )
            tilings.at ( 16 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == 1 && points.at ( i )[1] == 0 )
            tilings.at ( 11 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == 0 && points.at ( i )[1] == 0 )
            tilings.at ( 10 )->addColor ( colorMap[i] );
        // 8-conn
        else if( points.at ( i )[0] == -1 && points.at ( i )[1] == 2 )
            tilings.at ( 0 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == 0 && points.at ( i )[1] == 2 )
            tilings.at ( 1 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == 1 && points.at ( i )[1] == 2 )
            tilings.at ( 2 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == -2 && points.at ( i )[1] == 1 )
            tilings.at ( 3 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == 2 && points.at ( i )[1] == 1 )
            tilings.at ( 7 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == -2 && points.at ( i )[1] == 0 )
            tilings.at ( 8 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == 2 && points.at ( i )[1] == 0 )
            tilings.at ( 12 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == -2 && points.at ( i )[1] == -1 )
            tilings.at ( 13 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == 2 && points.at ( i )[1] == -1 )
            tilings.at ( 17 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == -1 && points.at ( i )[1] == -2 )
            tilings.at ( 18 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == 0 && points.at ( i )[1] == -2 )
            tilings.at ( 19 )->addColor ( colorMap[i] );
        else if( points.at ( i )[0] == 1 && points.at ( i )[1] == -2 )
            tilings.at ( 20 )->addColor ( colorMap[i] );
    }
    QPainter painter(this);
    painter.setRenderHints(QPainter::TextAntialiasing);
    QFont font;
    font.setPointSize(5);
    painter.setFont(font);
    painter.setPen(QPen(Qt::black, 1));
    painter.drawText(QPoint(0,height()),label);
}

void TilingWidget::colorChanged(std::vector<Point> &points)
{
    this->points = points;
    update();
}

Frame::Frame (QRectF rec, QWidget *parent) : QWidget ( parent )
{
    setGeometry ( rec.x(), rec.y(), rec.width(), rec.height() );
    QPalette pal( palette() );
    pal.setColor( QPalette::Window, Qt::transparent );
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
    QPainter painter ( this );
    if ( second == Qt::transparent )
        painter.fillRect( rect(), QBrush ( first, Qt::SolidPattern ) );
    else
    {
        QPolygonF region1;
        region1.push_back ( QPointF ( 0, 0 ) );
        region1.push_back ( QPointF ( 0, height() - 1 ) );
        region1.push_back ( QPointF ( width() - 1, height() - 1 ) );
        region1.push_back ( QPointF ( 0, 0 ) );

        QPainterPath path1;
        path1.addPolygon ( region1 );
        painter.fillPath ( path1, QBrush ( first, Qt::SolidPattern ) );

        QPolygonF region2;
        region2.push_back ( QPointF ( 0, 0 ) );
        region2.push_back ( QPointF ( width() - 1, 0 ) );
        region2.push_back ( QPointF ( width() - 1, height() - 1 ) );
        region2.push_back ( QPointF ( 0, 0 ) );

        QPainterPath path2;
        path2.addPolygon ( region2 );
        painter.fillPath ( path2, QBrush ( second, Qt::SolidPattern ) );
    }
        painter.setPen ( QPen ( Qt::black ) );
        painter.drawRect ( QRect ( 0,0, width() - 1, height() - 1 ) );
}
