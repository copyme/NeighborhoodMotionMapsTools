#include <QPainter>
#include "colorwidget.h"

ColorWidget::ColorWidget(QRectF rec, QWidget *parent, const char *p_label):
    QWidget(parent), label(p_label)
{
    setGeometry ( rec.x(), rec.y(), rec.width(), rec.height() );
    QPalette pal( palette() );
    pal.setColor( QPalette::Window, Qt::transparent );
    setAutoFillBackground ( true );
    setPalette ( pal );
}

void ColorWidget::colorChanged(std::vector<Point> &points)
{
    this->points = points;
    update();
}

void ColorWidget::labelTransformedPoint(const char *label)
{
    label2 = QString(label);
}

void ColorWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPointF center ( width()/2, height()/2 );

    painter.setPen ( QPen ( Qt::gray, 1 ) );
    painter.drawRect ( QRect ( rect().x(), rect().y(), rect().width() - 1, rect().height() - 1 ) );

    for ( unsigned int i = 0; i < points.size(); i++ )
    {
        painter.setPen ( QPen ( Qt::black,2 ) );
        if( points.at ( i )[0] == 1 &&  points.at ( i )[1] == 1 )
            painter.drawLine ( QLineF ( center, QPointF(width(),0) ) );
        else if( points.at ( i )[0] == 0 && points.at ( i )[1] == 1 )
            painter.drawLine ( QLineF ( center, QPointF(width()/2,0) ) );
        else if( points.at ( i )[0] == -1 && points.at ( i )[1] == 1 )
            painter.drawLine ( QLineF ( center, QPointF(0,0) ) );
        else if( points.at ( i )[0] == -1 && points.at ( i )[1] == 0 )
            painter.drawLine ( QLineF ( center, QPointF(0,height()/2) ) );
        else if( points.at ( i )[0] == -1 && points.at ( i )[1] == -1 )
            painter.drawLine ( QLineF ( center, QPointF(0,height()) ) );
        else if( points.at ( i )[0] == 0 && points.at ( i )[1] == -1 )
            painter.drawLine ( QLineF ( center, QPointF(width()/2,height()) ) );
        else if( points.at ( i )[0] == 1 && points.at ( i )[1] == -1 )
            painter.drawLine ( QLineF ( center, QPointF(width(),height()) ) );
        else if( points.at ( i )[0] == 1 && points.at ( i )[1] == 0 )
            painter.drawLine ( QLineF ( center, QPointF(width(),height()/2) ) );
        //20-neigborhood
        painter.setPen ( QPen ( Qt::blue, 2, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin ));
        if ( points.at ( i )[0] == 0 && points.at ( i )[1] == 2 )
            painter.drawLine ( QLineF ( center, QPointF(width()/2,0) ) );
        else if ( points.at ( i )[0] == 1 && points.at ( i )[1] == 2 )
            painter.drawLine ( QLineF ( center, QPointF(width() - width()/4,0) ) );
        else if ( points.at ( i )[0] == 2 && points.at ( i )[1] == 1 )
            painter.drawLine ( QLineF ( center, QPointF ( width(), height()/4 ) ) );
        else if ( points.at ( i )[0] == 2 && points.at ( i )[1] == 0 )
            painter.drawLine ( QLineF ( center, QPointF(width(), height()/2) ) );
        else if ( points.at ( i )[0] == 2 && points.at ( i )[1] == -1 )
            painter.drawLine ( QLineF ( center, QPointF ( width(), height() - height()/4 ) ) );
        else if ( points.at ( i )[0] == 1 && points.at ( i )[1] == -2 )
            painter.drawLine ( QLineF ( center, QPointF(width() - width()/4,height()) ) );
        else if ( points.at ( i )[0] == 0 && points.at ( i )[1] == -2 )
            painter.drawLine ( QLineF ( center, QPointF(width()/2,height() ) ) );
        else if ( points.at ( i )[0] == -1 && points.at ( i )[1] == -2 )
            painter.drawLine ( QLineF ( center, QPointF(width()/4,height()) ) );
        else if ( points.at ( i )[0] == -2 && points.at ( i )[1] == -1 )
            painter.drawLine ( QLineF ( center, QPointF(0,height() - height()/4) ) );
        else if ( points.at ( i )[0] == -2 && points.at ( i )[1] == 0 )
            painter.drawLine ( QLineF ( center, QPointF(0,height()/2) ) );
        else if ( points.at ( i )[0] == -2 && points.at ( i )[1] == 1 )
            painter.drawLine ( QLineF ( center, QPointF(0,height()/4) ) );
        else if ( points.at ( i )[0] == -1 && points.at ( i )[1] == 2 )
            painter.drawLine ( QLineF ( center, QPointF(width()/4,0) ) );
    }
    QFont font;
    font.setPointSize(6);
    painter.setFont(font);
    painter.setPen(QPen(Qt::red, 2));
    painter.drawText(QPoint(2,height()-2),label);

    painter.drawText(QPoint(2,8),label2);
}
